#include <QtGui/QApplication>
#include <QDate>
#include "mainwindow.h"
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator myTranslator;

    myTranslator.load(qApp->applicationDirPath()+"/timetable_" + QLocale::system().name());
    a.installTranslator(&myTranslator);

    QTranslator qtTranslator;
    qtTranslator.load(qApp->applicationDirPath()+"/qt_" + QLocale::system().name());
    a.installTranslator(&qtTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
