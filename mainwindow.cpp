#include "mainwindow.h"
#include "settings.h"
#include "places.h"
#include "users.h"
#include "services.h"
#include "authorization.h"

#include "ui_mainwindow.h"
#include "authorization.h"
#include "mheader.h"
#include "toolbars.h"



#define SPANCOLS(txt,start,stop) \
 if (!h->spanCols(QString("%1 %2-%3").arg(txt).arg(start).arg(stop),start,stop))\
   qDebug()<<QString("Failure for %1,%2").arg(start).arg(stop);

#define SPANCOLS2(txt,start,stop) \
 if (!h->spanCols(QString(txt),start,stop))\
   qDebug()<<QString("Failure for %1,%2").arg(start).arg(stop);



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Строим панели инструментов
      MakeToolbars();
      day = QDate::currentDate();

    //Подключение к БД и авторизация
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("timetable");
    authorization a(&db);
    a.exec();
    QTableWidget *tw = ui->ttable;
     h = new HMultiHeader(tw, Qt::Horizontal);
    tw->setHorizontalHeader(h);

onOneDay();


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
 settings s(&db);
 s.exec();
}

void MainWindow::on_action_3_triggered()
{
    places s(&db);
    s.exec();
}

void MainWindow::on_action_4_triggered()
{
    users s(&db);
    s.exec();
}

void MainWindow::on_action_5_triggered()
{
    services s(&db);
    s.exec();
}


void MainWindow::on_action_6_triggered()
{
    authorization *s = new authorization;
    s->show();
//ui->tableView->model()->setItemData()
}

void MainWindow::on_ttable_doubleClicked(QModelIndex index)
{
    //Двойной клик - вызываем форму назначения.

}

void MainWindow::onPrev()
{

}

void MainWindow::onNext(){

}

void MainWindow::ClearTTable(){
    //Зачистка
        int m=ui->ttable->columnCount();
        for (int i=0;i<=m;i++) ui->ttable->removeColumn(0);
        int n=ui->ttable->rowCount();
        for (int i=0;i<=n;i++) ui->ttable->removeRow(0);
}

void MainWindow::onOneDay(){
ClearTTable();
    //Создаём заголовки таблицы
        //Строки
        QStringList lblsH, lblsV;
        for (int i=8;i<20;i++)
        {
            lblsH.append(QString("%1:00").arg(i));
            ui->ttable->insertRow(i-8);
        }
        ui->ttable->setVerticalHeaderLabels(lblsH);

    //Столбцы
    if (db.isOpen()){
        QSqlQuery query;
        query.exec("select place_id, name from places order by name");
        int j=0;
        while (query.next()){
            ui->ttable->insertColumn(j);
            lblsV.append(QString(query.value(1).toString()));
            j++;
        }
    }
    ui->ttable->setHorizontalHeaderLabels(lblsV);
    QString cday=day.toString("dd.MM.yyyy dddd");
    SPANCOLS2(cday ,0,2);
}
void MainWindow::onTwoDays(){}
void MainWindow::onThreeDays(){}
void MainWindow::onWeek(){}


