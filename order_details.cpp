#include "order_details.h"
#include "ui_order_details.h"
#include <QMessageBox>
#include <QDateTime>
#include <QSqlError>

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

        if (!q.exec("insert into clients (client_id, car, phone, name) values ("+newid.toString()+", '"+ui->lineEdit->text()+"', '"+ui->lineEdit_3->text()+"', '"+ui->lineEdit_2->text()+"');")){
            QMessageBox::critical(0, tr("Error!"),db->lastError().text() ,0,0,0);
        }

        //Находим услугу...
        if (!q.exec("select service_id from services where name='"+ui->comboBox->currentText()+"'")){
            QMessageBox::critical(0, tr("Error!"),db->lastError().text() ,0,0,0);
        }
        q.first();
        QVariant serv_id;
        if (q.size()==0){
            //...или не находим, тогда создаём новую.
            if (!q.exec("select MAX(service_id) from services")){
                QMessageBox::critical(0, tr("Error!"),db->lastError().text() ,0,0,0);
            }
            q.first();
            serv_id= q.value(0).toInt()+1;
            if (!q.exec("insert into services (service_id, name) values ("+serv_id.toString()+", '"+
                   ui->comboBox->currentText()+"');")){
                QMessageBox::critical(0, tr("Error!"),db->lastError().text() ,0,0,0);
            }
        }else{
            serv_id=q.value(0).toInt();
        };

        int work_end_time=24;
        int work_start_time=0;
        q.exec("select value from settings where name='work_start_time'");
        if (q.numRowsAffected()>0){
            q.next();
            work_start_time=q.value(0).toInt();
            if (work_start_time==24) work_start_time=0;
        }
        q.exec("select value from settings where name='work_end_time'");
        if (q.numRowsAffected()>0){
            q.next();
            work_end_time=q.value(0).toInt();
            if (work_end_time==0) work_end_time=24;
        }


        //Добавляем запись на обслуживание
        if ((destdate.toString("hh").toInt()+ui->lineEdit_4->text().toInt())<=work_end_time){
            if (!q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(place)+", "+newid.toString()+", "+serv_id.toString()+", '"+
                   destdate.toString("yyyy-MM-dd hh:mm:ss")+"', "+ui->lineEdit_4->text()+");")){
                QMessageBox::critical(0, tr("Error!"),db->lastError().text() ,0,0,0);
            }
        }else{
            int remain_hours=ui->lineEdit_4->text().toInt()-work_end_time+destdate.toString("hh").toInt();
            if (!q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(place)+", "+newid.toString()+", "+serv_id.toString()+", '"+
                   destdate.toString("yyyy-MM-dd hh:mm:ss")+"', "+QString::number(work_end_time-destdate.toString("hh").toInt())+");")){
                QMessageBox::critical(0, tr("Error!"),  db->lastError().text() ,0,0,0);
            }
            QDateTime testdate=destdate.addDays(1);
            QTime time(work_start_time,0);
            testdate.setTime(time);

            q.exec("select date, hours from ttable");
            bool flag_insert = false;
            while (q.next()){
                if (q.value(0).toDate()!=testdate.date()||(q.value(0).toDateTime().toString("hh").toInt()-testdate.toString("hh").toInt())>=remain_hours){
                    if (!q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(place)+", "+newid.toString()+", "+serv_id.toString()+", '"+
                           testdate.toString("yyyy-MM-dd hh:mm:ss")+"', "+QString::number(remain_hours)+");")){
                        QMessageBox::critical(0, tr("Error!"),  db->lastError().text() ,0,0,0);
                    }
                    flag_insert = true;
                    break;
                }else{
                    if ((q.value(0).toDateTime().toString("hh").toInt()+q.value(1).toInt())<work_end_time){
                        time.setHMS(q.value(0).toDateTime().toString("hh").toInt()+q.value(1).toInt(),0,0);
                    }else{
                        testdate=testdate.addDays(1);
                        time.setHMS(work_start_time,0,0);
                    }
                    testdate.setTime(time);
                }
            }
            if (flag_insert == false){
                if ((testdate.toString("hh").toInt()+remain_hours) > work_end_time){
                    testdate=testdate.addDays(1);
                    time.setHMS(work_start_time,0,0);
                }
                if (!q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(place)+", "+newid.toString()+", "+serv_id.toString()+", '"+
                       testdate.toString("yyyy-MM-dd hh:mm:ss")+"', "+QString::number(remain_hours)+");")){
                    QMessageBox::critical(0, tr("Error!"),  db->lastError().text() ,0,0,0);
                }

            }

        }
        
        
            if (ui->checkBox->checkState()){
        //Если отмечено, записываем клиента на развал-схождение
        //Сначала вычисляем время окончания работ
        QDateTime endtime= destdate.addSecs(ui->lineEdit_4->text().toInt()*3600);

        //Узнаём, какая площадка делает развал-схождение
        q.exec("select place_id from places where rs=1"); q.first();
        int rsplace=q.value(0).toInt();

        //Находим, когда она освободится
        //Находим ближайшую работу
        q.exec("select MAX(record_id), date, hours from ttable where place_id="+QString("%1").arg(rsplace)+" and date < '"+endtime.toString("yyyy-MM-dd hh:mm:ss")+"';");
        q.first();
        //Находим время её окончания
        QDateTime et = q.value(1).toDateTime().addSecs(3600*q.value(2).toInt());
/*

        q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(rsplace)+", "+newid.toString()+", "+serv_id.toString()+", '"+
               endtime.toString("yyyy-MM-dd hh:mm:ss")+"', 1)");
               * */
        };
        

        db->commit();
}else{
    QMessageBox::critical(0, tr("Error!"), tr("All fields must be filled in."),0,0,0);
    };
}
