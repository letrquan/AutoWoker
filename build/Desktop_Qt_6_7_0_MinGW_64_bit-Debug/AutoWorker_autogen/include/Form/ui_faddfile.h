/********************************************************************************
** Form generated from reading UI file 'faddfile.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FADDFILE_H
#define UI_FADDFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_fAddFile
{
public:
    QPushButton *btnCancel;
    QPushButton *btnAdd;
    QLabel *label;
    QLineEdit *txbNameFile;

    void setupUi(QDialog *fAddFile)
    {
        if (fAddFile->objectName().isEmpty())
            fAddFile->setObjectName("fAddFile");
        fAddFile->resize(400, 128);
        fAddFile->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(0, 0, 0);"));
        btnCancel = new QPushButton(fAddFile);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(210, 80, 131, 31));
        btnCancel->setStyleSheet(QString::fromUtf8("background-color: darkred;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));
        btnAdd = new QPushButton(fAddFile);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(70, 80, 131, 31));
        btnAdd->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));
        label = new QLabel(fAddFile);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 71, 16));
        txbNameFile = new QLineEdit(fAddFile);
        txbNameFile->setObjectName("txbNameFile");
        txbNameFile->setGeometry(QRect(90, 40, 281, 24));
        txbNameFile->setStyleSheet(QString::fromUtf8("border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: white; /* Define the color of the border */"));

        retranslateUi(fAddFile);

        QMetaObject::connectSlotsByName(fAddFile);
    } // setupUi

    void retranslateUi(QDialog *fAddFile)
    {
        fAddFile->setWindowTitle(QCoreApplication::translate("fAddFile", "Dialog", nullptr));
        btnCancel->setText(QCoreApplication::translate("fAddFile", "H\341\273\247y", nullptr));
        btnAdd->setText(QCoreApplication::translate("fAddFile", "Th\303\252m", nullptr));
        label->setText(QCoreApplication::translate("fAddFile", "T\303\252n th\306\260 m\341\273\245c:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fAddFile: public Ui_fAddFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FADDFILE_H
