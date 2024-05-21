/********************************************************************************
** Form generated from reading UI file 'downloaddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADDIALOG_H
#define UI_DOWNLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_DownloadDialog
{
public:
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *gifLabel;

    void setupUi(QDialog *DownloadDialog)
    {
        if (DownloadDialog->objectName().isEmpty())
            DownloadDialog->setObjectName("DownloadDialog");
        DownloadDialog->resize(473, 167);
        label = new QLabel(DownloadDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 121, 31));
        progressBar = new QProgressBar(DownloadDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(30, 70, 251, 31));
        progressBar->setValue(24);
        gifLabel = new QLabel(DownloadDialog);
        gifLabel->setObjectName("gifLabel");
        gifLabel->setGeometry(QRect(320, 40, 91, 81));
        gifLabel->setScaledContents(true);
        gifLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(DownloadDialog);

        QMetaObject::connectSlotsByName(DownloadDialog);
    } // setupUi

    void retranslateUi(QDialog *DownloadDialog)
    {
        DownloadDialog->setWindowTitle(QCoreApplication::translate("DownloadDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DownloadDialog", "Downloading: ", nullptr));
        gifLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DownloadDialog: public Ui_DownloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIALOG_H
