#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QModelIndex>
#include <QColor>
#include <QDate>

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

//private Q_SLOTS:
   void MakeToolbars();
   void ClearTTable();
   void SetDays(int DaysCount);
   void onPrev();
   void onNext();
   void onOneDay();
   void onTwoDays();
   void onThreeDays();
   void onWeek();
   void on_ttable_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QDate day;
    int Days;
    QAction *prevAct;
    QAction *nextAct;
    QAction *onedayAct;
    QAction *twodaysAct;
    QAction *threedaysAct;
    QAction *weekAct;
    QColor  dinner_color;
};

#endif // MAINWINDOW_H
