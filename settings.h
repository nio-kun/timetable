#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>

namespace Ui {
    class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    explicit settings(QSqlDatabase *kept_db, bool hide_dinner =false, QWidget *parent = 0);
    ~settings();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_3_lostFocus();

    void on_lineEdit_4_lostFocus();

private:
    Ui::settings *ui;
    QSqlDatabase *db;
    void check_dinner_time(QLineEdit *lineEdit);
};

#endif // SETTINGS_H
