#include "services.h"
#include "ui_services.h"

services::services(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::services)
{
    ui->setupUi(this);
}

services::~services()
{
    delete ui;
}
