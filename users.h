#ifndef USERS_H
#define USERS_H

#include <QDialog>

namespace Ui {
    class users;
}

class users : public QDialog
{
    Q_OBJECT

public:
    explicit users(QWidget *parent = 0);
    ~users();

private:
    Ui::users *ui;
};

#endif // USERS_H
