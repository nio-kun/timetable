/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created: Wed Sep 28 14:59:26 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_authorization
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *authorization)
    {
        if (authorization->objectName().isEmpty())
            authorization->setObjectName(QString::fromUtf8("authorization"));
        authorization->resize(312, 119);
        authorization->setSizeGripEnabled(false);
        authorization->setModal(false);
        verticalLayout = new QVBoxLayout(authorization);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(authorization);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setMinimumSize(QSize(50, 0));

        horizontalLayout_2->addWidget(label);

        lineEdit_2 = new QLineEdit(authorization);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(authorization);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(authorization);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(authorization);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(authorization);
        QObject::connect(buttonBox, SIGNAL(accepted()), authorization, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), authorization, SLOT(reject()));

        QMetaObject::connectSlotsByName(authorization);
    } // setupUi

    void retranslateUi(QDialog *authorization)
    {
        authorization->setWindowTitle(QApplication::translate("authorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("authorization", "\320\233\320\276\320\263\320\270\320\275", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QString());
        label_2->setText(QApplication::translate("authorization", "\320\237\320\260\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class authorization: public Ui_authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
