#include "mainwindow.h"
#include "settings.h"
#include "places.h"
#include "users.h"
#include "services.h"
#include "authorization.h"
#include "order_details.h"
#include "ui_mainwindow.h"
#include "authorization.h"
#include "toolbars.h"
#include <QBrush>

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

    ui->ttable->setStyleSheet("QTableView { gridline-color: black; }" );
    ui->ttable->horizontalHeader()->hide();
    ui->ttable->verticalHeader()->hide();

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
}

void MainWindow::onOneDay(){Days=1; SetDays(1);}
void MainWindow::onTwoDays(){Days=2; SetDays(2);}
void MainWindow::onThreeDays(){Days=3; SetDays(3);}
void MainWindow::onWeek(){Days=7; SetDays(7);}

//Главная функция, которая рисует дни
void MainWindow::SetDays(int DaysCount){
    ClearTTable(); //Очищаем таблицу

    ui->ttable->insertRow(0);      // Две строчки
    ui->ttable->insertRow(0);      // и столбец для
    ui->ttable->insertColumn(0);   // имитации заголовков

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
          int j=1;
          // Забиваем список площадок в массив заголовков столько раз,
          // сколько требуется показать дней
          do {
              ui->ttable->insertColumn(j);
              QTableWidgetItem * nitm = new QTableWidgetItem (query.value(1).toString());
              nitm->setBackgroundColor("lightgray");
              nitm->setStatusTip("ac");
              ui->ttable->setItem(1,j, nitm);

              j++;
          }
          while (query.next());
          query.first();
      }

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

          //Добавляем имитацию заголовка
          QTableWidgetItem * nitm = new QTableWidgetItem (QString("%1:00").arg(hr));
          nitm->setBackgroundColor("lightgray");
          nitm->setStatusTip("ac");
          ui->ttable->setItem(beginRow, 0, nitm);

              //Смотрим, не обеденное ли сейчас время?
         if (hr>=dinner_start_time && hr<dinner_end_time && dinner_start_time<dinner_end_time ){
              //Обеденное - закрашиваем строчку цветом обеда
                            for (int j=1; j<ui->ttable->columnCount(); j++){
                            QTableWidgetItem *newItem1 = new QTableWidgetItem("");
                            newItem1->setBackgroundColor(dinner_color);
                            newItem1->setStatusTip("dt");
                            newItem1->setToolTip(tr("Dinner"));
                            ui->ttable->setItem(ui->ttable->rowCount()-1,j, newItem1);
                    }
                } else {

             //Время не обеденное, но учитывать обед всё равно надо
             //int dinnerlap=0;
             //if (hr>=dinner_end_time) dinnerlap=dinner_end_time-dinner_start_time;

              for (int dd=0; dd<DaysCount; dd++){
              //Добавляем в строчку часа закрашенные ячейки
              //Получаем список площадок, на которых работы начинаются в этот час в i-й день.
                  query.exec("select place_id, client_id, service_id, date, TIME(date), record_id, hours from ttable where DATE(date)='"+ day.addDays(dd).toString("yyyy-MM-dd") +"' and TIME(date)<='"+QTime::fromString("00:00:00").addSecs(3600*hr).toString("hh:mm:ss")+"'");
                  while (query.next()) {
                  if (QTime::fromString(query.value(4).toString()).toString("h:mm:ss")==QString("%1:00:00").arg(hr)){
                  //Получаем id площадки и вычисляем её положение среди столбцов
                  QSqlQuery plname;
                  plname.exec("select name, color from places where place_id="+query.value(0).toString()); plname.first();
                  int col=1;
                  for (int i=1+(ui->ttable->columnCount()/DaysCount)*dd; i<1+(ui->ttable->columnCount()/DaysCount)*dd+placesCount; i++)
                      if(ui->ttable->item(1,i)->text()==plname.value(0).toString()) col=i;
                  //Создаём закрашенную ячейку
                  //Убираем заголовок ячейки из массива - он попадёт в объединённый заголовок
                           subq.exec("select * from clients where client_id="+query.value(1).toString()+";"); subq.first();
                  subq2.exec("select * from services where service_id="+query.value(2).toString()+";"); subq2.first();
                  QString ttip = query.value(4).toString()+"\n"+subq.value(1).toString()+"\n"+subq2.value(1).toString()+"\n"+subq.value(3).toString()+"\n"+subq.value(2).toString();
                  QColor colr = plname.value(1).toString();
                  QTableWidgetItem *newItem = new QTableWidgetItem();
                  newItem->setBackgroundColor(colr);
                  newItem->setToolTip(ttip);
                  newItem->setStatusTip(query.value(5).toString());
                  ui->ttable->setItem(beginRow,col, newItem);
                  bool arfilled=false;
                  if (addedRows>0){
                      for (int m=1; m<=addedRows; m++){
                          if (!ui->ttable->item(beginRow+m, 1+(ui->ttable->columnCount()/DaysCount)*dd )){
                              //Новую строчку добавлять не надо, пишем в найденной пустой
                              QTableWidgetItem * nitm = new QTableWidgetItem (subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
                              nitm->setBackgroundColor("#ffffff");
                              nitm->setStatusTip("ac");
                              ui->ttable->setItem(beginRow+m, 1+(ui->ttable->columnCount()/DaysCount)*dd, nitm);
                              arfilled=true;
                              break;
                          }
                        }
                      };
                      if (!arfilled){
                  //Добавляем дополнительную строчку
                  ui->ttable->insertRow(ui->ttable->rowCount());
                  addedRows++;
                  //Делаем объединение ячеек
                  for (int ds=0; ds<DaysCount; ds++)
                  ui->ttable->setSpan(ui->ttable->rowCount()-1, 1+(ui->ttable->columnCount()/DaysCount)*ds,1,placesCount);
                  QTableWidgetItem * nitm = new QTableWidgetItem (subq.value(1).toString()+" "+subq2.value(1).toString()+" "+subq.value(3).toString()+" "+subq.value(2).toString());
                  nitm->setBackgroundColor("#ffffff");
                  nitm->setStatusTip("ac");
                  ui->ttable->setItem(ui->ttable->rowCount()-1, 1+(ui->ttable->columnCount()/DaysCount)*dd, nitm);
                          };
                 }else if(
                          (hr>QTime::fromString(query.value(4).toString()).toString("hh").toInt())
                          &&(hr<=(QTime::fromString(query.value(4).toString()).toString("hh").toInt() + query.value(6).toInt()))
                                                                                               ) {
                      //Просто заливаем ячейку
                      //Получаем id площадки и вычисляем её положение среди столбцов
                      QSqlQuery plname;
                      plname.exec("select name, color from places where place_id="+query.value(0).toString()); plname.first();
                      int col=1;
                      for (int i=1+(ui->ttable->columnCount()/DaysCount)*dd; i<1+(ui->ttable->columnCount()/DaysCount)*dd+placesCount; i++)
                          if(ui->ttable->item(1,i)->text()==plname.value(0).toString()) col=i;
                      subq.exec("select * from clients where client_id="+query.value(1).toString()+";"); subq.first();
                      subq2.exec("select * from services where service_id="+query.value(2).toString()+";"); subq2.first();
                      QString ttip = query.value(4).toString()+"\n"+subq.value(1).toString()+"\n"+subq2.value(1).toString()+"\n"+subq.value(3).toString()+"\n"+subq.value(2).toString();
                      QColor colr = plname.value(1).toString();
                      QTableWidgetItem *newItem = new QTableWidgetItem();
                      newItem->setBackgroundColor(colr);
                      newItem->setToolTip(ttip);
                      newItem->setStatusTip(query.value(5).toString());
                      ui->ttable->setItem(ui->ttable->rowCount()-1-addedRows,col, newItem);
                  };

              };
          };
          };
          //Объединяем горизонтальные заголовки в часы
          if (addedRows>0) ui->ttable->setSpan(beginRow, 0,addedRows+1,1);
      };

 //А теперь объединяем площадки в дни

      for (int k=0;k<DaysCount;k++){
          QString cday=day.addDays(k).toString("dd.MM.yyyy dddd");
          QTableWidgetItem * nitm = new QTableWidgetItem (cday);
          nitm->setBackgroundColor("lightgray");
          nitm->setStatusTip("ac");
          ui->ttable->setItem(0, 1+(ui->ttable->columnCount()/DaysCount)*k, nitm);
          ui->ttable->setSpan(0, 1+(ui->ttable->columnCount()/DaysCount)*k,1,placesCount);
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
        }else if(ui->ttable->item(row, column)->statusTip()=="ac"){
            ; //В дополнительную строчку работы вставлять нельзя
        }else {


        if(QMessageBox::question(0,tr("Confirm"),tr("Are you really want to insert another work in this cell?"),3,4,0)==3){
            //Узнаём время
            QTime tme=QTime::fromString(ui->ttable->item(row,0)->text(),"h:mm");

            //Узнаём, на сколько часов нужно сократить работу
            QSqlQuery q;
            q.exec("select hours, date from ttable where record_id="+ui->ttable->item(row,column)->statusTip()); q.first();
            int hours=q.value(0).toInt(); QDateTime dat = q.value(1).toDateTime();
            int begin=dat.toString("HH").toInt();
            int tm= tme.toString("HH").toInt();

            //Здесь ещё нужно учесть обед
            QSqlQuery queryD;
            queryD.exec("select value from settings where name='dinner_start_time'"); queryD.first();
            int dinner_start_time=queryD.value(0).toInt();
            queryD.exec("select value from settings where name='dinner_end_time'"); queryD.first();
            int dinner_end_time=queryD.value(0).toInt();
            int dt=0;
            if (begin<dinner_start_time && (begin+hours)>dinner_end_time) dt=1;


            int delta=(hours+begin)-tm+dt;
            QVariant newHours=hours-delta;
            q.exec("update ttable set hours="+newHours.toString()+" where record_id="+ui->ttable->item(row,column)->statusTip());
            q.exec("select place_id from places where name='"+ui->ttable->item(1,column)->text()+"';");
            q.first();
            //Узнаём дату и время
            QDateTime data = QDateTime::fromString(day.addDays((column+1)/(ui->ttable->columnCount() / Days)).toString("dd.MM.yyyy")+" "+tme.toString("hh:mm:ss"), "dd.MM.yyyy hh:mm:ss");
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
        q.exec("select place_id from places where name='"+ui->ttable->item(1,column)->text()+"';");
        q.first();
    }
    //Узнаём дату и время
    QTime tme=QTime::fromString(ui->ttable->item(row,0)->text(),"h:mm");
    QDateTime data = QDateTime::fromString(day.addDays((column+1)/(ui->ttable->columnCount() / Days)).toString("dd.MM.yyyy")+" "+tme.toString("hh:mm:ss"), "dd.MM.yyyy hh:mm:ss");
   //Вызываем форму назначения
   order_details s(&db, q.value(0).toInt(), data);
   s.exec();
    SetDays(Days);
    }
}
