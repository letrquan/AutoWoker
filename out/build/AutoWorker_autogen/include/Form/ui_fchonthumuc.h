/********************************************************************************
** Form generated from reading UI file 'fchonthumuc.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCHONTHUMUC_H
#define UI_FCHONTHUMUC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_fChonThuMuc
{
public:
    QPushButton *btnCancel;
    QPushButton *btnAdd;
    QPushButton *button5;
    QPushButton *button4;
    QTableWidget *dtgvAcc;
    QLabel *label;
    QLabel *lblCountChoose;
    QLabel *label_9;
    QLabel *lblCountTotal;
    QLabel *label_8;
    QCheckBox *checkBox1;

    void setupUi(QDialog *fChonThuMuc)
    {
        if (fChonThuMuc->objectName().isEmpty())
            fChonThuMuc->setObjectName("fChonThuMuc");
        fChonThuMuc->resize(427, 375);
        fChonThuMuc->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
""));
        btnCancel = new QPushButton(fChonThuMuc);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(210, 330, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto Medium")});
        font.setPointSize(9);
        font.setBold(true);
        font.setItalic(false);
        btnCancel->setFont(font);
        btnCancel->setStyleSheet(QString::fromUtf8("background-color:darkred;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));
        btnAdd = new QPushButton(fChonThuMuc);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(93, 330, 111, 31));
        btnAdd->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));
        button5 = new QPushButton(fChonThuMuc);
        button5->setObjectName("button5");
        button5->setGeometry(QRect(360, 60, 41, 41));
        button5->setStyleSheet(QString::fromUtf8("image: url(:/img/img/up-arrow-blue.png);"));
        button4 = new QPushButton(fChonThuMuc);
        button4->setObjectName("button4");
        button4->setGeometry(QRect(360, 120, 41, 41));
        button4->setStyleSheet(QString::fromUtf8("image: url(:/img/img/down-arrow.png);"));
        dtgvAcc = new QTableWidget(fChonThuMuc);
        if (dtgvAcc->columnCount() < 4)
            dtgvAcc->setColumnCount(4);
        QFont font1;
        font1.setPointSize(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        dtgvAcc->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dtgvAcc->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        dtgvAcc->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        dtgvAcc->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        dtgvAcc->setObjectName("dtgvAcc");
        dtgvAcc->setGeometry(QRect(10, 30, 341, 231));
        dtgvAcc->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        dtgvAcc->setSortingEnabled(false);
        label = new QLabel(fChonThuMuc);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 270, 341, 16));
        label->setStyleSheet(QString::fromUtf8("color: rgb(85, 0, 0);"));
        lblCountChoose = new QLabel(fChonThuMuc);
        lblCountChoose->setObjectName("lblCountChoose");
        lblCountChoose->setGeometry(QRect(180, 300, 31, 16));
        lblCountChoose->setStyleSheet(QString::fromUtf8("border:none;"));
        label_9 = new QLabel(fChonThuMuc);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(220, 300, 51, 16));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));
        lblCountTotal = new QLabel(fChonThuMuc);
        lblCountTotal->setObjectName("lblCountTotal");
        lblCountTotal->setGeometry(QRect(270, 300, 31, 16));
        lblCountTotal->setStyleSheet(QString::fromUtf8("border:none;\n"
"color:darkred;"));
        label_8 = new QLabel(fChonThuMuc);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 300, 61, 16));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
""));
        checkBox1 = new QCheckBox(fChonThuMuc);
        checkBox1->setObjectName("checkBox1");
        checkBox1->setGeometry(QRect(55, 35, 16, 16));
        checkBox1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(fChonThuMuc);

        QMetaObject::connectSlotsByName(fChonThuMuc);
    } // setupUi

    void retranslateUi(QDialog *fChonThuMuc)
    {
        fChonThuMuc->setWindowTitle(QCoreApplication::translate("fChonThuMuc", "Dialog", nullptr));
        btnCancel->setText(QCoreApplication::translate("fChonThuMuc", "\304\220\303\263ng", nullptr));
        btnAdd->setText(QCoreApplication::translate("fChonThuMuc", "L\306\260u", nullptr));
        button5->setText(QString());
        button4->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = dtgvAcc->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("fChonThuMuc", "STT", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dtgvAcc->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("fChonThuMuc", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dtgvAcc->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("fChonThuMuc", "Id", nullptr));
        label->setText(QCoreApplication::translate("fChonThuMuc", "(Click \304\221\303\272p v\303\240o d\303\262ng \304\221\341\273\203 ch\341\273\215n)", nullptr));
        lblCountChoose->setText(QCoreApplication::translate("fChonThuMuc", "0", nullptr));
        label_9->setText(QCoreApplication::translate("fChonThuMuc", "T\341\272\245t c\341\272\243:", nullptr));
        lblCountTotal->setText(QCoreApplication::translate("fChonThuMuc", "0", nullptr));
        label_8->setText(QCoreApplication::translate("fChonThuMuc", "\304\220\303\243 ch\341\273\215n:", nullptr));
        checkBox1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class fChonThuMuc: public Ui_fChonThuMuc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCHONTHUMUC_H
