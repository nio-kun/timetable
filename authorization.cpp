#include "authorization.h"
#include "ui_authorization.h"
#include "mainwindow.h"
#include "settings.h"

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

authorization::authorization(QSqlDatabase *kept_db, QColor *d_color, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    db=kept_db;
    dinner_color=d_color;
    read_properties();
}

authorization::~authorization()
{
    delete ui;
}

void authorization::on_pushButton_2_clicked()
{
    read_properties();

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
                QMessageBox::critical(0, "Ошибка авторизации","Авторизация не удалась", 0,0,0);
            }
        }else{
            QMessageBox::critical(0, "Ошибка авторизации",db->lastError().text(), 0,0,0);
//            QMessageBox::information(0, "Ошибка авторизации","Авторизация не удалась", 0,0,0);
        }
    }else{
        QMessageBox::critical(0, "Ошибка авторизации",db->lastError().text(), 0,0,0);
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

void authorization::on_pushButton_3_clicked()
{
    settings s(db, dinner_color, true);
    s.exec();
}

void authorization::on_authorization_rejected()
{
    QMessageBox::critical(0, tr("Ошибка авторизации"),"Ляля", 0,0,0);
}

void authorization::reject()
{
    //Не удалять! Эта функция запрещает закрывать форму авторизации при нажатии на кнопку Escape
}

void  authorization::read_properties()
{
    //QMessageBox::information(0, "Kanji",db->hostName(), 0,0,0);
    QFile file(qApp->applicationDirPath()+"/properties.ini");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString temp_text;
        int pos;
        QString param;
        while ( !stream.atEnd() ) {
            temp_text=stream.readLine();
            pos = temp_text.indexOf("=");
            if (pos>-1){
                param=temp_text.left(pos).trimmed();

                if (param=="database_host"){
                    db->setHostName(temp_text.mid(pos+1).trimmed());
                } else if (param=="database_port") {
                    db->setPort(temp_text.mid(pos+1).trimmed().toInt());
                } else if (param=="dinner_color") {
                    dinner_color->setNamedColor(temp_text.mid(pos+1).trimmed());
                }
            }
        }
        file.close();
    }
}
