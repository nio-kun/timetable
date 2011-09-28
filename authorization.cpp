#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);

//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setDatabaseName("timetable");
//    db.setHostName("localhost");
//    db.setPort(3307);

}

authorization::authorization(QSqlDatabase *kept_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    db=kept_db;



}

authorization::~authorization()
{
    delete ui;
}

void authorization::on_pushButton_2_clicked()
{
    //QMessageBox::information(0, "Kanji",db->hostName(), 0,0,0);
    db->setUserName(ui->lineEdit->text());
    db->setPassword(ui->lineEdit_2->text());
    if( db->open() ){
        QSqlQuery query (*db);
        query.prepare ("select count(*) from users where login= :login");
        query.bindValue(":login", ui->lineEdit->text());


        if ( query.exec()){
            //QMessageBox::information(0, "Ошибка авторизации","Ура!!!", 0,0,0);
            query.next();
            if (query.value(0).toInt()>0){
                this->hide();
            }else{
                QMessageBox::information(0, "Ошибка авторизации","Авторизация не удалась", 0,0,0);
            }
        }else{
            QMessageBox::information(0, "Ошибка авторизации",db->lastError().text(), 0,0,0);
//            QMessageBox::information(0, "Ошибка авторизации","Авторизация не удалась", 0,0,0);
        }
    }else{
        QMessageBox::information(0, "Ошибка авторизации",db->lastError().text(), 0,0,0);
//        QMessageBox::information(0, "Ошибка авторизации","Авторизация не удалась", 0,0,0);
    }

}

void authorization::on_pushButton_clicked()
{
    this->close();
}

void authorization::closeEvent(QCloseEvent *event)
{
    exit(0);
}
