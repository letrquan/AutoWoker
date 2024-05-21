/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_10;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QFrame *frame_5;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLabel *lblCountSelect;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLabel *lblCountTotal;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *metroButton1;
    QPushButton *button9;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QComboBox *cbbSearch;
    QFrame *frame_4;
    QComboBox *cbbThuMuc;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cbbTinhTrang;
    QGridLayout *gridLayout;
    QPushButton *btnLoadAcc;
    QPushButton *btnEditFile;
    QPushButton *btnDeleteFile;
    QPushButton *addFileAccount;
    QFrame *frame_6;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_11;
    QPushButton *pushButton_7;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1381, 723);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"border-radius:15px;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 1365, 707));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(274, 705));
        frame->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"background-color: #FFBB70;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(60, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Jersey 10")});
        font.setPointSize(22);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color:#FBC02D;\n"
"image: url(:/img/img/eagle.png);"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("C:/Users/quan2/Downloads/Telegram Desktop/AutoPC/AutoPC/autoworkerpc.ico")));
        label_4->setScaledContents(true);

        horizontalLayout_4->addWidget(label_4);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(141, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Jersey 10")});
        font1.setPointSize(18);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color:black;"));

        horizontalLayout_4->addWidget(label_5);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        pushButton_10 = new QPushButton(frame);
        pushButton_10->setObjectName("pushButton_10");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy2);
        pushButton_10->setMinimumSize(QSize(211, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Roboto Medium")});
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setItalic(false);
        pushButton_10->setFont(font2);
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;\n"
"qproperty-icon: url(:/img/C:/Users/quan2/Downloads/play-button.png);\n"
"qproperty-iconSize: 20px 20px;\n"
"text-align: center;\n"
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

        verticalLayout_5->addWidget(pushButton_10);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(211, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{ background-color: #FFFBDA;\n"
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

        verticalLayout_5->addWidget(pushButton);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(211, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;}\n"
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

        verticalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(211, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;}\n"
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

        verticalLayout_5->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(211, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;}\n"
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

        verticalLayout_5->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(211, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;}\n"
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

        verticalLayout_5->addWidget(pushButton_6);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        sizePolicy.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy);
        frame_5->setMinimumSize(QSize(251, 211));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_5);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_8 = new QLabel(frame_5);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(61, 16));
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */\n"
""));

        horizontalLayout_7->addWidget(label_8);

        lblCountSelect = new QLabel(frame_5);
        lblCountSelect->setObjectName("lblCountSelect");
        lblCountSelect->setMinimumSize(QSize(31, 16));
        lblCountSelect->setStyleSheet(QString::fromUtf8("border:none;"));

        horizontalLayout_7->addWidget(lblCountSelect);


        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_9 = new QLabel(frame_5);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(51, 16));
        label_9->setFont(font2);
        label_9->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));

        horizontalLayout_8->addWidget(label_9);

        lblCountTotal = new QLabel(frame_5);
        lblCountTotal->setObjectName("lblCountTotal");
        lblCountTotal->setMinimumSize(QSize(31, 16));
        lblCountTotal->setStyleSheet(QString::fromUtf8("border:none;\n"
"color:darkred;"));

        horizontalLayout_8->addWidget(lblCountTotal);


        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_10 = new QLabel(frame_5);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(51, 16));
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("font-weight:bold;\n"
"border-width: 0; /* Set the width of the border */"));

        horizontalLayout_9->addWidget(label_10);

        label_15 = new QLabel(frame_5);
        label_15->setObjectName("label_15");
        label_15->setMinimumSize(QSize(31, 16));
        label_15->setStyleSheet(QString::fromUtf8("border:none;"));

        horizontalLayout_9->addWidget(label_15);


        verticalLayout_8->addLayout(horizontalLayout_9);


        gridLayout_2->addLayout(verticalLayout_8, 0, 0, 1, 1);


        verticalLayout_5->addWidget(frame_5);


        horizontalLayout_5->addWidget(frame);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(1081, 121));
        frame_2->setLayoutDirection(Qt::RightToLeft);
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFBB70;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(frame_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(9, 9, 1021, 103));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        metroButton1 = new QPushButton(layoutWidget1);
        metroButton1->setObjectName("metroButton1");
        metroButton1->setMinimumSize(QSize(151, 40));
        metroButton1->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border:2px solid black;\n"
"font-weight:bold;}\n"
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
"}\n"
""));

        verticalLayout_2->addWidget(metroButton1);

        button9 = new QPushButton(layoutWidget1);
        button9->setObjectName("button9");
        button9->setMinimumSize(QSize(151, 40));
        button9->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"border:2px solid black;\n"
"font-weight:bold;}\n"
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

        verticalLayout_2->addWidget(button9);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        frame_3 = new QFrame(layoutWidget1);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(421, 40));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget2 = new QWidget(frame_3);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 8, 397, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(31, 24));
        pushButton_2->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/search.png);\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;\n"
"background-color: black;"));

        horizontalLayout->addWidget(pushButton_2);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(191, 24));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));

        horizontalLayout->addWidget(lineEdit);

        cbbSearch = new QComboBox(layoutWidget2);
        cbbSearch->setObjectName("cbbSearch");
        cbbSearch->setMinimumSize(QSize(161, 24));
        cbbSearch->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));

        horizontalLayout->addWidget(cbbSearch);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(layoutWidget1);
        frame_4->setObjectName("frame_4");
        frame_4->setMinimumSize(QSize(471, 40));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        cbbThuMuc = new QComboBox(frame_4);
        cbbThuMuc->setObjectName("cbbThuMuc");
        cbbThuMuc->setGeometry(QRect(80, 10, 181, 24));
        cbbThuMuc->setMinimumSize(QSize(181, 24));
        cbbThuMuc->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));
        label = new QLabel(frame_4);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 24));
        label->setMinimumSize(QSize(61, 24));
        label->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;"));
        label_2 = new QLabel(frame_4);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 10, 31, 24));
        label_2->setMinimumSize(QSize(31, 24));
        label_2->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;"));
        cbbTinhTrang = new QComboBox(frame_4);
        cbbTinhTrang->setObjectName("cbbTinhTrang");
        cbbTinhTrang->setGeometry(QRect(310, 10, 141, 24));
        cbbTinhTrang->setMinimumSize(QSize(141, 24));
        cbbTinhTrang->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));

        verticalLayout->addWidget(frame_4);


        horizontalLayout_3->addLayout(verticalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        btnLoadAcc = new QPushButton(layoutWidget1);
        btnLoadAcc->setObjectName("btnLoadAcc");
        btnLoadAcc->setMinimumSize(QSize(21, 24));
        btnLoadAcc->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/refresh.png);"));

        gridLayout->addWidget(btnLoadAcc, 1, 1, 1, 1);

        btnEditFile = new QPushButton(layoutWidget1);
        btnEditFile->setObjectName("btnEditFile");
        btnEditFile->setMinimumSize(QSize(21, 24));
        btnEditFile->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/img/C:/Users/quan2/Downloads/pencil.png);"));

        gridLayout->addWidget(btnEditFile, 0, 1, 1, 1);

        btnDeleteFile = new QPushButton(layoutWidget1);
        btnDeleteFile->setObjectName("btnDeleteFile");
        btnDeleteFile->setMinimumSize(QSize(21, 24));
        btnDeleteFile->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/minus.png);\n"
""));

        gridLayout->addWidget(btnDeleteFile, 1, 0, 1, 1);

        addFileAccount = new QPushButton(layoutWidget1);
        addFileAccount->setObjectName("addFileAccount");
        addFileAccount->setMinimumSize(QSize(21, 24));
        addFileAccount->setStyleSheet(QString::fromUtf8("image: url(:/img/C:/Users/quan2/Downloads/add.png);\n"
""));

        gridLayout->addWidget(addFileAccount, 0, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        frame_6 = new QFrame(layoutWidget1);
        frame_6->setObjectName("frame_6");
        frame_6->setMinimumSize(QSize(311, 101));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        layoutWidget3 = new QWidget(frame_6);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(10, 10, 294, 82));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_11 = new QLabel(layoutWidget3);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(61, 41));
        label_11->setStyleSheet(QString::fromUtf8("border-radius:50%;\n"
"image: url(:/img/C:/Users/quan2/Downloads/profile-user.png);"));

        verticalLayout_4->addWidget(label_11);

        pushButton_7 = new QPushButton(layoutWidget3);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(61, 31));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: darkred;\n"
"color:white;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;"));

        verticalLayout_4->addWidget(pushButton_7);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(221, 16));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_3);

        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(211, 16));
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(221, 16));
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_3->addWidget(frame_6);


        verticalLayout_6->addWidget(frame_2);

        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 38)
            tableWidget->setColumnCount(38);
        QFont font3;
        font3.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font3);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font3);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font3);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font3);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font3);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font3);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font3);
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font3);
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font3);
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font3);
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font3);
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font3);
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font3);
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font3);
        tableWidget->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font3);
        tableWidget->setHorizontalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font3);
        tableWidget->setHorizontalHeaderItem(16, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font3);
        tableWidget->setHorizontalHeaderItem(17, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font3);
        tableWidget->setHorizontalHeaderItem(18, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setFont(font3);
        tableWidget->setHorizontalHeaderItem(19, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setFont(font3);
        tableWidget->setHorizontalHeaderItem(20, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font3);
        tableWidget->setHorizontalHeaderItem(21, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font3);
        tableWidget->setHorizontalHeaderItem(22, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setFont(font3);
        tableWidget->setHorizontalHeaderItem(23, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setFont(font3);
        tableWidget->setHorizontalHeaderItem(24, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setFont(font3);
        tableWidget->setHorizontalHeaderItem(25, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setFont(font3);
        tableWidget->setHorizontalHeaderItem(26, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setFont(font3);
        tableWidget->setHorizontalHeaderItem(27, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFont(font3);
        tableWidget->setHorizontalHeaderItem(28, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFont(font3);
        tableWidget->setHorizontalHeaderItem(29, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setFont(font3);
        tableWidget->setHorizontalHeaderItem(30, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setFont(font3);
        tableWidget->setHorizontalHeaderItem(31, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setFont(font3);
        tableWidget->setHorizontalHeaderItem(32, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setFont(font3);
        tableWidget->setHorizontalHeaderItem(33, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        __qtablewidgetitem34->setFont(font3);
        tableWidget->setHorizontalHeaderItem(34, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setFont(font3);
        tableWidget->setHorizontalHeaderItem(35, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setFont(font3);
        tableWidget->setHorizontalHeaderItem(36, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setFont(font3);
        tableWidget->setHorizontalHeaderItem(37, __qtablewidgetitem37);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setMinimumSize(QSize(1081, 571));
        tableWidget->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color: #503C3C;\n"
"border-radius:15px;"));
        tableWidget->setSortingEnabled(true);

        verticalLayout_6->addWidget(tableWidget);


        horizontalLayout_5->addLayout(verticalLayout_6);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Auto Worker", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Ch\341\272\241y t\306\260\306\241ng t\303\241c     ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\245u h\303\254nh chung", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "C\341\272\245u h\303\254nh t\306\260\306\241ng t\303\241c", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "C\341\272\245u h\303\254nh hi\341\273\203n th\341\273\213", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "T\303\240i kho\341\272\243n \304\221\303\243 x\303\263a", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Auto G\341\273\241 Checkpoint", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\304\220\303\243 ch\341\273\215n:", nullptr));
        lblCountSelect->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "T\341\272\245t c\341\272\243:", nullptr));
        lblCountTotal->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Chrome:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        metroButton1->setText(QCoreApplication::translate("MainWindow", "Close Chromedriver", nullptr));
        button9->setText(QCoreApplication::translate("MainWindow", "Nh\341\272\255p t\303\240i kho\341\272\243n", nullptr));
        pushButton_2->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Th\306\260 m\341\273\245c:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "L\341\273\215c:", nullptr));
        btnLoadAcc->setText(QString());
        btnEditFile->setText(QString());
        btnDeleteFile->setText(QString());
        addFileAccount->setText(QString());
        label_11->setText(QString());
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "H\341\273\215 t\303\252n: ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "M\303\243 Thi\341\272\277t b\341\273\213: ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "S\304\220T: ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Ch\341\273\215n", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "STT", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Uid", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Token", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Cookies", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "T\303\252n", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "B\341\272\241n B\303\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "PagePro5", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y sinh", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Gi\341\273\233i t\303\255nh", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(15);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "M\341\272\255t kh\341\272\251u", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->horizontalHeaderItem(16);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Mail Kh\303\264i Ph\341\273\245c", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->horizontalHeaderItem(17);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "M\341\272\255t kh\341\272\251u Mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->horizontalHeaderItem(18);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Backup", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->horizontalHeaderItem(19);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "M\303\243 2FA", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(20);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Proxy", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->horizontalHeaderItem(21);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y t\341\272\241o t\303\240i kho\341\272\243n", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->horizontalHeaderItem(22);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Avatar", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->horizontalHeaderItem(23);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "Profile", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->horizontalHeaderItem(24);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Th\306\260 M\341\273\245c", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->horizontalHeaderItem(25);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "L\341\272\247n T\306\260\306\241ng T\303\241c Cu\341\273\221i", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->horizontalHeaderItem(26);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "T\303\254nh Tr\341\272\241ng", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->horizontalHeaderItem(27);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Ghi Ch\303\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->horizontalHeaderItem(28);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Status282", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->horizontalHeaderItem(29);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->horizontalHeaderItem(30);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Home Town", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->horizontalHeaderItem(31);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Current City", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->horizontalHeaderItem(32);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Dating", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->horizontalHeaderItem(33);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "Ads", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->horizontalHeaderItem(34);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "BM", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->horizontalHeaderItem(35);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "FbBlock", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->horizontalHeaderItem(36);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "Job", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->horizontalHeaderItem(37);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "Tr\341\272\241ng th\303\241i", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
