#ifndef ORDER_DETAILS_H
#define ORDER_DETAILS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>


namespace Ui {
    class order_details;
}

class order_details : public QDialog
{
    Q_OBJECT

public:
    explicit order_details(QWidget *parent = 0);
    explicit order_details(QSqlDatabase *keptdb, int plc, QDateTime dt, QWidget *parent = 0);
    ~order_details();

private slots:
    void on_buttonBox_accepted();

    void on_checkBox_stateChanged(int arg1);

    void on_lineEdit_5_editingFinished();

private:
    Ui::order_details *ui;
    QSqlDatabase *db;
    QDateTime destdate;
    int place;
};

#endif // ORDER_DETAILS_H
