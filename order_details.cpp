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
    ui->dateEdit->setDisabled(true);
    ui->dateEdit->setDate(dt.date());
    ui->lineEdit_5->setDisabled(true);
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
        //QDateTime endtime= destdate.addSecs(ui->lineEdit_4->text().toInt()*3600);

        //Узнаём, какая площадка делает развал-схождение
        q.exec("select place_id from places where rs=1");
        int rsplace=0;//=q.value(0).toInt();
        bool flag = false;
        while (q.next()){
            QSqlQuery q2;
            q2.exec("select max(date) from ttable where place_id="+q.value(0).toString()+" and date <= '"+ui->dateEdit->date().toString("yyyy-MM-dd")+" "+ui->lineEdit_5->text()+":00:00"+"';");
            if (q2.numRowsAffected()){
                q2.next();

                if (q2.value(0).toDate()<ui->dateEdit->date()){
                    rsplace=q.value(0).toInt();
                    q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(rsplace)+", "+newid.toString()+", 1, '"+
                           ui->dateEdit->date().toString("yyyy-MM-dd")+" "+ui->lineEdit_5->text()+":00:00"+"', 1)");
                    flag = true;
                    break;
                }else{

                    q2.exec("select date, hours from ttable where place_id="+q.value(0).toString()+" and date = '"+q2.value(0).toString()+"';");
                    q2.next();
                    if (q2.value(0).toDate()==ui->dateEdit->date() && q2.value(0).toDateTime().toString("hh").toInt()+q2.value(1).toInt() <=ui->lineEdit_5->text().toInt()){
                        rsplace=q.value(0).toInt();
                        q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(rsplace)+", "+newid.toString()+", 1, '"+
                               ui->dateEdit->date().toString("yyyy-MM-dd")+" "+ui->lineEdit_5->text()+":00:00"+"', 1)");
                        flag = true;
                        break;
                    }
                }
            }else{
                rsplace=q.value(0).toInt();
                q.exec("insert into ttable (place_id, client_id, service_id, date, hours) values ("+QString("%1").arg(rsplace)+", "+newid.toString()+", 1, '"+
                       ui->dateEdit->date().toString("yyyy-MM-dd")+" "+ui->lineEdit_5->text()+":00:00"+"', 1)");
                flag = true;
                break;
            }
        }
        if (!flag){
            QMessageBox::critical(0, tr("Error!"), tr("All incine platforms are busy at selected time") ,0,0,0); //по-английски предложение написано неправильно
        }

        //Находим, когда она освободится
        //Находим ближайшую работу
//        q.exec("select MAX(record_id), date, hours from ttable where place_id="+QString("%1").arg(rsplace)+" and date < '"+endtime.toString("yyyy-MM-dd hh:mm:ss")+"';");
//        q.first();
        //Находим время её окончания
//        QDateTime et = q.value(1).toDateTime().addSecs(3600*q.value(2).toInt());
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

void order_details::on_checkBox_stateChanged(int arg1)
{
    if (arg1){
        ui->dateEdit->setDisabled(false);
        ui->lineEdit_5->setDisabled(false);
    }else{
        ui->dateEdit->setDisabled(true);
        ui->lineEdit_5->setDisabled(true);
    }
}

void order_details::on_lineEdit_5_editingFinished()
{
    int dinner_start_time=0;
    int dinner_end_time=0;
    QSqlQuery query;
    query.exec("select value from settings where name='dinner_start_time'");
    if (query.numRowsAffected()>0){
        query.next();
        dinner_start_time=query.value(0).toInt();
    }

    query.exec("select value from settings where name='dinner_end_time'");
    if (query.numRowsAffected()>0){
        query.next();
        dinner_end_time=query.value(0).toInt();
    }

    if (dinner_start_time && dinner_end_time && dinner_start_time<=ui->lineEdit_5->text().toInt() && dinner_end_time> ui->lineEdit_5->text().toInt()){
        QMessageBox::critical(0,tr("Error!"),tr("You can't work at dinner time!"));
        ui->lineEdit_5->setFocus();
    }

}
