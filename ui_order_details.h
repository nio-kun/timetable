/********************************************************************************
** Form generated from reading UI file 'order_details.ui'
**
** Created: Sun Oct 9 15:41:57 2011
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_order_details
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_7;
    QLabel *label_5;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_6;
    QCheckBox *checkBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *order_details)
    {
        if (order_details->objectName().isEmpty())
            order_details->setObjectName(QString::fromUtf8("order_details"));
        order_details->resize(477, 291);
        gridLayout = new QGridLayout(order_details);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(order_details);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(order_details);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 2);

        label_2 = new QLabel(order_details);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(order_details);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 2);

        label_3 = new QLabel(order_details);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        lineEdit_3 = new QLineEdit(order_details);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 2, 1, 2);

        label_4 = new QLabel(order_details);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 2);

        lineEdit_4 = new QLineEdit(order_details);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 3, 2, 1, 1);

        label_7 = new QLabel(order_details);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 3, 1, 1);

        label_5 = new QLabel(order_details);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(order_details);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 4, 2, 1, 2);

        label_6 = new QLabel(order_details);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        checkBox = new QCheckBox(order_details);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 5, 2, 1, 2);

        buttonBox = new QDialogButtonBox(order_details);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 1, 1, 3);


        retranslateUi(order_details);
        QObject::connect(buttonBox, SIGNAL(accepted()), order_details, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), order_details, SLOT(reject()));

        QMetaObject::connectSlotsByName(order_details);
    } // setupUi

    void retranslateUi(QDialog *order_details)
    {
        order_details->setWindowTitle(QApplication::translate("order_details", "\320\237\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\275\320\260 \320\276\320\261\321\201\320\273\321\203\320\266\320\270\320\262\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("order_details", "\320\234\320\260\321\200\320\272\320\260 \320\260\320\262\321\202\320\276\320\274\320\276\320\261\320\270\320\273\321\217", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QString());
        label_2->setText(QApplication::translate("order_details", "\320\244\320\230\320\236 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("order_details", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("order_details", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\205\320\276\320\266\320\264\320\265\320\275\320\270\321\217 \320\275\320\260 \320\277\320\273\320\276\321\211\320\260\320\264\320\272\320\265", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setText(QString());
        label_7->setText(QApplication::translate("order_details", "\321\207\320\260\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("order_details", "\320\237\321\200\320\270\320\274\320\265\321\207\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("order_details", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\272\321\203</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\321\200\320\260\320\267\320\262\320\260\320\273\320\260 \321\201\321\205\320\276\320\266\320\264\320\265\320\275\320\270\321\217</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class order_details: public Ui_order_details {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDER_DETAILS_H
