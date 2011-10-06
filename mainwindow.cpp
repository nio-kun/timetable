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

//onOneDay();
    onTwoDays();


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
day=day.addDays(-1);
SetDays(Days);
}

void MainWindow::onNext(){
    day=day.addDays(1);
    SetDays(Days);
}

void MainWindow::ClearTTable(){
    //Зачистка
        int m=ui->ttable->columnCount();
        for (int i=0;i<=m;i++) ui->ttable->removeColumn(0);
        int n=ui->ttable->rowCount();
        for (int i=0;i<=n;i++) ui->ttable->removeRow(0);
        //Строки
        QStringList lblsH;
        for (int i=8;i<20;i++)
        {
            lblsH.append(QString("%1:00").arg(i));
            ui->ttable->insertRow(i-8);
        }
        ui->ttable->setVerticalHeaderLabels(lblsH);
}

void MainWindow::onOneDay(){Days=1; SetDays(1);}
void MainWindow::onTwoDays(){Days=2; SetDays(2);}
void MainWindow::onThreeDays(){Days=3; SetDays(3);}
void MainWindow::onWeek(){Days=7; SetDays(7);}

//Главнаяфункция, которая рисует дни
void MainWindow::SetDays(int DaysCount){
    ClearTTable(); //Очищаем таблицу
    QStringList lblsV; //Массив заголовков
    int placesCount;  //Число площадок

  if (db.isOpen()){
      QSqlQuery query;

      //Узнаём, сколько имеется площадок
      query.exec("select count(place_id) from places");
      query.first();
      placesCount= query.value(0).toInt();

      //Получаем список площадок
      query.exec("select place_id, name from places order by name");
      query.first();
      int j=0;
      for (int k=0;k<DaysCount;k++){
          // Забиваем список площадок в массив заголовков столько раз,
          // сколько требуется показать дней

          do {
              ui->ttable->insertColumn(j);
              lblsV.append(QString(query.value(1).toString()));
              j++;
          }
          while (query.next());
          query.first();
      }
  }
  ui->ttable->setHorizontalHeaderLabels(lblsV);

  //А теперь объединяем площадки в дни
  for (int k=0;k<DaysCount;k++)
  {
      QString cday=day.addDays(k).toString("dd.MM.yyyy dddd");
      SPANCOLS2(cday, 0+(ui->ttable->columnCount()/DaysCount)*k,(ui->ttable->columnCount()/DaysCount)-1+placesCount*k);
  }
}


