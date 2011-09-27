/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Tue Sep 27 00:21:24 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QString::fromUtf8("settings"));
        settings->resize(361, 178);
        buttonBox = new QDialogButtonBox(settings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(180, 140, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(settings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 341, 51));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 20, 171, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 25, 46, 13));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 25, 31, 16));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(280, 20, 51, 20));
        label_3 = new QLabel(settings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 84, 131, 16));
        lineEdit_3 = new QLineEdit(settings);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 80, 21, 20));
        label_4 = new QLabel(settings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 84, 46, 13));
        lineEdit_4 = new QLineEdit(settings);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(210, 80, 21, 20));
        label_5 = new QLabel(settings);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(230, 84, 46, 13));

        retranslateUi(settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("settings", "\320\241\320\265\321\200\320\262\320\265\321\200 \320\221\320\224", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("settings", "\320\220\320\264\321\200\320\265\321\201:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("settings", "\320\237\320\276\321\200\321\202:", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("settings", "3306", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("settings", "\320\236\320\261\320\265\320\264\320\265\320\275\320\275\321\213\320\271 \320\277\320\265\321\200\320\265\321\200\321\213\320\262 \321\201 ", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("settings", "12", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("settings", ":00 \320\264\320\276", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setText(QApplication::translate("settings", "14", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("settings", ":00", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
