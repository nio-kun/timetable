#include "order_details.h"
#include "ui_order_details.h"
#include <QMessageBox>
#include <QDateTime>

order_details::order_details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::order_details)
{
    ui->setupUi(this);
}

order_details::order_details(QSqlDatabase *keptdb, int plc, QDateTime dt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::order_details)
{
    db=keptdb;
    destdate = dt;
    place = plc;
    ui->setupUi(this);
    if (db->isOpen()){
        db->transaction();
        QSqlQuery q;
        q.exec("select name from services order by name");q.first();
        do {ui->comboBox->addItem(q.value(0).toString()); } while (q.next());
    };
};




order_details::~order_details()
{
    delete ui;
}

void order_details::on_buttonBox_accepted()
{
    QSqlQuery q;
    if (ui->lineEdit->text().length()>0&&ui->lineEdit_2->text().length()>0
            &&ui->lineEdit_3->text().length()>0
            &&ui->lineEdit_4->text().length()>0&&ui->comboBox->currentText().length()>0){

        //Создаём клиента
        q.exec("select MAX(client_id) from clients"); q.first();
        QVariant newid= q.value(0).toInt()+1;
        q.exec("insert into clients (client_id, car, phone, name) values ("+newid.toString()+", '"+ui->lineEdit->text()+"', '"+ui->lineEdit_3->text()+"', '"+ui->lineEdit_2->text()+"');");

        //Находим услугу...
        q.exec("select service_id from services where name='"+ui->comboBox->currentText()+"'"); q.first();
        QVariant serv_id;
        if (q.size()==0){
            //...или не находим, тогда создаём новую.
            q.exec("select MAX(service_id) from services"); q.first();
            serv_id= q.value(0).toInt()+1;
            q.exec("insert into services (service_id, name) values ("+serv_id.toString()+", '"+
                   ui->comboBox->currentText()+"');");
        }else{
            serv_id=q.value(0).toInt();
        };

        //Добавляем запись на обслуживание
        q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(place)+", "+newid.toString()+", "+serv_id.toString()+", '"+
               destdate.toString("yyyy-MM-dd hh:mm:ss")+"', "+ui->lineEdit_4->text()+");");

        if (ui->checkBox->checkState()){
        //Если отмечено, записываем клиента на развал-схождение
        //Сначала вычисляем время окончания работ
        QDateTime et, endtime= destdate.addSecs(ui->lineEdit_4->text().toInt()*3600);

        //Узнаём, какая площадка делает развал-схождение
        q.exec("select place_id from places where rs=1"); q.first();
        int rsplace=q.value(0).toInt();
        //Находим ближайшее свободное время
        while (!isEmpty(endtime, rsplace)) {
            if (endtime.time() < QTime::fromString("18:00:00","hh:mm:ss")) {
                endtime.addSecs(3600);
            }else{
            et=endtime.addDays(1);
            endtime=QDateTime::fromString(et.toString("yyyy-MM-dd")+" 08:00:00","yyyy-MM-dd hh:mm:ss");
                };
        };
};
        db->commit();
}else{
    QMessageBox::critical(0, tr("Error!"), tr("All fields must be filled in."),0,0,0);
    };

};
bool order_details::isEmpty(QDateTime tme, QVariant rsplace)
{
QSqlQuery q;
//Находим ближайшую запись, которая предшествует времени окончания работы (tme)
q.exec("select MAX(record_id), date, hours from ttable where place_id="+rsplace.toString() +" and date<'"+tme.toString("yyyy-MM-dd hh:mm:ss")+"';"); q.first();
//Находим время её окончания
QDateTime endofwork= q.value(1).toDateTime().addSecs(q.value(2).toInt()*3600);
//Теперь мы знаем, когда заканчивается работа. Ищем, когда начинается следующая
q.exec("select MIN(record_id), date, hours from ttable where place_id="+rsplace.toString() +" and date>'"+endofwork.toString("yyyy-MM-dd hh:mm:ss")+"';");
if (q.size()>0){ //Такая работа нашлась
    q.first();
    QDateTime beginnextwork=q.value(1).toDateTime();
    if (endofwork>tme&&tme<beginnextwork) return true;
} else {
    //Такой работы не нашлось
    return true;
};
return false;
}


