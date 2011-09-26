#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

namespace Ui {
    class authorization;
}

class authorization : public QDialog
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = 0);
    ~authorization();

private:
    Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
