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
    constructor(kept_db, hide_dinner, parent);
}

settings::settings(QSqlDatabase *kept_db, QColor *d_color, bool hide_dinner, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    constructor(kept_db, hide_dinner, parent);
    dinner_color=d_color;

    QFile file(qApp->applicationDirPath()+"/properties.ini");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString temp_text;
        int pos;
        QString param;
        while ( !stream.atEnd() ) {
            temp_text=stream.readLine();
            pos = temp_text.indexOf("=");
            if (pos>-1){
                param=temp_text.left(pos).trimmed();
                if (param=="dinner_color"){
                    dinner_color->setNamedColor(temp_text.mid(pos+1).trimmed());
                }
            }
        }
        file.close();
    }


    QPixmap pix(16, 16);
    pix.fill(*dinner_color);
    ui->pushButton_3->setIcon(pix);

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
        stream << "dinner_color = "+dinner_color->name()+"\n";
        file.close();
    }else{
        QMessageBox::critical(0, tr("File write error"),tr("Settings file can't be saved"), 0,0,0);
        return;
    }


    if (ui->lineEdit_3->text().toInt() > ui->lineEdit_4->text().toInt()){
        QMessageBox::information(0, tr("Error!"),tr("Dinner initiation time can't be greater than dinner finalization time"), 0,0,0);
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
        QMessageBox::critical(0, ("Error!"),tr("Dinner time must be an integer value from 0 to 24"), 0,0,0);
        lineEdit->setFocus();
    }
}

void settings::on_lineEdit_4_lostFocus()
{
    check_dinner_time(ui->lineEdit_4);
}


void settings::constructor(QSqlDatabase *kept_db, bool hide_dinner, QWidget *parent)
{
    ui->setupUi(this);
    db=kept_db;
    ui->lineEdit->setText(db->hostName());
    ui->lineEdit_2->setText(QString::number(db->port()));

    int isadmin=0;

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

        query.exec("select isadmin from users where login='"+db->userName()+"'");
        query.next();
        isadmin=query.value(0).toInt();
    }

    if (hide_dinner || !isadmin){
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

void settings::on_pushButton_3_clicked()
{
    *dinner_color = QColorDialog::getColor();
    QPixmap pix(16, 16);
    pix.fill(*dinner_color);
    ui->pushButton_3->setIcon(pix);
}
