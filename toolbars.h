#include "mainwindow.h"
#ifndef TOOLBARS_H
#define TOOLBARS_H

void MainWindow::MakeToolbars()
{
    prevAct = new QAction(tr("Previous day"), this);
    prevAct->setIcon(QIcon::fromTheme("go-previous", QIcon(qApp->applicationDirPath()+"/../share/timetable/go-previous.png")));
    prevAct->setShortcut(Qt::CTRL+Qt::Key_Left);
    connect(prevAct, SIGNAL(triggered()), this, SLOT(onPrev()));
    ui->mainToolBar->addAction(prevAct);

    nextAct = new QAction(tr("Next day"), this);
    nextAct->setIcon(QIcon::fromTheme("go-next", QIcon(qApp->applicationDirPath()+"/../share/timetable/go-next.png")));
    nextAct->setShortcut(Qt::CTRL+Qt::Key_Right);
    connect(nextAct, SIGNAL(triggered()), this, SLOT(onNext()));
    ui->mainToolBar->addAction(nextAct);
    ui->mainToolBar->addSeparator();

    onedayAct = new QAction(tr("One day"), this);
    onedayAct->setText("1");
    onedayAct->setShortcut(Qt::CTRL+Qt::Key_1);
    connect(onedayAct, SIGNAL(triggered()), this, SLOT(onOneDay()));
    ui->mainToolBar->addAction(onedayAct);


    twodaysAct = new QAction(tr("Two days"), this);
    twodaysAct->setText("2");
    twodaysAct->setShortcut(Qt::CTRL+Qt::Key_2);
    connect(twodaysAct, SIGNAL(triggered()), this, SLOT(onTwoDays()));
    ui->mainToolBar->addAction(twodaysAct);

    threedaysAct = new QAction(tr("Three days"), this);
    threedaysAct->setText("3");
    threedaysAct->setShortcut(Qt::CTRL+Qt::Key_3);
    connect(threedaysAct, SIGNAL(triggered()), this, SLOT(onThreeDays()));
    ui->mainToolBar->addAction(threedaysAct);

    weekAct = new QAction(tr("One week"), this);
    weekAct->setText("7");
    weekAct->setShortcut(Qt::CTRL+Qt::Key_7);
    connect(weekAct, SIGNAL(triggered()), this, SLOT(onWeek()));
    ui->mainToolBar->addAction(weekAct);

}

#endif // TOOLBARS_H
