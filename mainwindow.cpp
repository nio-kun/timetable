#include "mainwindow.h"
#include "settings.h"
#include "places.h"
#include "users.h"
#include "services.h"
#include "authorization.h"

#include "ui_mainwindow.h"
#include "authorization.h"
#include "mheader.h"


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

/*    QStringList lbls;
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
    ui->ttable->insertColumn(0);*/
/*    ui->ttable->insertRow(1);
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
*/
    //ui->ttable->setVerticalHeaderLabels(lbls);


 //QAbstractItemModel bsd;
 //bsd.insertRow(0);
 //bsd.insertRow(1);
 //bsd.insertColumn(0);
 //bsd.insertColumn(1);

 //bsd.
//
 //QHeaderView asd ;
 //asd.setModel(bsd);

 //ui->ttable->setVerticalHeader(asd);

    //ui->ttable->setVerticalHeader();

//    QStandardItem fff ("asdasdasd");
    //QStandardItem ffd ("123");

//QStandardItemModel ddd;
//ddd.appendRow(&fff);
//QHeaderView *asd = new  QHeaderView(Qt::Vertical,ui->ttable) ;
//asd->setModel(&ddd);
//ui->ttable->verticalHeader()->model()->index(0,0).data().toString();
//QMessageBox::information(0, "Kanji",ui->ttable->verticalHeader()->model()->index(0,0).data().toString(), 0,0,0);
//ui->ttable->verticalHeader()->model()->index(1,1).data()="asd";

    /*
QTableView tv;
    QStandardItemModel *model = new QStandardItemModel(5,5, this);
    QStandardItem *aaa;
    for (int i=0;i!=5;++i) {
        for (int j=0;j!=5;++j) {

//            model->setItem(i,j, new QStandardItem(tr("item %1").arg(j+i*5)));
            aaa=new QStandardItem(1,1);
            aaa->setChild(0,0,new QStandardItem(tr("item %1").arg(j+i*5)));
            aaa->setChild(1,0,new QStandardItem(tr("item %1").arg(j+i*5)));
            model->setItem(i,j, aaa);
        }
    }
    tv.setModel(model);

    QHeaderView *header_1 = new QHeaderView(Qt::Horizontal, &tv);
    QStandardItemModel *header_model_1 = new QStandardItemModel(0,0, header_1);
     header_model_1->setHorizontalHeaderLabels(QStringList()<<"A"<<"B"<<"C"<<"D"<<"E");
    header_1->setModel(header_model_1);
      tv.setHorizontalHeader(header_1);
      tv.show();
*/

/*
    TimeModel em;
    //QTableView tv;
    HierarchicalHeaderView* hv=new HierarchicalHeaderView(Qt::Horizontal, ui->tableView);
hv->setHighlightSections(true);
hv->setClickable(true);
    ui->tableView->setHorizontalHeader(hv);
    hv=new HierarchicalHeaderView(Qt::Vertical, ui->tableView);
hv->setHighlightSections(true);
hv->setClickable(true);
ui->tableView->setVerticalHeader(hv);

    ui->tableView->setModel(&em);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->repaint();
    ui->tableView->hide();
    ui->tableView->show();
*/
/*
    TimeModel em;
    QTableView tv (this);
    HierarchicalHeaderView* hv=new HierarchicalHeaderView(Qt::Horizontal, &tv);
hv->setHighlightSections(true);
hv->setClickable(true);
    tv.setHorizontalHeader(hv);
    hv=new HierarchicalHeaderView(Qt::Vertical, &tv);
hv->setHighlightSections(true);
hv->setClickable(true);
tv.setVerticalHeader(hv);

    tv.setModel(&em);
    tv.resizeColumnsToContents();
    tv.resizeRowsToContents();*/
    //tv.show();
    //ui->tableView=&tv;
   //show();



/*

QStandardItemModel headerModel;
      QStandardItem* rootItem = new QStandardItem("root");
      QList<QStandardItem*> l;

      QStandardItem* rotatedTextCell=new QStandardItem("Rotated text");
      rotatedTextCell->setData(1, Qt::UserRole);
      l.push_back(rotatedTextCell);
      rootItem->appendColumn(l);

      l.clear();

      QStandardItem* cell=new QStandardItem("level 2");
      l.push_back(cell);
      rootItem->appendColumn(l);

      l.clear();

      l.push_back(new QStandardItem("level 3"));
      cell->appendColumn(l);

      l.clear();

      l.push_back(new QStandardItem("level 3"));
      cell->appendColumn(l);

      l.clear();

      l.push_back(new QStandardItem("level 2"));
      rootItem->appendColumn(l);

      headerModel.setItem(0, 0, rootItem);
header_1->setModel(&headerModel);
ui->tableView->setHorizontalHeader(header_1);
//ui->tableView->setHorizontalHeader(&headerModel);
ui->tableView->show();*/










    int nRows=15, nCols=15;

    QTableWidget *tw = ui->ttable;

//set data
//    for (int i=0; i<nRows; i++)
//     for (int j=0; j<nCols; j++)
      //tw->setItem(i,j,new QTableWidgetItem(QString("Item %1,%2").arg(i).arg(j)));

//set header text
    for (int i=0; i<nCols; i++)
        tw->setHorizontalHeaderItem(i,new QTableWidgetItem(QString("Text %1").arg(i)));

    for (int i=0; i<nRows; i++)
        tw->setVerticalHeaderItem(i,new QTableWidgetItem(QString("Text %1").arg(i)));

/*    HMultiHeader *h = new HMultiHeader(tw);
    tw->setHorizontalHeader(h);*/

//set spans
/*    SPANCOLS("SPANNED HEADER",0,1);
    SPANCOLS("SPANNED HEADER",3,12);

    SPANCOLS("SUB SPANNED HEADER",3,6);
    SPANCOLS("SUB SPANNED HEADER",8,11);

    SPANCOLS("SUB SUB SPANNED HEADER",3,4);
    SPANCOLS("SUB SUB SPANNED HEADER",5,6);

    SPANCOLS("SUB SUB SPANNED HEADER",8,9);
    SPANCOLS("SUB SUB SPANNED HEADER",10,11);
*/

    HMultiHeader *h = new HMultiHeader(tw, Qt::Vertical);
    tw->setVerticalHeader(h);

//    SPANCOLS("SPANNED HEADER",0,1);
//    SPANCOLS("SPANNED HEADER",3,12);

//    SPANCOLS("SUB SPANNED HEADER",3,6);
//    SPANCOLS("SUB SPANNED HEADER",8,11);

//    SPANCOLS("SUB SUB SPANNED HEADER",3,4);
//    SPANCOLS("SUB SUB SPANNED HEADER",5,6);

//    SPANCOLS("SUB SUB SPANNED HEADER",8,9);
//    SPANCOLS("SUB SUB SPANNED HEADER",10,11);

      SPANCOLS2("09:00",0,3);
      SPANCOLS2("10:00",4,7);
      SPANCOLS2("11:00",8,10);
      SPANCOLS2("12:00",11,14);



//    h->spanCols(QString("%1 %2-%3").arg("SPANNED HEADER").arg(0).arg(1),0,1);

//    tw->resizeColumnsToContents();
//    tw->setCurrentCell(0,0);

//    tw->showMaximized();















    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("timetable");

    authorization a(&db);
    a.exec();
//QMessageBox::information(0, "Kanji",ui->ttable->verticalHeader()->model()->index(1,1).data().toString(), 0,0,0);
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
    services s;
    s.exec();
}

void MainWindow::on_pushButton_clicked()
{


}

void MainWindow::on_action_6_triggered()
{
    authorization *s = new authorization;
    s->show();
//ui->tableView->model()->setItemData()
}
