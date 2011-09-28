#include <QtGui/QApplication>
#include "mainwindow.h"
#include "authorization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    authorization au;
w.show();
    return a.exec();
}
