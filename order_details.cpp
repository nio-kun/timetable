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
        db->commit();
}else{
    QMessageBox::critical(0, tr("Error!"), tr("All fields must be filled in."),0,0,0);
    };

}
