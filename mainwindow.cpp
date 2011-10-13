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
#include <QBrush>


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

    dinner_color.setNamedColor("#00FF00");

    //Подключение к БД и авторизация
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("timetable");
    authorization a(&db,&dinner_color);
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
 settings s(&db, &dinner_color);
 s.exec();
}

void MainWindow::on_action_3_triggered()
{
    places s(&db);
    s.exec();
    SetDays(Days);
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
        for (int i=0;i=ui->ttable->columnCount();i++) ui->ttable->removeColumn(0);
        for (int i=0;i=ui->ttable->rowCount();i++) ui->ttable->removeRow(0);
        //Строки
        QStringList lblsH;
        for (int i=8;i<20;i++){
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

      int dinner_start_time=0;
      int dinner_end_time=0;

      if (db.isOpen()){
          QSqlQuery query;
          query.exec("select value from settings where name='dinner_start_time'");
          if (query.numRowsAffected()>0){
              query.next();
              dinner_start_time=query.value(0).toInt();
          }

          query.exec("select value from settings where name='dinner_end_time'");
          if (query.numRowsAffected()>0){
              query.next();
              dinner_end_time=query.value(0).toInt();
          }
          if (dinner_start_time && dinner_end_time && dinner_start_time<dinner_end_time ){
              for (int i=dinner_start_time; i<dinner_end_time; i++){

                  for (int j=0; j<ui->ttable->columnCount(); j++){
                      QTableWidgetItem *newItem1 = new QTableWidgetItem("");
                      newItem1->setBackgroundColor(dinner_color);
                      newItem1->setStatusTip("dt");
                      ui->ttable->setItem(i-8,j, newItem1);
                  }
              }
          }
      }

      //Добавим данные
       int jj=0;
      for (int k=0;k<DaysCount;k++){
          query.first();
          do {
              q.exec("select TIME(date), client_id, service_id, hours, record_id from ttable where place_id="+query.value(0).toString()+" and DATE(date)='"+day.addDays(k).toString("yyyy-MM-dd")+"' order by date");
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
                  newItem->setStatusTip(q.value(4).toString());
                  ui->ttable->setItem(row,jj, newItem);

                  //Заливаем фоном занятое время
                  for (int m=1;m<q.value(3).toInt();m++){
                  QTableWidgetItem *bg = new QTableWidgetItem();
                  bg->setBackgroundColor(colr);
                  bg->setToolTip(ttip);
                  bg->setStatusTip(q.value(4).toString());
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
      SPANCOLS2(cday, 0+(ui->ttable->columnCount()/DaysCount)*k,(ui->ttable->columnCount()/DaysCount)-1+(placesCount*k));
  }
  ui->ttable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}



void MainWindow::on_ttable_cellDoubleClicked(int row, int column)
{
    if (ui->ttable->item(row,column)){
       //Ячейка уже занята

        //Проверяем, не обеденное ли это время
        if (ui->ttable->item(row, column)->statusTip()=="dt") {
            QMessageBox::critical(0,"Error!","You can't work at dinner time!");
        } else {
        if(QMessageBox::question(0,"Confirm","Are you really want to insert another work in this cell?",3,4,0)==3){
            //Узнаём, на сколько часов нужно сократить работу
            QSqlQuery q;
            q.exec("select hours, date from ttable where record_id="+ui->ttable->item(row,column)->statusTip()); q.first();
            int hours=q.value(0).toInt(); QDateTime dat = q.value(1).toDateTime();
            int begin=dat.toString("HH").toInt();
            int delta=hours+((begin-8)-row);
            QVariant newHours=hours-delta;
            q.exec("update ttable set hours="+newHours.toString()+" where record_id="+ui->ttable->item(row,column)->statusTip());
            q.exec("select place_id from places where name='"+ui->ttable->horizontalHeaderItem(column)->text()+"';");
            q.first();
            QDateTime data = QDateTime::fromString(day.addDays(column/(ui->ttable->columnCount() / Days)).toString("dd.MM.yyyy")+" "+QTime(8,0,0,0).addSecs(row*3600).toString("hh:mm:ss"), "dd.MM.yyyy hh:mm:ss");
            //Вызываем форму назначения
            order_details s(&db, q.value(0).toInt(), data);
            s.exec();
            SetDays(Days);
            }
        }
    }else{
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
}
