#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QAbstractButton>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>


namespace Ui {
    class authorization;
}

class authorization : public QDialog
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = 0);
    explicit authorization(QSqlDatabase *kept_db, QColor *d_color, QWidget *parent = 0);

    ~authorization();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

    void on_pushButton_3_clicked();

    void on_authorization_rejected();
    void reject();

private:
    Ui::authorization *ui;
    QSqlDatabase *db;
    void  read_properties();
    QColor *dinner_color;
};

#endif // AUTHORIZATION_H
