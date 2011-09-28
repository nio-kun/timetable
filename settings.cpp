#include "settings.h"
#include "ui_settings.h"
#include <QFile>
#include <QTextStream>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);


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

                if (param=="database_host"){
                    ui->lineEdit->setText(temp_text.mid(pos+1).trimmed());
                } else if (param=="database_port") {
                    ui->lineEdit_2->setText(temp_text.mid(pos+1).trimmed());
                }
            }
        }
        file.close();
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
        close();
    }else{
        QMessageBox::information(0, "Ошибка записи файла","Невозможно записать файл с настройками.", 0,0,0);
    }
}

void settings::on_pushButton_2_clicked()
{
    close();
}
