/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
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
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QPushButton *btnInteract;
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
    QFrame *frame_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *metroButton1;
    QPushButton *button9;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QWidget *layoutWidget1;
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
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_11;
    QPushButton *pushButton_7;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QTableView *tableView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1382, 723);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"border-radius:15px;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(11, 11, 274, 705));
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

        btnInteract = new QPushButton(frame);
        btnInteract->setObjectName("btnInteract");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnInteract->sizePolicy().hasHeightForWidth());
        btnInteract->setSizePolicy(sizePolicy2);
        btnInteract->setMinimumSize(QSize(211, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Roboto Medium")});
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setItalic(false);
        btnInteract->setFont(font2);
        btnInteract->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";\n"
"font-weight:bold;\n"
"border-width: 2px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 20px;\n"
"qproperty-icon: url(:/img/img/play-button.png);\n"
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

        verticalLayout_5->addWidget(btnInteract);

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

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(292, 12, 1081, 121));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(1081, 121));
        frame_2->setLayoutDirection(Qt::RightToLeft);
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFBB70;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frame_2);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(9, 9, 1021, 103));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        metroButton1 = new QPushButton(layoutWidget);
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

        button9 = new QPushButton(layoutWidget);
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
        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(421, 40));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(frame_3);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 8, 397, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(31, 24));
        pushButton_2->setStyleSheet(QString::fromUtf8("image: url(:/img/img/search.png);\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;\n"
"background-color: black;"));

        horizontalLayout->addWidget(pushButton_2);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(191, 24));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));

        horizontalLayout->addWidget(lineEdit);

        cbbSearch = new QComboBox(layoutWidget1);
        cbbSearch->setObjectName("cbbSearch");
        cbbSearch->setMinimumSize(QSize(161, 24));
        cbbSearch->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px; /* Set the width of the border */\n"
"border-style: solid; /* Define the style of the border */\n"
"border-color: black; /* Define the color of the border */\n"
"border-radius: 5px;"));

        horizontalLayout->addWidget(cbbSearch);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(layoutWidget);
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
        btnLoadAcc = new QPushButton(layoutWidget);
        btnLoadAcc->setObjectName("btnLoadAcc");
        btnLoadAcc->setMinimumSize(QSize(21, 24));
        btnLoadAcc->setStyleSheet(QString::fromUtf8("image: url(:/img/img/refresh.png);"));

        gridLayout->addWidget(btnLoadAcc, 1, 1, 1, 1);

        btnEditFile = new QPushButton(layoutWidget);
        btnEditFile->setObjectName("btnEditFile");
        btnEditFile->setMinimumSize(QSize(21, 24));
        btnEditFile->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/img/img/pencil.png);"));

        gridLayout->addWidget(btnEditFile, 0, 1, 1, 1);

        btnDeleteFile = new QPushButton(layoutWidget);
        btnDeleteFile->setObjectName("btnDeleteFile");
        btnDeleteFile->setMinimumSize(QSize(21, 24));
        btnDeleteFile->setStyleSheet(QString::fromUtf8("image: url(:/img/img/minus.png);\n"
""));

        gridLayout->addWidget(btnDeleteFile, 1, 0, 1, 1);

        addFileAccount = new QPushButton(layoutWidget);
        addFileAccount->setObjectName("addFileAccount");
        addFileAccount->setMinimumSize(QSize(21, 24));
        addFileAccount->setStyleSheet(QString::fromUtf8("image: url(:/img/img/plus.png);\n"
""));

        gridLayout->addWidget(addFileAccount, 0, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        frame_6 = new QFrame(layoutWidget);
        frame_6->setObjectName("frame_6");
        frame_6->setMinimumSize(QSize(311, 101));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: #FFFBDA;\n"
"color:black;\n"
"font: 500 9pt \"Roboto Medium\";"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        layoutWidget2 = new QWidget(frame_6);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 10, 294, 82));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(61, 41));
        label_11->setStyleSheet(QString::fromUtf8("border-radius:50%;\n"
"image: url(:/img/C:/Users/quan2/Downloads/profile-user.png);"));

        verticalLayout_4->addWidget(label_11);

        pushButton_7 = new QPushButton(layoutWidget2);
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
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(221, 16));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_3);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(211, 16));
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(221, 16));
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("font-weight:bold;"));

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_3->addWidget(frame_6);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(292, 139, 1081, 571));
        tableView->setMinimumSize(QSize(1081, 571));
        tableView->setStyleSheet(QString::fromUtf8("background-color: #222831;\n"
"color: black;\n"
""));
        tableView->setShowGrid(true);
        tableView->setSortingEnabled(false);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Auto Worker", nullptr));
        btnInteract->setText(QCoreApplication::translate("MainWindow", "Ch\341\272\241y t\306\260\306\241ng t\303\241c     ", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
