#ifndef PLACES_H
#define PLACES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QColor>
#include <QColorDialog>
#include <QPixmap>

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

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_2_clicked();

//    void accept();

    void reject();

    void on_lineEdit_3_textEdited(QString str);

    void on_checkBox_stateChanged(int st);

    void on_lineEdit_3_editingFinished();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void closeEvent(QCloseEvent *event);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


private:
    Ui::places *ui;
    QSqlDatabase *db;
    QVector<int> listvector;
};

#endif // PLACES_H
