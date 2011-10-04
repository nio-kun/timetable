#ifndef SERVICES_H
#define SERVICES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
    class services;
}

class services : public QDialog
{
    Q_OBJECT

public:
    explicit services(QWidget *parent = 0);
    explicit services(QSqlDatabase *kept_db, QWidget *parent = 0);
    ~services();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void closeEvent(QCloseEvent *event);

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::services *ui;
    QSqlDatabase *db;
    QVector<int> listvector;
};

#endif // SERVICES_H
