#include <QtGui/QApplication>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "authorization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    authorization au;

    au.show();
    //w.show();

    return a.exec();
}
