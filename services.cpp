#include "services.h"
#include "ui_services.h"

services::services(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::services)
{
    ui->setupUi(this);
}


services::services(QSqlDatabase *kept_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::services)
{
    ui->setupUi(this);
    db=kept_db;

    if (db->isOpen()){
        QSqlQuery query;
        query.exec("select service_id, name from services order by name");
        while (query.next()){
            ui->listWidget->addItem(query.value(1).toString());
            listvector.append(query.value(0).toInt());
        }
    }

    db->transaction();
}


services::~services()
{
    delete ui;
}

void services::on_buttonBox_accepted()
{
    db->commit();
    close();
}

void services::on_buttonBox_rejected()
{
    close();
}

void services::closeEvent(QCloseEvent *event)
{
    db->rollback();
}

void services::on_pushButton_clicked()
{
    db->commit();
    db->transaction();
}

void services::on_lineEdit_editingFinished()
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        query.exec("update services set name='"+ui->lineEdit->text() +"' where service_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
    }
}

void services::on_lineEdit_textEdited(const QString &arg1)
{
    if (ui->listWidget->currentRow()>-1){
        ui->listWidget->currentItem()->setText(arg1);
    }
}

void services::on_listWidget_currentRowChanged(int currentRow)
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        query.exec("select service_id, name from services where service_id="+QString::number(listvector.at(currentRow)));
        query.next();
        ui->lineEdit->setText(query.value(1).toString());
    }
}

void services::on_pushButton_2_clicked()
{
    QSqlQuery query;
    QString str;
    bool ok;
    str = QInputDialog::getText(0,"",tr("Enter service name"),QLineEdit::Normal,"",&ok);
    if (ok){
        if (str.length()>0){
            query.prepare("insert into services (name) values (:name)");
            query.bindValue(":name", str);
            query.exec();

            query.exec("select max(service_id) from services");
            query.next();

            ui->listWidget->addItem(str);
            listvector.append(query.value(0).toInt());

            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

        }
        else{
            QMessageBox::critical(0,tr("Error!"),tr("Service name can't be empty"),0,0,0);
        }
    }
}

void services::on_pushButton_3_clicked()
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        if (QMessageBox::question(0,tr("Service removal"),tr("Do you want to remove service")+" \""+ui->listWidget->currentItem()->text()+"\"?",3,4,0)==3){
            query.exec("delete from services where service_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
            listvector.remove(ui->listWidget->currentRow());
            delete ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
    }else{
        QMessageBox::critical(0,tr("Removal error"),tr("Select service to remove"),0,0,0);
    }
}
