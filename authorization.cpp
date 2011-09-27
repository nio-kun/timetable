#include "authorization.h"
#include "ui_authorization.h"
//#include "QMessageBox"

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
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

void authorization::on_buttonBox_clicked(QAbstractButton* button)
{
//    QSqlDatabase db;// = QSqlDatabase::addDatabase("QMYSQL");
    //QMessageBox::information(0, "Kanji","test", 0,0,0);
//    result();
}

void authorization::on_buttonBox_accepted()
{
//    QMessageBox::information(0, "Kanji","accept", 0,0,0);
}
