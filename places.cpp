#include "places.h"
#include "ui_places.h"

places::places(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::places)
{
    ui->setupUi(this);
}

places::places(QSqlDatabase *kept_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::places)
{
    ui->setupUi(this);
    db=kept_db;
    if (db->isOpen()){
        QSqlQuery query;
        query.exec("select place_id, name, color, rs from places order by name");
        while (query.next()){
            ui->listWidget->addItem(query.value(1).toString());
            listvector.append(query.value(0).toInt());
        }
    }

    db->transaction();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    ui->pushButton_2->setIcon(pix);
}

places::~places()
{
    delete ui;
}

void places::on_pushButton_clicked()
{
    db->commit();
    db->transaction();
}

void places::on_listWidget_currentRowChanged(int currentRow)
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        query.exec("select place_id, name, color, rs from places where place_id="+QString::number(listvector.at(currentRow)));
        query.next();
        ui->lineEdit_3->setText(query.value(1).toString());
        if (query.value(3).toInt()){
            ui->checkBox->setCheckState(Qt::Checked);
        }else{
            ui->checkBox->setCheckState(Qt::Unchecked);
        }

        QColor color(query.value(2).toString());
        QPixmap pix(16, 16);
        pix.fill(color);
        ui->pushButton_2->setIcon(pix);
    }
}

void places::on_pushButton_2_clicked()
{
    if (ui->listWidget->currentRow()>-1){
        QColor color = QColorDialog::getColor();
        QPixmap pix(16, 16);
        pix.fill(color);
        ui->pushButton_2->setIcon(pix);
        QSqlQuery query(*db);
        query.exec("update places set color='"+color.name() +"' where place_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
    }
}

//void places::accept()
//{
//    db->commit();
//    close();
//}

void places::reject()
{
    close();
}


void places::on_lineEdit_3_textEdited(QString str)
{
    if (ui->listWidget->currentRow()>-1){
        ui->listWidget->currentItem()->setText(str);
    }
}

void places::on_checkBox_stateChanged(int st)
{
//    QMessageBox::information(0, QString::number(st), 0,0,0);
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        int ch=0;
        if (st){
            ch=1;
        }
        query.exec("update places set rs='"+QString::number(ch) +"' where place_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
    }

}

void places::on_lineEdit_3_editingFinished()
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        query.exec("update places set name='"+ui->lineEdit_3->text() +"' where place_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
    }
}

void places::on_buttonBox_accepted()
{
    db->commit();
    close();
}

void places::on_buttonBox_rejected()
{
    close();
}

void places::closeEvent(QCloseEvent *event)
{
    db->rollback();
}

void places::on_pushButton_3_clicked()
{
    QSqlQuery query;
    QString str;
    bool ok;
    str = QInputDialog::getText(0,"","Введите название площадки",QLineEdit::Normal,"",&ok);
    if (ok){
        if (str.length()>0){
            query.prepare("insert into places (name, color, rs) values (:name, '#000000', 0)");
            query.bindValue(":name", str);
            query.exec();

            query.exec("select max(place_id) from places");
            query.next();

            ui->listWidget->addItem(str);
            listvector.append(query.value(0).toInt());

            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

        }
        else{
            QMessageBox::critical(0,"Ошибка","Название площадки не может быть пустым",0,0,0);
        }
    }
}

void places::on_pushButton_4_clicked()
{
    if (ui->listWidget->currentRow()>-1){
        QSqlQuery query;
        if (QMessageBox::question(0,"Удаление площадки","Удалить площадку \""+ui->listWidget->currentItem()->text()+"\"?",3,4,0)==3){
            query.exec("delete from places where place_id="+QString::number(listvector.at(ui->listWidget->currentRow())));
            listvector.remove(ui->listWidget->currentRow());
            delete ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
    }else{
        QMessageBox::information(0,"Удаление невозможно","Выберите площадку для удаления",0,0,0);
    }

}
