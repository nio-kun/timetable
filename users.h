#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
    class users;
}

class users : public QDialog
{
    Q_OBJECT

public:
    explicit users(QWidget *parent = 0);
    explicit users(QSqlDatabase *kept_db, QWidget *parent = 0);
    ~users();

private slots:


    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void closeEvent(QCloseEvent *event);

    void on_lineEdit_3_textEdited(QString );

    void on_lineEdit_textEdited(QString );

    void on_lineEdit_2_textEdited(QString );

private:
    Ui::users *ui;
    QSqlDatabase *db;
    QVector<int> listvector;
    bool adduser;
    bool saved;
};

#endif // USERS_H
