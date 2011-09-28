#ifndef PLACES_H
#define PLACES_H

#include <QDialog>

namespace Ui {
    class places;
}

class places : public QDialog
{
    Q_OBJECT

public:
    explicit places(QWidget *parent = 0);
    ~places();

private:
    Ui::places *ui;
};

#endif // PLACES_H
