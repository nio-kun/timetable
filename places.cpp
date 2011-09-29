#include "places.h"
#include "ui_places.h"

places::places(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::places)
{
    ui->setupUi(this);
}

places::places(QSqlDatabase *kept_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::places)
{
    ui->setupUi(this);
    db=kept_db;
    if (db->isOpen()){
        QSqlQuery query;
        query.exec("select place_id, name, color, rs from places order by name");
        while (query.next()){
            ui->listWidget->addItem(query.value(1).toString());
        }
    }

}

places::~places()
{
    delete ui;
}

void places::on_pushButton_clicked()
{

}
