#ifndef ORDER_DETAILS_H
#define ORDER_DETAILS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>


namespace Ui {
    class order_details;
}

class order_details : public QDialog
{
    Q_OBJECT

public:
    explicit order_details(QWidget *parent = 0);
    explicit order_details(QSqlDatabase *db, QWidget *parent = 0);
    ~order_details();

private:
    Ui::order_details *ui;
};

#endif // ORDER_DETAILS_H
