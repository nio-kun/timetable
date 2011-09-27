/********************************************************************************
** Form generated from reading UI file 'order_details.ui'
**
** Created: Tue Sep 27 00:21:24 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDER_DETAILS_H
#define UI_ORDER_DETAILS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_order_details
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_6;
    QLabel *label_7;
    QCheckBox *checkBox;

    void setupUi(QDialog *order_details)
    {
        if (order_details->objectName().isEmpty())
            order_details->setObjectName(QString::fromUtf8("order_details"));
        order_details->resize(440, 286);
        buttonBox = new QDialogButtonBox(order_details);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(130, 250, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(order_details);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 14, 101, 16));
        label_2 = new QLabel(order_details);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 44, 71, 16));
        label_3 = new QLabel(order_details);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 74, 91, 16));
        label_4 = new QLabel(order_details);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 104, 171, 16));
        label_5 = new QLabel(order_details);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 134, 71, 16));
        lineEdit = new QLineEdit(order_details);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 10, 231, 20));
        lineEdit_2 = new QLineEdit(order_details);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(200, 40, 231, 20));
        lineEdit_3 = new QLineEdit(order_details);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(200, 70, 231, 20));
        lineEdit_4 = new QLineEdit(order_details);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(200, 100, 41, 20));
        plainTextEdit = new QPlainTextEdit(order_details);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(200, 130, 231, 71));
        label_6 = new QLabel(order_details);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 204, 131, 31));
        label_7 = new QLabel(order_details);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(260, 104, 46, 13));
        checkBox = new QCheckBox(order_details);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(200, 210, 71, 18));

        retranslateUi(order_details);
        QObject::connect(buttonBox, SIGNAL(accepted()), order_details, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), order_details, SLOT(reject()));

        QMetaObject::connectSlotsByName(order_details);
    } // setupUi

    void retranslateUi(QDialog *order_details)
    {
        order_details->setWindowTitle(QApplication::translate("order_details", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\201\320\273\321\203\320\266\320\270\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("order_details", "\320\234\320\260\321\200\320\272\320\260 \320\260\320\262\321\202\320\276\320\274\320\276\320\261\320\270\320\273\321\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("order_details", "\320\244\320\230\320\236 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("order_details", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("order_details", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\205\320\276\320\266\320\264\320\265\320\275\320\270\321\217 \320\275\320\260 \320\277\320\273\320\276\321\211\320\260\320\264\320\272\320\265", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("order_details", "\320\237\321\200\320\270\320\274\320\265\321\207\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QString());
        lineEdit_4->setText(QString());
        label_6->setText(QApplication::translate("order_details", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\272\321\203</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\321\200\320\260\320\267\320\262\320\260\320\273\320\260 \321\201\321\205\320\276\320\266\320\264\320\265\320\275\320\270\321\217</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("order_details", "\321\207\320\260\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class order_details: public Ui_order_details {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDER_DETAILS_H
