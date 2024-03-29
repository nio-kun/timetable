#include "users.h"
#include "ui_users.h"
#include <QMessageBox>
#include <QSqlError>

users::users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::users)
{
    ui->setupUi(this);
}

users::users(QSqlDatabase *kept_db, QWidget *parent) : QDialog(parent),
    ui(new Ui::users)
{
    ui->setupUi(this);
    adduser=false;
    db=kept_db;
    if (db->isOpen()){
        QSqlQuery query;
        query.exec("select user_id, login, fio from users where login!='root' order by login");
        while (query.next()){
            ui->listWidget->addItem(query.value(1).toString());
            listvector.append(query.value(0).toInt());
        }
        db->transaction();
    }
}

users::~users()
{
    delete ui;
}

void users::on_listWidget_currentRowChanged(int currentRow)
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        query.exec("select user_id, login, fio from users where user_id="+QString::number(listvector.at(currentRow)));
        query.next();
        ui->lineEdit_3->setText(query.value(2).toString());
        ui->lineEdit->setText(query.value(1).toString());
    }
}

void users::on_pushButton_3_clicked()
{
    if (saved) {
        //Добавление пользователя
        adduser= true;
        ui->lineEdit_3->setText("Фамилия Имя Отчество");
        ui->lineEdit->setText("login");
    } else {
        QMessageBox::information(0,tr("Message"),tr("Please, save your changes first."));
    };
 }

void users::on_pushButton_clicked()
{
    QSqlQuery query;
    QString fio, login, password;
    int isadmin=0;
    fio=ui->lineEdit_3->text();
    login=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    if (ui->checkBox->checkState()){
        isadmin=1;
    }

    if(adduser){
        //Добавляем нового пользователя
       if (fio.length()>0&&login.length()>0&&password.length()>0){
//        query.exec("insert into users (login, fio) values ('"+login+"', '"+fio+"')");
//        query.exec("Grant ALL on *.* to '"+login+"' identified by '"+password+"';");

            if (query.exec("CALL adduser('"+login+"','"+password+"', '"+fio+"', '"+QString::number(isadmin)+"');")){
                query.exec("select max(user_id) from users");
                query.next();

                ui->listWidget->addItem(login);
                listvector.append(query.value(0).toInt());
                ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
            }else{
                QMessageBox::critical(0,tr("Error!"),query.lastError().text());
            }


        }else{
            QMessageBox::critical(0, tr("Error!"), tr("All fields must be filled in."),0,0,0);
        }
       adduser=false;
    }else {
        //Сохраняем пользователя
        if (fio.length()>0&&login.length()>0){
            if (query.exec("CALL updateuser('"+ui->listWidget->currentItem()->text()+"', '"+login+"','"+password+"', '"+fio+"', '"+QString::number(isadmin)+"');")){

                //query.exec("update users set login='"+login+"', fio='"+fio+"', isadmin="+QString::number(isadmin)+" where user_id="+QString::number(listvector.at(ui->listWidget->currentRow()))+";");
                //query.exec("DROP USER '"+ui->listWidget->currentItem()->text() +"';");
                //query.exec("Grant ALL on *.* to '"+login+"' identified by '"+password+"';");
                ui->listWidget->currentItem()->setText(login);
            }else{
                QMessageBox::critical(0,tr("Error!"),query.lastError().text());
            }
        }else{
            QMessageBox::critical(0, tr("Error!"), tr("All fields must be filled in."),0,0,0);
        }
    }
    saved= true;
    db->commit();
    db->transaction();
}

void users::on_pushButton_2_clicked()
{
    QSqlQuery query;
    int currow =ui->listWidget->currentRow();

    //Удаление пользователя
    if (QMessageBox::question(0,tr("Are you sure?"),tr("Really delete?"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
    {
        QString login=ui->listWidget->currentItem()->text();
        if (login!=db->userName()){
            query.exec("delete from users where user_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
            query.exec("DROP USER '"+login+"';");
            delete ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
            ui->listWidget->setCurrentRow(currow);
        }else{
            QMessageBox::critical(0, tr("Error!"), tr("You can't remove yourself."),0,0,0);
        }
    };

}

void users::on_buttonBox_accepted()
{
    db->commit();
    close();
}

void users::closeEvent(QCloseEvent *event)
{
db->rollback();
}

void users::on_buttonBox_rejected()
{
    close();
}

void users::on_lineEdit_3_textEdited(QString )
{
    saved=false;
}

void users::on_lineEdit_textEdited(QString )
{
    saved=false;
}

void users::on_lineEdit_2_textEdited(QString )
{
    saved=false;
}
