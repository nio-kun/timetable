#include "order_details.h"
#include "ui_order_details.h"

order_details::order_details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::order_details)
{
    ui->setupUi(this);
}

order_details::order_details(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::order_details)
{
    ui->setupUi(this);
    if (db->isOpen()){

    };
};




order_details::~order_details()
{
    delete ui;
}
