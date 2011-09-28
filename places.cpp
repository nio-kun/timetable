#include "places.h"
#include "ui_places.h"

places::places(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::places)
{
    ui->setupUi(this);
}

places::~places()
{
    delete ui;
}
