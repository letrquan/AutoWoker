/********************************************************************************
** Form generated from reading UI file 'fviewchrome.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FVIEWCHROME_H
#define UI_FVIEWCHROME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fViewChrome
{
public:

    void setupUi(QWidget *fViewChrome)
    {
        if (fViewChrome->objectName().isEmpty())
            fViewChrome->setObjectName("fViewChrome");
        fViewChrome->resize(400, 300);

        retranslateUi(fViewChrome);

        QMetaObject::connectSlotsByName(fViewChrome);
    } // setupUi

    void retranslateUi(QWidget *fViewChrome)
    {
        fViewChrome->setWindowTitle(QCoreApplication::translate("fViewChrome", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fViewChrome: public Ui_fViewChrome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FVIEWCHROME_H
