/********************************************************************************
** Form generated from reading UI file 'fdanhsachkichban_old.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FDANHSACHKICHBAN_OLD_H
#define UI_FDANHSACHKICHBAN_OLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fDanhSachKichBan_Old
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *dtgvKichBan;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QTableWidget *dtgvhanhDong;

    void setupUi(QDialog *fDanhSachKichBan_Old)
    {
        if (fDanhSachKichBan_Old->objectName().isEmpty())
            fDanhSachKichBan_Old->setObjectName("fDanhSachKichBan_Old");
        fDanhSachKichBan_Old->resize(935, 515);
        widget = new QWidget(fDanhSachKichBan_Old);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 901, 491));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        dtgvKichBan = new QTableWidget(groupBox);
        if (dtgvKichBan->columnCount() < 3)
            dtgvKichBan->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        dtgvKichBan->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dtgvKichBan->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        dtgvKichBan->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        dtgvKichBan->setObjectName("dtgvKichBan");

        gridLayout->addWidget(dtgvKichBan, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName("gridLayout_2");
        dtgvhanhDong = new QTableWidget(groupBox_3);
        if (dtgvhanhDong->columnCount() < 4)
            dtgvhanhDong->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        dtgvhanhDong->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        dtgvhanhDong->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        dtgvhanhDong->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        dtgvhanhDong->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        dtgvhanhDong->setObjectName("dtgvhanhDong");
        dtgvhanhDong->setMinimumSize(QSize(600, 0));

        gridLayout_2->addWidget(dtgvhanhDong, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        retranslateUi(fDanhSachKichBan_Old);

        QMetaObject::connectSlotsByName(fDanhSachKichBan_Old);
    } // setupUi

    void retranslateUi(QDialog *fDanhSachKichBan_Old)
    {
        fDanhSachKichBan_Old->setWindowTitle(QCoreApplication::translate("fDanhSachKichBan_Old", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("fDanhSachKichBan_Old", "Danh s\303\241ch k\341\273\213ch b\341\272\243n", nullptr));
        QTableWidgetItem *___qtablewidgetitem = dtgvKichBan->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "STT", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dtgvKichBan->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "Id_KichBan", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dtgvKichBan->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "T\303\252n K\341\273\213ch B\341\272\243n", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("fDanhSachKichBan_Old", "Dah s\303\241ch h\303\240nh \304\221\341\273\231ng", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = dtgvhanhDong->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "STT", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = dtgvhanhDong->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = dtgvhanhDong->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "T\303\252n H\303\240nh \304\220\341\273\231ng", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = dtgvhanhDong->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("fDanhSachKichBan_Old", "Lo\341\272\241i T\306\260\306\241ng T\303\241c", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fDanhSachKichBan_Old: public Ui_fDanhSachKichBan_Old {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FDANHSACHKICHBAN_OLD_H
