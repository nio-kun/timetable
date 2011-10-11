#include "mainwindow.h"
#include "settings.h"
#include "places.h"
#include "users.h"
#include "services.h"
#include "authorization.h"
#include "order_details.h"
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
    tw->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
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

//Главная функция, которая рисует дни
void MainWindow::SetDays(int DaysCount){
    ClearTTable(); //Очищаем таблицу
    QStringList lblsV; //Массив заголовков
    int placesCount;  //Число площадок

  if (db.isOpen()){
      QSqlQuery query, q, subq, subq2;

      //Узнаём, сколько имеется площадок
      query.exec("select count(place_id) from places");
      query.first();
      placesCount= query.value(0).toInt();

      //Получаем список площадок
      query.exec("select place_id, name, color from places order by name");
      query.first();
      for (int k=0;k<DaysCount;k++){
          int j=0;
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

      //Добавим данные
       int jj=0;
      for (int k=0;k<DaysCount;k++){
          query.first();
          do {
              q.exec("select TIME(date), client_id, service_id, hours from ttable where place_id="+query.value(0).toString()+" and DATE(date)='"+day.addDays(k).toString("yyyy-MM-dd")+"' order by date");
              if (q.size()>0){
              q.first();
              do {
                  int row= q.value(0).toString().left(2).toInt()-8;
                  QColor colr(query.value(2).toString());
                  //Вписываем данные
                  //Сначала считываем их из таблицы
                  subq.exec("select * from clients where client_id="+q.value(1).toString()+";"); subq.first();
                  subq2.exec("select * from services where service_id="+q.value(2).toString()+";"); subq2.first();
                  QTableWidgetItem *newItem = new QTableWidgetItem(subq.value(1).toString());
                  if (DaysCount==1) newItem->setText(subq.value(1).toString()+" "+subq2.value(1).toString());
                  newItem->setBackgroundColor(colr);
                  QString ttip = subq.value(1).toString()+"\n"+subq2.value(1).toString()+"\n"+subq.value(3).toString()+"\n"+subq.value(2).toString();
                  newItem->setToolTip(ttip);
                  ui->ttable->setItem(row,jj, newItem);

                  //Заливаем фоном занятое время
                  for (int m=1;m<q.value(3).toInt();m++){
                  QTableWidgetItem *bg = new QTableWidgetItem();
                  bg->setBackgroundColor(colr);
                  bg->setToolTip(ttip);
                  ui->ttable->setItem(row+m,jj, bg);
                  }
              } while (q.next());
              };
              jj++;
          }
          while (query.next());
      }
  }
  ui->ttable->setHorizontalHeaderLabels(lblsV);

  //А теперь объединяем площадки в дни
  for (int k=0;k<DaysCount;k++)
  {
      QString cday=day.addDays(k).toString("dd.MM.yyyy dddd");
      SPANCOLS2(cday, 0+(ui->ttable->columnCount()/DaysCount)*k,(ui->ttable->columnCount()/DaysCount)-1+placesCount*k);
  }
  ui->ttable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}



void MainWindow::on_ttable_cellDoubleClicked(int row, int column)
{
    QSqlQuery q;

    //Узнаём номер площадки
    if (db.isOpen()){
        q.exec("select place_id from places where name='"+ui->ttable->horizontalHeaderItem(column)->text()+"';");
        q.first();
    }
    //Узнаём дату и время
    QDateTime data = QDateTime::fromString(day.addDays(column/(ui->ttable->columnCount() / Days)).toString("dd.MM.yyyy")+" "+QTime(8,0,0,0).addSecs(row*3600).toString("hh:mm:ss"), "dd.MM.yyyy hh:mm:ss");

    //Вызываем форму назначения
    order_details s(&db, q.value(0).toInt(), data);
    s.exec();
    SetDays(Days);
}
