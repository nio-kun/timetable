#ifndef PLACES_H
#define PLACES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
    class places;
}

class places : public QDialog
{
    Q_OBJECT

public:
    explicit places(QWidget *parent = 0);
    explicit places(QSqlDatabase *kept_db, QWidget *parent = 0);
    ~places();

private slots:
    void on_pushButton_clicked();

private:
    Ui::places *ui;
    QSqlDatabase *db;
};

#endif // PLACES_H
