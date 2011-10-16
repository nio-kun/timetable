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


#define SPANCOLS3(txt,start,stop) \
 if (!hv->spanCols(QString(txt),start,stop))\
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
     hv = new HMultiHeader (tw,Qt::Vertical);
     tw->setVerticalHeader(hv);
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
    QSqlQuery query;
    query.exec("select isadmin from users where login='"+db.userName()+"'");
    query.next();
    if (query.value(0).toInt()){
        places s(&db);
        s.exec();
        SetDays(Days);
    }else{
        QMessageBox::critical(0,tr("Error!"),tr("You have no right to edit platforms!"));
    }
}

void MainWindow::on_action_4_triggered()
{

    QSqlQuery query;
    query.exec("select isadmin from users where login='"+db.userName()+"'");
    query.next();
    if (query.value(0).toInt()){
        users s(&db);
        s.exec();
    }else{
        QMessageBox::critical(0,tr("Error!"),tr("You have no right to edit users!"));
    }
}

void MainWindow::on_action_5_triggered()
{

    QSqlQuery query;
    query.exec("select isadmin from users where login='"+db.userName()+"'");
    query.next();
    if (query.value(0).toInt()){
        services s(&db);
        s.exec();
    }else{
        QMessageBox::critical(0,tr("Error!"),tr("You have no right to edit services!"));
    }
}


void MainWindow::on_action_6_triggered()
{
    authorization *s = new authorization;
    s->show();
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
        hv->reset();
}

void MainWindow::onOneDay(){Days=1; SetDays(1);}
void MainWindow::onTwoDays(){Days=2; SetDays(2);}
void MainWindow::onThreeDays(){Days=3; SetDays(3);}
void MainWindow::onWeek(){Days=7; SetDays(7);}

//Главная функция, которая рисует дни
void MainWindow::SetDays(int DaysCount){
    ClearTTable(); //Очищаем таблицу
    QStringList lblsV; // Массивы заголовков
    QStringList lblsH; // строк и столбцов
    int placesCount;  //Число площадок
    int beginRow, addedRows =0; //Начальная строка объединения и число дополнительно вставленных строчек

    if (db.isOpen()){
      QSqlQuery query, subq, subq2;

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
      ui->ttable->setHorizontalHeaderLabels(lblsV);

      //Узнаём рабочее время
      QSqlQuery q2;
      q2.exec("select value from settings where name='work_start_time'"); q2.first();
      int work_start_time=q2.value(0).toInt();
      q2.exec("select value from settings where name='work_end_time'"); q2.first();
      int work_end_time=q2.value(0).toInt();

      //Узнаём обеденное время
      QSqlQuery queryD;
      queryD.exec("select value from settings where name='dinner_start_time'"); queryD.first();
      int dinner_start_time=queryD.value(0).toInt();
      queryD.exec("select value from settings where name='dinner_end_time'"); queryD.first();
      int dinner_end_time=queryD.value(0).toInt();

      int hr;
      for (hr=work_start_time; hr<=work_end_time; hr++) {
          //Добавляем строчку часа
          ui->ttable->insertRow(ui->ttable->rowCount());
          beginRow=ui->ttable->rowCount()-1;
          addedRows=0;
          lblsH.append(QString("%1:00").arg(hr));

          //Смотрим, не обеденное ли сейчас время?
         if (hr>=dinner_start_time && hr<dinner_end_time && dinner_start_time<dinner_end_time ){
              //Обеденное - закрашиваем строчку цветом обеда
                            for (int j=0; j<ui->ttable->columnCount(); j++){
                            QTableWidgetItem *newItem1 = new QTableWidgetItem("");
                            newItem1->setBackgroundColor(dinner_color);
                            newItem1->setStatusTip("dt");
                            newItem1->setToolTip(tr("Dinner"));
                            ui->ttable->setItem(ui->ttable->rowCount()-1,j, newItem1);
                    }
                } else {

              for (int dd=0; dd<DaysCount; dd++){
              //Добавляем в строчку часа закрашенные ячейки
              //Получаем список площадок, на которых работы начинаются в этот час в i-й день.
                  query.exec("select place_id, client_id, service_id, date, TIME(date), record_id, hours from ttable where DATE(date)='"+ day.addDays(dd).toString("yyyy-MM-dd") +"' and TIME(date)='"+QTime::fromString("00:00:00").addSecs(3600*hr).toString("hh:mm:ss")+"'");
                  while (query.next()) {
                  if (QTime::fromString(query.value(4).toString()).toString("h:mm:ss")==QString("%1:00:00").arg(hr)){
                  //Получаем id площадки и вычисляем её положение среди столбцов
                  QSqlQuery plname;
                  plname.exec("select name, color from places where place_id="+query.value(0).toString()); plname.first();
                  int col=0;
                  for (int i=0+(ui->ttable->columnCount()/DaysCount)*dd; i<0+(ui->ttable->columnCount()/DaysCount)*dd+placesCount; i++)
                      if(lblsV.value(i)==plname.value(0).toString()) col=i;
                  //Создаём закрашенную ячейку
                  //Убираем заголовок ячейки из массива - он попадёт в объединённый заголовок
                  lblsH.removeLast(); lblsH.append("");
                  subq.exec("select * from clients where client_id="+query.value(1).toString()+";"); subq.first();
                  subq2.exec("select * from services where service_id="+query.value(2).toString()+";"); subq2.first();
                  QString ttip = query.value(4).toString()+"\n"+subq.value(1).toString()+"\n"+subq2.value(1).toString()+"\n"+subq.value(3).toString()+"\n"+subq.value(2).toString();
                  QColor colr = plname.value(1).toString();
                  QTableWidgetItem *newItem = new QTableWidgetItem();
                  newItem->setBackgroundColor(colr);
                  newItem->setToolTip(ttip);
                  newItem->setStatusTip(query.value(5).toString());
                  ui->ttable->setItem(beginRow,col, newItem);
                  //Добавляем дополнительную строчку
                  ui->ttable->insertRow(ui->ttable->rowCount());
                  lblsH.append("");
                  addedRows++;
                  //Делаем объединение ячеек
                  for (int ds=0; ds<DaysCount; ds++)
                  ui->ttable->setSpan(ui->ttable->rowCount()-1, 0+(ui->ttable->columnCount()/DaysCount)*ds,1,placesCount);
                  QTableWidgetItem * nitm = new QTableWidgetItem (subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
                  nitm->setBackgroundColor("#ffffff");
                  nitm->setStatusTip("ac");
                  ui->ttable->setItem(ui->ttable->rowCount()-1, 0+(ui->ttable->columnCount()/DaysCount)*dd, nitm);
                 }else if(
                           (QTime::fromString(QString("%1:00:00").arg(hr))>QTime::fromString(query.value(4).toString()))
                           &&(QTime::fromString(QString("%1:00:00").arg(hr))<QTime::fromString(query.value(4).toString()).addSecs(3600*query.value(6).toInt()))
                                                                                               ) {
                      //Просто заливаем ячейку
                      //Получаем id площадки и вычисляем её положение среди столбцов
                      QSqlQuery plname;
                      plname.exec("select name, color from places where place_id="+query.value(0).toString()); plname.first();
                      int col=0;
                      for (int i=0+(ui->ttable->columnCount()/DaysCount)*dd; i<0+(ui->ttable->columnCount()/DaysCount)*dd+placesCount; i++)
                          if(lblsV.value(i)==plname.value(0).toString())
                              col=i;
                      subq.exec("select * from clients where client_id="+query.value(1).toString()+";"); subq.first();
                      subq2.exec("select * from services where service_id="+query.value(2).toString()+";"); subq2.first();
                      QString ttip = query.value(4).toString()+"\n"+subq.value(1).toString()+"\n"+subq2.value(1).toString()+"\n"+subq.value(3).toString()+"\n"+subq.value(2).toString();
                      QColor colr = plname.value(1).toString();
                      QTableWidgetItem *newItem = new QTableWidgetItem();
                      newItem->setBackgroundColor(colr);
                      newItem->setToolTip(ttip);
                      newItem->setStatusTip(query.value(5).toString());
                      ui->ttable->setItem(ui->ttable->rowCount()-1,col, newItem);

                  };

              };
          };
          };
          //Объединяем горизонтальные заголовки
         if (addedRows>0) SPANCOLS3 (QString("%1:00").arg(hr),beginRow,beginRow+addedRows);
      };
      ui->ttable->setVerticalHeaderLabels(lblsH);





      //Добавим заголовки занятых часов.
   /*    int jj=0;
      for (int k=0;k<DaysCount;k++){
          query.first();
          do {
              q.exec("select TIME(date), client_id, service_id, hours, record_id from ttable where place_id="+query.value(0).toString()+" and DATE(date)='"+day.addDays(k).toString("yyyy-MM-dd")+"' order by date");
              if (q.size()>0){
              q.first();
              addedRows = 0;
              do {
                  int row= q.value(0).toString().left(2).toInt()-8;
                  QColor colr(query.value(2).toString());
                  //Вписываем данные
                  //Сначала считываем их из таблицы

                  //QTableWidgetItem *newItem = new QTableWidgetItem(subq.value(1).toString());

                  //Добавим дополнительную строчку
                  ui->ttable->insertRow(row+1);
                  for (int ds=0; ds<DaysCount; ds++)
                  ui->ttable->setSpan(row+1, 0+(ui->ttable->columnCount()/DaysCount)*ds,1,placesCount);


                  QTableWidgetItem * nitm = new QTableWidgetItem (q.value(0).toString()+" "+subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
                  nitm->setBackgroundColor("#ffffff");
                  nitm->setStatusTip("ac");
                  ui->ttable->setItem(row+1, jj, nitm);
                  addedRows++;


                  //Заливаем фоном занятое время
                  int addcell=0;
                  for (int m=1;m<q.value(3).toInt();m++){
                      if (ui->ttable->item(row+m+1,jj)&&(ui->ttable->item(row+m+1,jj)->statusTip()=="dt")) addcell=1;
                  QTableWidgetItem *bg = new QTableWidgetItem();
                  bg->setBackgroundColor(colr);
                  bg->setToolTip(ttip);
                  bg->setStatusTip(q.value(4).toString());
                  ui->ttable->setItem(row+m+addcell+1,jj, bg);
                  }
                  //    SPANCOLS3 ("122",row,row+1);
              } while (q.next());
              };
              jj++;
          }
          while (query.next());
      }
      jj=0;


//  [===========]\
//  |^^^водка^^^||""\\_,_
//  |___________||___|__|)     <-----Это грузовик с водкой
//   (@)(@)""""(@)(@)**(@)



                    for (int ds=0; ds<DaysCount; ds++) {
                    ui->ttable->setSpan(h+1, 0+(ui->ttable->columnCount()/DaysCount)*ds,1,placesCount);
                    QTableWidgetItem * nitm = new QTableWidgetItem ("");
                    nitm->setBackgroundColor("#ffffff");
                    nitm->setStatusTip("eac");
                    ui->ttable->setItem(h+1, 0+(ui->ttable->columnCount()/DaysCount)*ds, nitm);
                    };

                    QTableWidgetItem * nitm = new QTableWidgetItem (QString("%1").arg(h));
                    ui->ttable->setItem(h+1,j, nitm);

                    addedRows++;

                }
              /* if (ui->ttable->item(h+addedRows-work_start_time,0+(ui->ttable->columnCount()/DaysCount)*k)
                        && ui->ttable->item(h+addedRows-work_start_time,0+(ui->ttable->columnCount()/DaysCount)*k)->statusTip()=="eac"){
                };

            };
        };

        /*

      if ( ui->ttable->item(row+1,0+(ui->ttable->columnCount()/DaysCount)*k)
           && ui->ttable->item(row+1,0+(ui->ttable->columnCount()/DaysCount)*k)->statusTip()=="eac") {
         ui->ttable->item(row+1,0+(ui->ttable->columnCount()/DaysCount)*k)->setText(subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
         ui->ttable->item(row+1,0+(ui->ttable->columnCount()/DaysCount)*k)->setTextColor(query.value(2).toString());
         ui->ttable->item(row+1,0+(ui->ttable->columnCount()/DaysCount)*k)->setStatusTip("ac");

      } else {
          //Добавим строчки занятых часов
              ui->ttable->insertRow(row+addedRows);
          //Добавим объединение для всех ячеек строки
              for (int ds=0; ds<DaysCount; ds++) {
              ui->ttable->setSpan(row+1+addedRows, 0+(ui->ttable->columnCount()/DaysCount)*ds,1,placesCount);
              QTableWidgetItem * nitm = new QTableWidgetItem ("");
              nitm->setBackgroundColor("#ffffff");
              nitm->setStatusTip("eac");
              ui->ttable->setItem(row+1+addedRows, 0+(ui->ttable->columnCount()/DaysCount)*ds, nitm);
              };
      ui->ttable->item(row+1+addedRows,0+(ui->ttable->columnCount()/DaysCount)*k)->setText(subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
      ui->ttable->item(row+1+addedRows,0+(ui->ttable->columnCount()/DaysCount)*k)->setTextColor(query.value(2).toString());
      addedRows++;
      };

    //};

      //////////////////////////////////
  }
*/



  //А теперь объединяем площадки в дни

      for (int k=0;k<DaysCount;k++){
          QString cday=day.addDays(k).toString("dd.MM.yyyy dddd");
          SPANCOLS2(cday, 0+(ui->ttable->columnCount()/DaysCount)*k,(ui->ttable->columnCount()/DaysCount)-1+(placesCount*k));
      }
    ui->ttable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
};
}


void MainWindow::on_ttable_cellDoubleClicked(int row, int column)
{
    if (ui->ttable->item(row,column)){
       //Ячейка уже занята

        //Проверяем, не обеденное ли это время
        if (ui->ttable->item(row, column)->statusTip()=="dt") {
            QMessageBox::critical(0,tr("Error!"),tr("You can't work at dinner time!"));
        } else {
        if(QMessageBox::question(0,tr("Confirm"),tr("Are you really want to insert another work in this cell?"),3,4,0)==3){
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
