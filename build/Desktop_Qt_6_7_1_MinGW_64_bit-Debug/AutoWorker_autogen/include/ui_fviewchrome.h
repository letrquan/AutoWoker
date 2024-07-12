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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fViewChrome
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *scrollLayout;

    void setupUi(QMainWindow *fViewChrome)
    {
        if (fViewChrome->objectName().isEmpty())
            fViewChrome->setObjectName("fViewChrome");
        fViewChrome->resize(800, 600);
        centralwidget = new QWidget(fViewChrome);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 780, 580));
        scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
        scrollLayout->setSpacing(10);
        scrollLayout->setObjectName("scrollLayout");
        scrollLayout->setContentsMargins(10, 10, 10, 10);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        fViewChrome->setCentralWidget(centralwidget);

        retranslateUi(fViewChrome);

        QMetaObject::connectSlotsByName(fViewChrome);
    } // setupUi

    void retranslateUi(QMainWindow *fViewChrome)
    {
        fViewChrome->setWindowTitle(QCoreApplication::translate("fViewChrome", "Qt Chrome Viewer (0)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fViewChrome: public Ui_fViewChrome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FVIEWCHROME_H
