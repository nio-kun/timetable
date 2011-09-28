#include "mainwindow.h"
#include "settings.h"
#include "places.h"
#include "users.h"
#include "services.h"
#include "ui_mainwindow.h"
#include "authorization.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList lbls;
    lbls.insert(0,"08:00");
    lbls.insert(1,"09:00");
    lbls.insert(2,"10:00");
    lbls.insert(3,"11:00");
    lbls.insert(4,"12:00");
    lbls.insert(5,"13:00");
    lbls.insert(6,"14:00");
    lbls.insert(7,"15:00");
    lbls.insert(8,"16:00");
    lbls.insert(9,"17:00");
    lbls.insert(10,"18:00");
    lbls.insert(11,"19:00");

    ui->ttable->insertRow(0);
    ui->ttable->insertRow(1);
    ui->ttable->insertRow(2);
    ui->ttable->insertRow(3);
    ui->ttable->insertRow(4);
    ui->ttable->insertRow(5);
    ui->ttable->insertRow(6);
    ui->ttable->insertRow(7);
    ui->ttable->insertRow(8);
    ui->ttable->insertRow(9);
    ui->ttable->insertRow(10);
    ui->ttable->insertRow(11);
    ui->ttable->setVerticalHeaderLabels(lbls);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("timetable");
    db.setHostName("localhost");
    db.setPort(3307);

    authorization a(&db);
    a.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered()
{
   exit(0);
}

void MainWindow::on_action_triggered()
{
 settings s;
 s.exec();
}

void MainWindow::on_action_3_triggered()
{
    places s;
    s.exec();
}

void MainWindow::on_action_4_triggered()
{
    users s;
    s.exec();
}

void MainWindow::on_action_5_triggered()
{
    services s;
    s.exec();
}

void MainWindow::on_pushButton_clicked()
{







}
