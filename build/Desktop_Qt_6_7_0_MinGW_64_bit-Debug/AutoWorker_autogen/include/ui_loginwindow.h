/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QFrame *frame;
    QLineEdit *accountEdit;
    QLineEdit *passwordEdit;
    QPushButton *LoginButton;
    QCheckBox *remeberBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QLabel *versionLabel;
    QFrame *frame_2;
    QLabel *gifLabel;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(956, 634);
        LoginWindow->setAutoFillBackground(false);
        LoginWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"border: 1px solid black;\n"
"    border-radius: 15px;\n"
"    background-color: rgba(255, 255, 255, 255);\n"
"}"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border-radius:15px;\n"
"background-color: black\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame = new QFrame(frame_3);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 391, 591));
        frame->setStyleSheet(QString::fromUtf8("background-color:#FFEC9E;\n"
"color:black;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        accountEdit = new QLineEdit(frame);
        accountEdit->setObjectName("accountEdit");
        accountEdit->setGeometry(QRect(60, 230, 251, 35));
        accountEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"        border: 1px solid #a1a1a1;\n"
"        border-radius: 15px; \n"
"       padding: 6px;\n"
"       background-color: #ffffff;\n"
"        color: #000000;\n"
"        font-size: 16px;\n"
"    }\n"
"    QLineEdit:focus {\n"
"        border: 2px solid #007BFF; \n"
"    }"));
        passwordEdit = new QLineEdit(frame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(60, 310, 251, 35));
        passwordEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"        border: 1px solid #a1a1a1;\n"
"        border-radius: 15px; \n"
"       padding: 6px;\n"
"       background-color: #ffffff;\n"
"        color: #000000;\n"
"        font-size: 16px;\n"
"    }\n"
"    QLineEdit:focus {\n"
"        border: 2px solid #007BFF; \n"
"    }"));
        passwordEdit->setEchoMode(QLineEdit::Password);
        LoginButton = new QPushButton(frame);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(60, 400, 251, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto Light")});
        font.setUnderline(false);
        font.setStrikeOut(false);
        LoginButton->setFont(font);
        LoginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #ED9455;\n"
"       border-radius: 15px; \n"
"        color: #ffffff; \n"
"        padding: 10px 20px; \n"
"        font-size: 18px;\n"
"        border: none;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #0056b3; \n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #0056b3;\n"
"    }"));
        remeberBox = new QCheckBox(frame);
        remeberBox->setObjectName("remeberBox");
        remeberBox->setGeometry(QRect(60, 350, 131, 22));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Roboto Light")});
        font1.setPointSize(10);
        remeberBox->setFont(font1);
        remeberBox->setStyleSheet(QString::fromUtf8("color:black;\n"
"border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
""));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 270, 81, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Roboto Light")});
        font2.setPointSize(12);
        font2.setBold(false);
        label_2->setFont(font2);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 120, 121, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Roboto")});
        font3.setPointSize(22);
        font3.setBold(true);
        font3.setUnderline(false);
        label_3->setFont(font3);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 190, 91, 31));
        label->setFont(font2);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(110, 50, 161, 41));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Jersey 10")});
        font4.setPointSize(22);
        label_4->setFont(font4);
        label_4->setStyleSheet(QString::fromUtf8("color:#FBC02D;"));
        versionLabel = new QLabel(frame);
        versionLabel->setObjectName("versionLabel");
        versionLabel->setGeometry(QRect(120, 550, 191, 16));
        versionLabel->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        frame_2 = new QFrame(frame_3);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(410, 10, 511, 591));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFEC9E;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gifLabel = new QLabel(frame_2);
        gifLabel->setObjectName("gifLabel");
        gifLabel->setGeometry(QRect(40, 50, 441, 511));

        verticalLayout->addWidget(frame_3);

        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "MainWindow", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginWindow", "\304\220\304\203ng nh\341\272\255p", nullptr));
        remeberBox->setText(QCoreApplication::translate("LoginWindow", "Nh\341\273\233 t\303\240i kho\341\272\243n", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "M\341\272\255t kh\341\272\251u", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWindow", "Sign In", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "T\303\240i kho\341\272\243n", nullptr));
        label_4->setText(QCoreApplication::translate("LoginWindow", "Auto Worker", nullptr));
        versionLabel->setText(QCoreApplication::translate("LoginWindow", "TextLabel", nullptr));
        gifLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
