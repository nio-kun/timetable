#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::settings(QSqlDatabase *kept_db, bool hide_dinner, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    db=kept_db;
    ui->lineEdit->setText(db->hostName());
    ui->lineEdit_2->setText(QString::number(db->port()));

    if (db->isOpen()){
        QSqlQuery query;
        query.exec("select value from settings where name='dinner_start_time'");
        if (query.numRowsAffected()>0){
            query.next();
            ui->lineEdit_3->setText(query.value(0).toString());
        }

        query.exec("select value from settings where name='dinner_end_time'");
        if (query.numRowsAffected()>0){
            query.next();
            ui->lineEdit_4->setText(query.value(0).toString());
        }

        query.exec("select value from settings where name='work_start_time'");
        if (query.numRowsAffected()>0){
            query.next();
            ui->lineEdit_5->setText(query.value(0).toString());
        }

        query.exec("select value from settings where name='work_end_time'");
        if (query.numRowsAffected()>0){
            query.next();
            ui->lineEdit_6->setText(query.value(0).toString());
        }
    }

    if (hide_dinner){
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();

        ui->label_6->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->lineEdit_5->hide();
        ui->lineEdit_6->hide();
    }
}

settings::~settings()
{
    delete ui;
}

void settings::on_pushButton_clicked()
{
    QFile file(qApp->applicationDirPath()+"/properties.ini");
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        stream << "database_host = "+ui->lineEdit->text()+"\n";
        stream << "database_port = "+ui->lineEdit_2->text()+"\n";
        file.close();
    }else{
        QMessageBox::information(0, "Ошибка записи файла","Невозможно записать файл с настройками.", 0,0,0);
        return;
    }


    if (ui->lineEdit_3->text().toInt() > ui->lineEdit_4->text().toInt()){
        QMessageBox::information(0, "Ошибка","Время начала обеда не может быть больше времени окончания", 0,0,0);
        ui->lineEdit_3->setFocus();
        return;
    }
    if (db->isOpen()){
        QSqlQuery query;

        query.exec("delete from settings where name='dinner_start_time'");
        query.prepare ("insert into settings (name, type, value) values ('dinner_start_time','integer',:data)");
        query.bindValue(":data", ui->lineEdit_3->text());
        query.exec();

        query.exec("delete from settings where name='dinner_end_time'");
        query.prepare ("insert into settings (name, type, value) values ('dinner_end_time','integer',:data)");
        query.bindValue(":data", ui->lineEdit_4->text());
        query.exec();

        query.exec("delete from settings where name='work_start_time'");
        query.prepare ("insert into settings (name, type, value) values ('work_start_time','integer',:data)");
        query.bindValue(":data", ui->lineEdit_5->text());
        query.exec();

        query.exec("delete from settings where name='work_end_time'");
        query.prepare ("insert into settings (name, type, value) values ('work_end_time','integer',:data)");
        query.bindValue(":data", ui->lineEdit_6->text());
        query.exec();
    }else{
        db->setHostName(ui->lineEdit->text());
        db->setPort(ui->lineEdit_2->text().toInt());
    }
    close();
}

void settings::on_pushButton_2_clicked()
{
    close();
}

void settings::on_lineEdit_3_lostFocus()
{
    check_dinner_time(ui->lineEdit_3);
}

void settings::check_dinner_time(QLineEdit *lineEdit){
    bool ok;
    int val;
    val=lineEdit->text().toInt(&ok);
    if (!ok || val < 0 || val > 24){
        QMessageBox::information(0, "Ошибка","Время обеда должно быть числом от 0 до 24", 0,0,0);
        lineEdit->setFocus();
    }
}

void settings::on_lineEdit_4_lostFocus()
{
    check_dinner_time(ui->lineEdit_4);
}
