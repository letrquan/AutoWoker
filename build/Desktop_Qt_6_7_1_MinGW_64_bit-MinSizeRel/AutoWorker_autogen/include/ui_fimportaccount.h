/********************************************************************************
** Form generated from reading UI file 'fimportaccount.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIMPORTACCOUNT_H
#define UI_FIMPORTACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fImportAccount
{
public:
    QFrame *frame_5;
    QFrame *frame_6;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *lblSuccess;
    QLabel *lblError;
    QLabel *lblTotal;
    QFrame *frame;
    QComboBox *cbbThuMuc;
    QLabel *label_13;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QComboBox *cbbDinhDangNhap;
    QLabel *label_12;
    QPushButton *metroButton1;
    QPushButton *addFileAccount;
    QFrame *frame_3;
    QComboBox *cbbDinhDang1;
    QPushButton *button2;
    QPushButton *button3;
    QComboBox *cbbDinhDang2;
    QComboBox *cbbDinhDang3;
    QComboBox *cbbDinhDang4;
    QComboBox *cbbDinhDang5;
    QComboBox *cbbDinhDang7;
    QComboBox *cbbDinhDang8;
    QComboBox *cbbDinhDang6;
    QComboBox *cbbDinhDang11;
    QComboBox *cbbDinhDang10;
    QComboBox *cbbDinhDang9;
    QFrame *frame_4;
    QLabel *label_14;
    QLabel *lblStatus;
    QPushButton *btnAdd;
    QPushButton *btnCancel;
    QPlainTextEdit *txbAccount;

    void setupUi(QWidget *fImportAccount)
    {
        if (fImportAccount->objectName().isEmpty())
            fImportAccount->setObjectName("fImportAccount");
        fImportAccount->resize(1144, 649);
        fImportAccount->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"border-radius:20px;"));
        frame_5 = new QFrame(fImportAccount);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 10, 1121, 211));
        frame_5->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color: #FFBB70;\n"
"color:black"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 8, 181, 101));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 70, 61, 16));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto Medium")});
        font.setPointSize(9);
        font.setBold(true);
        font.setItalic(false);
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));
        label_9 = new QLabel(frame_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 40, 51, 16));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));
        label_8 = new QLabel(frame_6);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 10, 81, 16));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
""));
        lblSuccess = new QLabel(frame_6);
        lblSuccess->setObjectName("lblSuccess");
        lblSuccess->setGeometry(QRect(100, 10, 31, 16));
        lblSuccess->setStyleSheet(QString::fromUtf8("border:none;\n"
"font-weight:bold;\n"
"color:rgb(53, 120, 229);\n"
""));
        lblError = new QLabel(frame_6);
        lblError->setObjectName("lblError");
        lblError->setGeometry(QRect(50, 40, 31, 16));
        lblError->setStyleSheet(QString::fromUtf8("border:none;\n"
"color:darkred;\n"
"font-weight:bold;\n"
""));
        lblTotal = new QLabel(frame_6);
        lblTotal->setObjectName("lblTotal");
        lblTotal->setGeometry(QRect(80, 70, 31, 16));
        lblTotal->setStyleSheet(QString::fromUtf8("border:none;\n"
"font-weight:bold;\n"
"color:rgb(53, 120, 229);"));
        frame = new QFrame(frame_5);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(510, 10, 301, 100));
        frame->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        cbbThuMuc = new QComboBox(frame);
        cbbThuMuc->setObjectName("cbbThuMuc");
        cbbThuMuc->setGeometry(QRect(20, 40, 181, 24));
        cbbThuMuc->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 10, 91, 16));
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
""));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(210, 40, 71, 24));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{ background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;\n"
"}\n"
"QPushButton:enabled {\n"
"		background-color: #FFFBDA;\n"
"		color: black;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"		background-color: #FFF2D7;\n"
"		color: #fffffe;\n"
"}\n"
"\n"
"\n"
"QPushButton:hover:!pressed {\n"
"		background-color: #ED9455;\n"
"		color: white;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"		background-color: #C40C0C;\n"
"		color: #ffffff;\n"
"}"));
        frame_2 = new QFrame(frame_5);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(200, 10, 301, 100));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        cbbDinhDangNhap = new QComboBox(frame_2);
        cbbDinhDangNhap->setObjectName("cbbDinhDangNhap");
        cbbDinhDangNhap->setGeometry(QRect(20, 40, 181, 24));
        cbbDinhDangNhap->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 10, 101, 16));
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));
        metroButton1 = new QPushButton(frame_2);
        metroButton1->setObjectName("metroButton1");
        metroButton1->setGeometry(QRect(250, 40, 24, 24));
        metroButton1->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/minus.png);\n"
"border-radius:20px;\n"
"border-color: transparent;\n"
""));
        addFileAccount = new QPushButton(frame_2);
        addFileAccount->setObjectName("addFileAccount");
        addFileAccount->setGeometry(QRect(220, 40, 27, 26));
        addFileAccount->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/add.png);\n"
"border-radius:20px;\n"
"border-color: transparent;\n"
""));
        frame_3 = new QFrame(frame_5);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(5, 115, 1111, 91));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        cbbDinhDang1 = new QComboBox(frame_3);
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->addItem(QString());
        cbbDinhDang1->setObjectName("cbbDinhDang1");
        cbbDinhDang1->setGeometry(QRect(10, 10, 91, 24));
        cbbDinhDang1->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        button2 = new QPushButton(frame_3);
        button2->setObjectName("button2");
        button2->setGeometry(QRect(410, 50, 131, 31));
        button2->setFont(font);
        button2->setStyleSheet(QString::fromUtf8("background-color:darkorange;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));
        button3 = new QPushButton(frame_3);
        button3->setObjectName("button3");
        button3->setGeometry(QRect(550, 50, 131, 31));
        button3->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));
        cbbDinhDang2 = new QComboBox(frame_3);
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->addItem(QString());
        cbbDinhDang2->setObjectName("cbbDinhDang2");
        cbbDinhDang2->setGeometry(QRect(110, 10, 91, 24));
        cbbDinhDang2->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang3 = new QComboBox(frame_3);
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->addItem(QString());
        cbbDinhDang3->setObjectName("cbbDinhDang3");
        cbbDinhDang3->setGeometry(QRect(210, 10, 91, 24));
        cbbDinhDang3->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang4 = new QComboBox(frame_3);
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->addItem(QString());
        cbbDinhDang4->setObjectName("cbbDinhDang4");
        cbbDinhDang4->setGeometry(QRect(310, 10, 91, 24));
        cbbDinhDang4->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang5 = new QComboBox(frame_3);
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->addItem(QString());
        cbbDinhDang5->setObjectName("cbbDinhDang5");
        cbbDinhDang5->setGeometry(QRect(410, 10, 91, 24));
        cbbDinhDang5->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang7 = new QComboBox(frame_3);
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->addItem(QString());
        cbbDinhDang7->setObjectName("cbbDinhDang7");
        cbbDinhDang7->setGeometry(QRect(610, 10, 91, 24));
        cbbDinhDang7->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang8 = new QComboBox(frame_3);
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->addItem(QString());
        cbbDinhDang8->setObjectName("cbbDinhDang8");
        cbbDinhDang8->setGeometry(QRect(710, 10, 91, 24));
        cbbDinhDang8->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang6 = new QComboBox(frame_3);
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->addItem(QString());
        cbbDinhDang6->setObjectName("cbbDinhDang6");
        cbbDinhDang6->setGeometry(QRect(510, 10, 91, 24));
        cbbDinhDang6->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang11 = new QComboBox(frame_3);
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->addItem(QString());
        cbbDinhDang11->setObjectName("cbbDinhDang11");
        cbbDinhDang11->setGeometry(QRect(1010, 10, 91, 24));
        cbbDinhDang11->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang10 = new QComboBox(frame_3);
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->addItem(QString());
        cbbDinhDang10->setObjectName("cbbDinhDang10");
        cbbDinhDang10->setGeometry(QRect(910, 10, 91, 24));
        cbbDinhDang10->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        cbbDinhDang9 = new QComboBox(frame_3);
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->addItem(QString());
        cbbDinhDang9->setObjectName("cbbDinhDang9");
        cbbDinhDang9->setGeometry(QRect(810, 10, 91, 24));
        cbbDinhDang9->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color:white;"));
        frame_4 = new QFrame(frame_5);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(820, 10, 291, 100));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 10, 91, 16));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
""));
        lblStatus = new QLabel(frame_4);
        lblStatus->setObjectName("lblStatus");
        lblStatus->setGeometry(QRect(20, 35, 164, 31));
        lblStatus->setFont(font);
        lblStatus->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(188, 38, 31);\n"
"font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
"font-size:12;"));
        btnAdd = new QPushButton(fImportAccount);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(440, 610, 131, 31));
        btnAdd->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));
        btnCancel = new QPushButton(fImportAccount);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(580, 610, 131, 31));
        btnCancel->setStyleSheet(QString::fromUtf8("background-color: darkred;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));
        txbAccount = new QPlainTextEdit(fImportAccount);
        txbAccount->setObjectName("txbAccount");
        txbAccount->setGeometry(QRect(10, 230, 1121, 371));
        txbAccount->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color: #503C3C;\n"
"border-radius:15px;"));

        retranslateUi(fImportAccount);

        QMetaObject::connectSlotsByName(fImportAccount);
    } // setupUi

    void retranslateUi(QWidget *fImportAccount)
    {
        fImportAccount->setWindowTitle(QCoreApplication::translate("fImportAccount", "Form", nullptr));
        label_10->setText(QCoreApplication::translate("fImportAccount", "T\341\273\225ng s\341\273\221:", nullptr));
        label_9->setText(QCoreApplication::translate("fImportAccount", "L\341\273\227i:", nullptr));
        label_8->setText(QCoreApplication::translate("fImportAccount", "Th\303\240nh c\303\264ng:", nullptr));
        lblSuccess->setText(QCoreApplication::translate("fImportAccount", "0", nullptr));
        lblError->setText(QCoreApplication::translate("fImportAccount", "0", nullptr));
        lblTotal->setText(QCoreApplication::translate("fImportAccount", "0", nullptr));
        label_13->setText(QCoreApplication::translate("fImportAccount", "Ch\341\273\215n th\306\260 m\341\273\245c:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("fImportAccount", "Th\303\252m", nullptr));
        label_12->setText(QCoreApplication::translate("fImportAccount", "\304\220\341\273\213nh d\341\272\241ng nh\341\272\255p:", nullptr));
        metroButton1->setText(QString());
        addFileAccount->setText(QString());
        cbbDinhDang1->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang1->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang1->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang1->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang1->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang1->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang1->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang1->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang1->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang1->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang1->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang1->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang1->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        button2->setText(QCoreApplication::translate("fImportAccount", "Reset \304\221\341\273\213nh d\341\272\241ng", nullptr));
        button3->setText(QCoreApplication::translate("fImportAccount", "L\306\260u \304\221\341\273\213nh d\341\272\241ng", nullptr));
        cbbDinhDang2->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang2->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang2->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang2->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang2->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang2->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang2->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang2->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang2->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang2->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang2->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang2->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang2->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang3->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang3->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang3->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang3->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang3->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang3->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang3->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang3->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang3->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang3->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang3->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang3->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang3->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang4->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang4->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang4->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang4->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang4->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang4->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang4->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang4->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang4->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang4->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang4->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang4->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang4->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang5->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang5->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang5->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang5->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang5->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang5->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang5->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang5->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang5->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang5->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang5->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang5->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang5->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang7->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang7->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang7->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang7->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang7->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang7->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang7->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang7->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang7->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang7->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang7->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang7->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang7->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang8->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang8->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang8->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang8->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang8->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang8->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang8->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang8->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang8->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang8->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang8->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang8->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang8->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang6->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang6->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang6->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang6->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang6->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang6->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang6->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang6->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang6->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang6->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang6->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang6->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang6->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang11->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang11->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang11->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang11->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang11->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang11->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang11->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang11->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang11->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang11->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang11->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang11->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang11->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang10->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang10->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang10->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang10->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang10->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang10->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang10->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang10->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang10->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang10->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang10->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang10->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang10->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        cbbDinhDang9->setItemText(0, QCoreApplication::translate("fImportAccount", "Uid", nullptr));
        cbbDinhDang9->setItemText(1, QCoreApplication::translate("fImportAccount", "Pass", nullptr));
        cbbDinhDang9->setItemText(2, QCoreApplication::translate("fImportAccount", "Token", nullptr));
        cbbDinhDang9->setItemText(3, QCoreApplication::translate("fImportAccount", "Cookie", nullptr));
        cbbDinhDang9->setItemText(4, QCoreApplication::translate("fImportAccount", "Email", nullptr));
        cbbDinhDang9->setItemText(5, QCoreApplication::translate("fImportAccount", "Pass Email", nullptr));
        cbbDinhDang9->setItemText(6, QCoreApplication::translate("fImportAccount", "2FA", nullptr));
        cbbDinhDang9->setItemText(7, QCoreApplication::translate("fImportAccount", "Useragent", nullptr));
        cbbDinhDang9->setItemText(8, QCoreApplication::translate("fImportAccount", "Proxy", nullptr));
        cbbDinhDang9->setItemText(9, QCoreApplication::translate("fImportAccount", "Birthday", nullptr));
        cbbDinhDang9->setItemText(10, QCoreApplication::translate("fImportAccount", "B\341\272\241n b\303\250", nullptr));
        cbbDinhDang9->setItemText(11, QCoreApplication::translate("fImportAccount", "Ng\303\240y t\341\272\241o", nullptr));
        cbbDinhDang9->setItemText(12, QCoreApplication::translate("fImportAccount", "Mail kh\303\264i ph\341\273\245c", nullptr));

        label_14->setText(QCoreApplication::translate("fImportAccount", "Tr\341\272\241ng th\303\241i:", nullptr));
        lblStatus->setText(QCoreApplication::translate("fImportAccount", "Chu\341\272\251n b\341\273\213 th\303\252m t\303\240i kho\341\272\243n...", nullptr));
        btnAdd->setText(QCoreApplication::translate("fImportAccount", "L\306\260u", nullptr));
        btnCancel->setText(QCoreApplication::translate("fImportAccount", "\304\220\303\263ng", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fImportAccount: public Ui_fImportAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIMPORTACCOUNT_H
