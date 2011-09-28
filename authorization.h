#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QAbstractButton>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "mainwindow.h"

namespace Ui {
    class authorization;
}

class authorization : public QDialog
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = 0);
    explicit authorization(QSqlDatabase *kept_db, QWidget *parent = 0);

    ~authorization();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::authorization *ui;
    QSqlDatabase *db;
};

#endif // AUTHORIZATION_H
