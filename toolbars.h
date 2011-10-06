#include "mainwindow.h"
#ifndef TOOLBARS_H
#define TOOLBARS_H

void MainWindow::MakeToolbars()
{
    prevAct = new QAction(tr("Previous day"), this);
    prevAct->setIcon(QIcon::fromTheme("go-previous", QIcon(qApp->applicationDirPath()+"/../share/mangaed/go-previous.png")));
    prevAct->setShortcut(Qt::CTRL+Qt::Key_Left);
    connect(prevAct, SIGNAL(triggered()), this, SLOT(onPrev()));
    ui->mainToolBar->addAction(prevAct);

    nextAct = new QAction(tr("Next day"), this);
    nextAct->setIcon(QIcon::fromTheme("go-next", QIcon(qApp->applicationDirPath()+"/../share/mangaed/go-next.png")));
    nextAct->setShortcut(Qt::CTRL+Qt::Key_Right);
    connect(nextAct, SIGNAL(triggered()), this, SLOT(onNext()));
    ui->mainToolBar->addAction(nextAct);
    ui->mainToolBar->addSeparator();

    onedayAct = new QAction(tr("One day"), this);
    onedayAct->setIcon(QIcon::fromTheme("office-calendar", QIcon(qApp->applicationDirPath()+"/../share/mangaed/go-next.png")));
    onedayAct->setShortcut(Qt::CTRL+Qt::Key_1);
    connect(onedayAct, SIGNAL(triggered()), this, SLOT(onOneDay()));
    ui->mainToolBar->addAction(onedayAct);


    /*
   void onOneDay();
   void onTwoDays();
   void onThreeDays();
   void onWeek();

*/
}

#endif // TOOLBARS_H
