/********************************************************************************
** Form generated from reading UI file 'fcauhinhtuongtac.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCAUHINHTUONGTAC_H
#define UI_FCAUHINHTUONGTAC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fCauhinhtuongtac
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *btnAdd;
    QPushButton *btnCancel;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *cbbKichban;
    QPushButton *pushButton;
    QCheckBox *checkBox_5;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_6;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox;
    QLabel *label_4;
    QSpinBox *spinBox_2;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_7;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *spinBox_3;
    QLabel *label_5;
    QSpinBox *spinBox_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QComboBox *comboBox;
    QCheckBox *checkBox_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_15;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_17;
    QCheckBox *checkBox_18;
    QCheckBox *checkBox_19;
    QCheckBox *checkBox_20;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBox_21;
    QCheckBox *checkBox_22;
    QCheckBox *checkBox_23;
    QCheckBox *checkBox_24;
    QCheckBox *checkBox_25;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_26;
    QCheckBox *checkBox_27;
    QCheckBox *checkBox_28;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkBox_29;
    QCheckBox *checkBox_30;
    QCheckBox *checkBox_31;
    QCheckBox *checkBox_32;
    QCheckBox *checkBox_33;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBox_34;
    QCheckBox *checkBox_35;

    void setupUi(QDialog *fCauhinhtuongtac)
    {
        if (fCauhinhtuongtac->objectName().isEmpty())
            fCauhinhtuongtac->setObjectName("fCauhinhtuongtac");
        fCauhinhtuongtac->resize(930, 554);
        widget = new QWidget(fCauhinhtuongtac);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(320, 490, 291, 41));
        horizontalLayout_13 = new QHBoxLayout(widget);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(widget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));

        horizontalLayout_13->addWidget(btnAdd);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setStyleSheet(QString::fromUtf8("background-color: darkred;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));

        horizontalLayout_13->addWidget(btnCancel);

        widget1 = new QWidget(fCauhinhtuongtac);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 10, 878, 451));
        horizontalLayout_12 = new QHBoxLayout(widget1);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(widget1);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName("checkBox");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, checkBox);

        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName("checkBox_3");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, checkBox_3);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName("checkBox_2");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, checkBox_2);

        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName("checkBox_4");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, checkBox_4);


        verticalLayout->addLayout(formLayout_2);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget1);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);


        gridLayout_2->addLayout(formLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget1);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        cbbKichban = new QComboBox(groupBox_3);
        cbbKichban->setObjectName("cbbKichban");

        horizontalLayout->addWidget(cbbKichban);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName("pushButton");
        QFont font;
        font.setBold(true);
        pushButton->setFont(font);

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName("checkBox_5");

        verticalLayout_2->addWidget(checkBox_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName("checkBox_6");

        horizontalLayout_3->addWidget(checkBox_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        spinBox = new QSpinBox(groupBox_3);
        spinBox->setObjectName("spinBox");

        horizontalLayout_2->addWidget(spinBox);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        spinBox_2 = new QSpinBox(groupBox_3);
        spinBox_2->setObjectName("spinBox_2");

        horizontalLayout_2->addWidget(spinBox_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        checkBox_7 = new QCheckBox(groupBox_3);
        checkBox_7->setObjectName("checkBox_7");

        horizontalLayout_5->addWidget(checkBox_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        spinBox_3 = new QSpinBox(groupBox_3);
        spinBox_3->setObjectName("spinBox_3");

        horizontalLayout_4->addWidget(spinBox_3);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        spinBox_4 = new QSpinBox(groupBox_3);
        spinBox_4->setObjectName("spinBox_4");

        horizontalLayout_4->addWidget(spinBox_4);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_12->addLayout(verticalLayout_3);

        groupBox_4 = new QGroupBox(widget1);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMinimumSize(QSize(460, 0));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        checkBox_8 = new QCheckBox(groupBox_4);
        checkBox_8->setObjectName("checkBox_8");

        horizontalLayout_6->addWidget(checkBox_8);

        checkBox_9 = new QCheckBox(groupBox_4);
        checkBox_9->setObjectName("checkBox_9");

        horizontalLayout_6->addWidget(checkBox_9);

        comboBox = new QComboBox(groupBox_4);
        comboBox->setObjectName("comboBox");

        horizontalLayout_6->addWidget(comboBox);


        verticalLayout_4->addLayout(horizontalLayout_6);

        checkBox_10 = new QCheckBox(groupBox_4);
        checkBox_10->setObjectName("checkBox_10");

        verticalLayout_4->addWidget(checkBox_10);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        checkBox_11 = new QCheckBox(groupBox_4);
        checkBox_11->setObjectName("checkBox_11");

        horizontalLayout_7->addWidget(checkBox_11);

        checkBox_12 = new QCheckBox(groupBox_4);
        checkBox_12->setObjectName("checkBox_12");

        horizontalLayout_7->addWidget(checkBox_12);

        checkBox_13 = new QCheckBox(groupBox_4);
        checkBox_13->setObjectName("checkBox_13");

        horizontalLayout_7->addWidget(checkBox_13);

        checkBox_14 = new QCheckBox(groupBox_4);
        checkBox_14->setObjectName("checkBox_14");

        horizontalLayout_7->addWidget(checkBox_14);

        checkBox_15 = new QCheckBox(groupBox_4);
        checkBox_15->setObjectName("checkBox_15");

        horizontalLayout_7->addWidget(checkBox_15);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        checkBox_16 = new QCheckBox(groupBox_4);
        checkBox_16->setObjectName("checkBox_16");

        horizontalLayout_8->addWidget(checkBox_16);

        checkBox_17 = new QCheckBox(groupBox_4);
        checkBox_17->setObjectName("checkBox_17");

        horizontalLayout_8->addWidget(checkBox_17);

        checkBox_18 = new QCheckBox(groupBox_4);
        checkBox_18->setObjectName("checkBox_18");

        horizontalLayout_8->addWidget(checkBox_18);

        checkBox_19 = new QCheckBox(groupBox_4);
        checkBox_19->setObjectName("checkBox_19");

        horizontalLayout_8->addWidget(checkBox_19);

        checkBox_20 = new QCheckBox(groupBox_4);
        checkBox_20->setObjectName("checkBox_20");

        horizontalLayout_8->addWidget(checkBox_20);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        checkBox_21 = new QCheckBox(groupBox_4);
        checkBox_21->setObjectName("checkBox_21");

        horizontalLayout_9->addWidget(checkBox_21);

        checkBox_22 = new QCheckBox(groupBox_4);
        checkBox_22->setObjectName("checkBox_22");

        horizontalLayout_9->addWidget(checkBox_22);

        checkBox_23 = new QCheckBox(groupBox_4);
        checkBox_23->setObjectName("checkBox_23");

        horizontalLayout_9->addWidget(checkBox_23);

        checkBox_24 = new QCheckBox(groupBox_4);
        checkBox_24->setObjectName("checkBox_24");

        horizontalLayout_9->addWidget(checkBox_24);

        checkBox_25 = new QCheckBox(groupBox_4);
        checkBox_25->setObjectName("checkBox_25");

        horizontalLayout_9->addWidget(checkBox_25);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        checkBox_26 = new QCheckBox(groupBox_4);
        checkBox_26->setObjectName("checkBox_26");

        horizontalLayout_10->addWidget(checkBox_26);

        checkBox_27 = new QCheckBox(groupBox_4);
        checkBox_27->setObjectName("checkBox_27");

        horizontalLayout_10->addWidget(checkBox_27);

        checkBox_28 = new QCheckBox(groupBox_4);
        checkBox_28->setObjectName("checkBox_28");

        horizontalLayout_10->addWidget(checkBox_28);


        verticalLayout_5->addLayout(horizontalLayout_10);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        checkBox_29 = new QCheckBox(groupBox_4);
        checkBox_29->setObjectName("checkBox_29");

        verticalLayout_7->addWidget(checkBox_29);

        checkBox_30 = new QCheckBox(groupBox_4);
        checkBox_30->setObjectName("checkBox_30");

        verticalLayout_7->addWidget(checkBox_30);

        checkBox_31 = new QCheckBox(groupBox_4);
        checkBox_31->setObjectName("checkBox_31");

        verticalLayout_7->addWidget(checkBox_31);

        checkBox_32 = new QCheckBox(groupBox_4);
        checkBox_32->setObjectName("checkBox_32");

        verticalLayout_7->addWidget(checkBox_32);

        checkBox_33 = new QCheckBox(groupBox_4);
        checkBox_33->setObjectName("checkBox_33");

        verticalLayout_7->addWidget(checkBox_33);


        horizontalLayout_11->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        checkBox_34 = new QCheckBox(groupBox_4);
        checkBox_34->setObjectName("checkBox_34");

        verticalLayout_8->addWidget(checkBox_34);

        checkBox_35 = new QCheckBox(groupBox_4);
        checkBox_35->setObjectName("checkBox_35");

        verticalLayout_8->addWidget(checkBox_35);


        horizontalLayout_11->addLayout(verticalLayout_8);


        verticalLayout_6->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);


        horizontalLayout_12->addWidget(groupBox_4);


        retranslateUi(fCauhinhtuongtac);

        QMetaObject::connectSlotsByName(fCauhinhtuongtac);
    } // setupUi

    void retranslateUi(QDialog *fCauhinhtuongtac)
    {
        fCauhinhtuongtac->setWindowTitle(QCoreApplication::translate("fCauhinhtuongtac", "Dialog", nullptr));
        btnAdd->setText(QCoreApplication::translate("fCauhinhtuongtac", "L\306\260u", nullptr));
        btnCancel->setText(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\303\263ng", nullptr));
        groupBox->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "Tr\306\260\341\273\233c khi ch\341\272\241y", nullptr));
        checkBox->setText(QCoreApplication::translate("fCauhinhtuongtac", "S\341\273\255 d\341\273\245ng profile chrome", nullptr));
        checkBox_3->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\263a cache chrome", nullptr));
        checkBox_2->setText(QCoreApplication::translate("fCauhinhtuongtac", "Check wall account", nullptr));
        checkBox_4->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\241o tr\341\273\231n th\341\273\251 t\341\273\261 t\303\240i kho\341\272\243n", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\304\203ng nh\341\272\255p", nullptr));
        label->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ki\341\273\203u \304\221\304\203ng nh\341\272\255p:", nullptr));
        label_2->setText(QCoreApplication::translate("fCauhinhtuongtac", "Web \304\221\304\203ng nh\341\272\255p:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "T\306\260\306\241ng t\303\241c", nullptr));
        label_3->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ch\341\273\215n k\341\273\213ch b\341\272\243n: ", nullptr));
        pushButton->setText(QCoreApplication::translate("fCauhinhtuongtac", "Qu\341\272\243n l\303\275 k\341\273\213ch b\341\272\243n", nullptr));
        checkBox_5->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\241o tr\341\273\231n th\341\273\251 t\341\273\261 h\303\240nh \304\221\341\273\231ng", nullptr));
        checkBox_6->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i h\341\272\241n th\341\273\235i gian ch\341\272\241y/t\303\240i kho\341\272\243n (gi\303\242y)", nullptr));
        label_4->setText(QCoreApplication::translate("fCauhinhtuongtac", ">", nullptr));
        checkBox_7->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i h\341\272\241n th\341\273\235i gian ch\341\272\241y/k\341\273\213ch b\341\272\243n (ph\303\272t)", nullptr));
        label_5->setText(QCoreApplication::translate("fCauhinhtuongtac", ">", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "Sau khi t\306\260\306\241ng t\303\241c", nullptr));
        checkBox_8->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y cookie", nullptr));
        checkBox_9->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y token", nullptr));
        checkBox_10->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y c\341\272\255p nh\341\272\255t th\303\264ng tin", nullptr));
        checkBox_11->setText(QCoreApplication::translate("fCauhinhtuongtac", "Name", nullptr));
        checkBox_12->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i t\303\255nh", nullptr));
        checkBox_13->setText(QCoreApplication::translate("fCauhinhtuongtac", "Birthday", nullptr));
        checkBox_14->setText(QCoreApplication::translate("fCauhinhtuongtac", "Email", nullptr));
        checkBox_15->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ng\303\240y t\341\272\241o", nullptr));
        checkBox_16->setText(QCoreApplication::translate("fCauhinhtuongtac", "Friend", nullptr));
        checkBox_17->setText(QCoreApplication::translate("fCauhinhtuongtac", "Group", nullptr));
        checkBox_18->setText(QCoreApplication::translate("fCauhinhtuongtac", "Follow", nullptr));
        checkBox_19->setText(QCoreApplication::translate("fCauhinhtuongtac", "Phone", nullptr));
        checkBox_20->setText(QCoreApplication::translate("fCauhinhtuongtac", "Avatar", nullptr));
        checkBox_21->setText(QCoreApplication::translate("fCauhinhtuongtac", "Page", nullptr));
        checkBox_22->setText(QCoreApplication::translate("fCauhinhtuongtac", "Page pro5", nullptr));
        checkBox_23->setText(QCoreApplication::translate("fCauhinhtuongtac", "BM", nullptr));
        checkBox_24->setText(QCoreApplication::translate("fCauhinhtuongtac", "Dating", nullptr));
        checkBox_25->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ads", nullptr));
        checkBox_26->setText(QCoreApplication::translate("fCauhinhtuongtac", "Location", nullptr));
        checkBox_27->setText(QCoreApplication::translate("fCauhinhtuongtac", "Hometown, CurrentCity", nullptr));
        checkBox_28->setText(QCoreApplication::translate("fCauhinhtuongtac", "Fb Block", nullptr));
        checkBox_29->setText(QCoreApplication::translate("fCauhinhtuongtac", "C\303\264ng khai danh s\303\241ch b\341\272\241n b\303\250", nullptr));
        checkBox_30->setText(QCoreApplication::translate("fCauhinhtuongtac", "B\341\272\255t duy\341\273\207t b\303\240i vi\341\272\277t tr\303\252n t\306\260\341\273\235ng", nullptr));
        checkBox_31->setText(QCoreApplication::translate("fCauhinhtuongtac", "Cho ph\303\251p ng\306\260\341\273\235i kh\303\241c Follow", nullptr));
        checkBox_32->setText(QCoreApplication::translate("fCauhinhtuongtac", "C\341\272\245u h\303\254nh t\303\240i kho\341\272\243n", nullptr));
        checkBox_33->setText(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\304\203ng xu\341\272\245t t\303\240i kho\341\272\243n", nullptr));
        checkBox_34->setText(QCoreApplication::translate("fCauhinhtuongtac", "Check spam", nullptr));
        checkBox_35->setText(QCoreApplication::translate("fCauhinhtuongtac", "Backup Database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fCauhinhtuongtac: public Ui_fCauhinhtuongtac {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCAUHINHTUONGTAC_H
