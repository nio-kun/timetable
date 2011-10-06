#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QModelIndex>
#include "mheader.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_2_triggered();
    void on_action_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();
    void on_action_6_triggered();
    void on_ttable_doubleClicked(QModelIndex index);


//private Q_SLOTS:
   void MakeToolbars();
   void ClearTTable();
   void onPrev();
   void onNext();
   void onOneDay();
   void onTwoDays();
   void onThreeDays();
   void onWeek();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    HMultiHeader *h;
    QDate day;
    QAction *prevAct;
    QAction *nextAct;
    QAction *onedayAct;
    QAction *twodaysAct;
    QAction *threedaysAct;
    QAction *weekAct;
};

#endif // MAINWINDOW_H
