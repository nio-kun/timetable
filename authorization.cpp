#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("timetable");
    db.setHostName("localhost");
    db.setPort(3307);

}

authorization::authorization(QSqlDatabase *kept_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    //db=kept_db;
ui->buttonBox->Reset;


}

authorization::~authorization()
{
    delete ui;
}

void authorization::on_buttonBox_clicked(QAbstractButton* button)
{
//    QSqlDatabase db;// = QSqlDatabase::addDatabase("QMYSQL");
    //QMessageBox::information(0, "Kanji","test", 0,0,0);
//    result();
//    this->show();
    return;
}

void authorization::on_buttonBox_accepted()
{
//    QMessageBox::information(0, "Kanji","accept", 0,0,0);
//    ui->buttonBox->event()

        return;
}

void authorization::on_pushButton_2_clicked()
{
    //QMessageBox::information(0, "Kanji",db->hostName(), 0,0,0);
    db.setUserName(ui->lineEdit->text());
    db.setPassword(ui->lineEdit_2->text());
    if( db.open() ){
        //QMessageBox::information(0, "Авторизация удалась","Авторизация удалась", 0,0,0);
        this->hide();
        MainWindow *w = new MainWindow;

        w->show();
//
    }else{
        QMessageBox::information(0, "Ошибка авторизации",db.lastError().text(), 0,0,0);
    }

}
