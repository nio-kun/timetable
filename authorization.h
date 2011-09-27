#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QAbstractButton>
#include <QSqlDatabase>

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
    void on_buttonBox_clicked(QAbstractButton* button);

    void on_buttonBox_accepted();

private:
    Ui::authorization *ui;
    QSqlDatabase *db;
};

#endif // AUTHORIZATION_H
