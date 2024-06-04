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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fCauhinhtuongtac
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QCheckBox *ckbCreateProfile;
    QCheckBox *ckbXoaCache;
    QCheckBox *ckbCheckLiveUid;
    QCheckBox *ckbRandonThuTuTaiKhoan;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cbbTypeLogin;
    QComboBox *cbbFaceBookWeb;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *cbbKichban;
    QPushButton *btnQuanlyKichBan;
    QCheckBox *ckbRandomHanhDong;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *ckbGioiHanThoiGianChayTaiKhoan;
    QFrame *plGioiHanThoiGianChayTaiKhoan;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_15;
    QSpinBox *nudThoiGianChayTaiKhoanFrom;
    QLabel *label_4;
    QSpinBox *nudThoiGianChayTaiKhoanTo;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *ckbGioiHanThoiGianChayKichBan;
    QFrame *plGioiHanThoiGianChayKichBan;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_16;
    QSpinBox *nudThoiGianChayKichBanFrom;
    QLabel *label_5;
    QSpinBox *nudThoiGianChayKichBanTo;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *ckbGetCookie;
    QCheckBox *ckbGetToken;
    QComboBox *cbbGetToken;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *ckbCapNhatThongTin;
    QCheckBox *ckbCapNhatThongTinTruocKhiTuongTac;
    QFrame *plCapNhatThongTin;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *ckbName;
    QCheckBox *ckbGioiTinh;
    QCheckBox *ckbBirthday;
    QCheckBox *ckbEmail;
    QCheckBox *ckbNgayTao;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *ckbFriend;
    QCheckBox *ckbGroup;
    QCheckBox *ckbFollow;
    QCheckBox *ckbPhone;
    QCheckBox *ckbAvatar;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *ckbPage;
    QCheckBox *ckbPagePro5;
    QCheckBox *ckbBM;
    QCheckBox *ckbDating;
    QCheckBox *ckbAds;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *ckbLocation;
    QCheckBox *ckbHomeTown;
    QCheckBox *ckbFb_Block;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *ckbCongKhaiBanBe;
    QCheckBox *ckbReviewTag;
    QCheckBox *ckbAllowFollow;
    QCheckBox *ckbCauHinhTaiKhoan;
    QCheckBox *ckbLogOut;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *ckbCheckSpam;
    QCheckBox *ckbBackupDB;
    QCheckBox *ckbWallPost;
    QCheckBox *ckbBackupDataBase_3;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *btnAdd;
    QPushButton *btnCancel;

    void setupUi(QDialog *fCauhinhtuongtac)
    {
        if (fCauhinhtuongtac->objectName().isEmpty())
            fCauhinhtuongtac->setObjectName("fCauhinhtuongtac");
        fCauhinhtuongtac->resize(913, 492);
        widget = new QWidget(fCauhinhtuongtac);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 868, 459));
        gridLayout_7 = new QGridLayout(widget);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        ckbCreateProfile = new QCheckBox(groupBox);
        ckbCreateProfile->setObjectName("ckbCreateProfile");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, ckbCreateProfile);

        ckbXoaCache = new QCheckBox(groupBox);
        ckbXoaCache->setObjectName("ckbXoaCache");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, ckbXoaCache);

        ckbCheckLiveUid = new QCheckBox(groupBox);
        ckbCheckLiveUid->setObjectName("ckbCheckLiveUid");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, ckbCheckLiveUid);

        ckbRandonThuTuTaiKhoan = new QCheckBox(groupBox);
        ckbRandonThuTuTaiKhoan->setObjectName("ckbRandonThuTuTaiKhoan");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, ckbRandonThuTuTaiKhoan);


        verticalLayout->addLayout(formLayout_2);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        cbbTypeLogin = new QComboBox(groupBox_2);
        cbbTypeLogin->setObjectName("cbbTypeLogin");

        formLayout->setWidget(0, QFormLayout::FieldRole, cbbTypeLogin);

        cbbFaceBookWeb = new QComboBox(groupBox_2);
        cbbFaceBookWeb->setObjectName("cbbFaceBookWeb");

        formLayout->setWidget(1, QFormLayout::FieldRole, cbbFaceBookWeb);


        gridLayout_2->addLayout(formLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget);
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

        btnQuanlyKichBan = new QPushButton(groupBox_3);
        btnQuanlyKichBan->setObjectName("btnQuanlyKichBan");
        QFont font;
        font.setBold(true);
        btnQuanlyKichBan->setFont(font);

        horizontalLayout->addWidget(btnQuanlyKichBan);


        verticalLayout_2->addLayout(horizontalLayout);

        ckbRandomHanhDong = new QCheckBox(groupBox_3);
        ckbRandomHanhDong->setObjectName("ckbRandomHanhDong");

        verticalLayout_2->addWidget(ckbRandomHanhDong);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        ckbGioiHanThoiGianChayTaiKhoan = new QCheckBox(groupBox_3);
        ckbGioiHanThoiGianChayTaiKhoan->setObjectName("ckbGioiHanThoiGianChayTaiKhoan");

        horizontalLayout_3->addWidget(ckbGioiHanThoiGianChayTaiKhoan);

        plGioiHanThoiGianChayTaiKhoan = new QFrame(groupBox_3);
        plGioiHanThoiGianChayTaiKhoan->setObjectName("plGioiHanThoiGianChayTaiKhoan");
        plGioiHanThoiGianChayTaiKhoan->setFrameShape(QFrame::StyledPanel);
        plGioiHanThoiGianChayTaiKhoan->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(plGioiHanThoiGianChayTaiKhoan);
        gridLayout_5->setObjectName("gridLayout_5");
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        nudThoiGianChayTaiKhoanFrom = new QSpinBox(plGioiHanThoiGianChayTaiKhoan);
        nudThoiGianChayTaiKhoanFrom->setObjectName("nudThoiGianChayTaiKhoanFrom");

        horizontalLayout_15->addWidget(nudThoiGianChayTaiKhoanFrom);

        label_4 = new QLabel(plGioiHanThoiGianChayTaiKhoan);
        label_4->setObjectName("label_4");

        horizontalLayout_15->addWidget(label_4);

        nudThoiGianChayTaiKhoanTo = new QSpinBox(plGioiHanThoiGianChayTaiKhoan);
        nudThoiGianChayTaiKhoanTo->setObjectName("nudThoiGianChayTaiKhoanTo");

        horizontalLayout_15->addWidget(nudThoiGianChayTaiKhoanTo);


        gridLayout_5->addLayout(horizontalLayout_15, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(plGioiHanThoiGianChayTaiKhoan);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        ckbGioiHanThoiGianChayKichBan = new QCheckBox(groupBox_3);
        ckbGioiHanThoiGianChayKichBan->setObjectName("ckbGioiHanThoiGianChayKichBan");

        horizontalLayout_5->addWidget(ckbGioiHanThoiGianChayKichBan);

        plGioiHanThoiGianChayKichBan = new QFrame(groupBox_3);
        plGioiHanThoiGianChayKichBan->setObjectName("plGioiHanThoiGianChayKichBan");
        plGioiHanThoiGianChayKichBan->setFrameShape(QFrame::StyledPanel);
        plGioiHanThoiGianChayKichBan->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(plGioiHanThoiGianChayKichBan);
        gridLayout_6->setObjectName("gridLayout_6");
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        nudThoiGianChayKichBanFrom = new QSpinBox(plGioiHanThoiGianChayKichBan);
        nudThoiGianChayKichBanFrom->setObjectName("nudThoiGianChayKichBanFrom");

        horizontalLayout_16->addWidget(nudThoiGianChayKichBanFrom);

        label_5 = new QLabel(plGioiHanThoiGianChayKichBan);
        label_5->setObjectName("label_5");

        horizontalLayout_16->addWidget(label_5);

        nudThoiGianChayKichBanTo = new QSpinBox(plGioiHanThoiGianChayKichBan);
        nudThoiGianChayKichBanTo->setObjectName("nudThoiGianChayKichBanTo");

        horizontalLayout_16->addWidget(nudThoiGianChayKichBanTo);


        gridLayout_6->addLayout(horizontalLayout_16, 0, 0, 1, 1);


        horizontalLayout_5->addWidget(plGioiHanThoiGianChayKichBan);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");

        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_12->addLayout(verticalLayout_3);

        groupBox_4 = new QGroupBox(widget);
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
        ckbGetCookie = new QCheckBox(groupBox_4);
        ckbGetCookie->setObjectName("ckbGetCookie");

        horizontalLayout_6->addWidget(ckbGetCookie);

        ckbGetToken = new QCheckBox(groupBox_4);
        ckbGetToken->setObjectName("ckbGetToken");

        horizontalLayout_6->addWidget(ckbGetToken);

        cbbGetToken = new QComboBox(groupBox_4);
        cbbGetToken->setObjectName("cbbGetToken");

        horizontalLayout_6->addWidget(cbbGetToken);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        ckbCapNhatThongTin = new QCheckBox(groupBox_4);
        ckbCapNhatThongTin->setObjectName("ckbCapNhatThongTin");

        horizontalLayout_14->addWidget(ckbCapNhatThongTin);

        ckbCapNhatThongTinTruocKhiTuongTac = new QCheckBox(groupBox_4);
        ckbCapNhatThongTinTruocKhiTuongTac->setObjectName("ckbCapNhatThongTinTruocKhiTuongTac");

        horizontalLayout_14->addWidget(ckbCapNhatThongTinTruocKhiTuongTac);


        verticalLayout_4->addLayout(horizontalLayout_14);


        verticalLayout_6->addLayout(verticalLayout_4);

        plCapNhatThongTin = new QFrame(groupBox_4);
        plCapNhatThongTin->setObjectName("plCapNhatThongTin");
        plCapNhatThongTin->setFrameShape(QFrame::StyledPanel);
        plCapNhatThongTin->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(plCapNhatThongTin);
        gridLayout_4->setObjectName("gridLayout_4");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        ckbName = new QCheckBox(plCapNhatThongTin);
        ckbName->setObjectName("ckbName");

        horizontalLayout_7->addWidget(ckbName);

        ckbGioiTinh = new QCheckBox(plCapNhatThongTin);
        ckbGioiTinh->setObjectName("ckbGioiTinh");

        horizontalLayout_7->addWidget(ckbGioiTinh);

        ckbBirthday = new QCheckBox(plCapNhatThongTin);
        ckbBirthday->setObjectName("ckbBirthday");

        horizontalLayout_7->addWidget(ckbBirthday);

        ckbEmail = new QCheckBox(plCapNhatThongTin);
        ckbEmail->setObjectName("ckbEmail");

        horizontalLayout_7->addWidget(ckbEmail);

        ckbNgayTao = new QCheckBox(plCapNhatThongTin);
        ckbNgayTao->setObjectName("ckbNgayTao");

        horizontalLayout_7->addWidget(ckbNgayTao);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        ckbFriend = new QCheckBox(plCapNhatThongTin);
        ckbFriend->setObjectName("ckbFriend");

        horizontalLayout_8->addWidget(ckbFriend);

        ckbGroup = new QCheckBox(plCapNhatThongTin);
        ckbGroup->setObjectName("ckbGroup");

        horizontalLayout_8->addWidget(ckbGroup);

        ckbFollow = new QCheckBox(plCapNhatThongTin);
        ckbFollow->setObjectName("ckbFollow");

        horizontalLayout_8->addWidget(ckbFollow);

        ckbPhone = new QCheckBox(plCapNhatThongTin);
        ckbPhone->setObjectName("ckbPhone");

        horizontalLayout_8->addWidget(ckbPhone);

        ckbAvatar = new QCheckBox(plCapNhatThongTin);
        ckbAvatar->setObjectName("ckbAvatar");

        horizontalLayout_8->addWidget(ckbAvatar);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        ckbPage = new QCheckBox(plCapNhatThongTin);
        ckbPage->setObjectName("ckbPage");

        horizontalLayout_9->addWidget(ckbPage);

        ckbPagePro5 = new QCheckBox(plCapNhatThongTin);
        ckbPagePro5->setObjectName("ckbPagePro5");

        horizontalLayout_9->addWidget(ckbPagePro5);

        ckbBM = new QCheckBox(plCapNhatThongTin);
        ckbBM->setObjectName("ckbBM");

        horizontalLayout_9->addWidget(ckbBM);

        ckbDating = new QCheckBox(plCapNhatThongTin);
        ckbDating->setObjectName("ckbDating");

        horizontalLayout_9->addWidget(ckbDating);

        ckbAds = new QCheckBox(plCapNhatThongTin);
        ckbAds->setObjectName("ckbAds");

        horizontalLayout_9->addWidget(ckbAds);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        ckbLocation = new QCheckBox(plCapNhatThongTin);
        ckbLocation->setObjectName("ckbLocation");

        horizontalLayout_10->addWidget(ckbLocation);

        ckbHomeTown = new QCheckBox(plCapNhatThongTin);
        ckbHomeTown->setObjectName("ckbHomeTown");

        horizontalLayout_10->addWidget(ckbHomeTown);

        ckbFb_Block = new QCheckBox(plCapNhatThongTin);
        ckbFb_Block->setObjectName("ckbFb_Block");

        horizontalLayout_10->addWidget(ckbFb_Block);


        verticalLayout_5->addLayout(horizontalLayout_10);


        gridLayout_4->addLayout(verticalLayout_5, 0, 0, 1, 1);


        verticalLayout_6->addWidget(plCapNhatThongTin);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        ckbCongKhaiBanBe = new QCheckBox(groupBox_4);
        ckbCongKhaiBanBe->setObjectName("ckbCongKhaiBanBe");

        verticalLayout_7->addWidget(ckbCongKhaiBanBe);

        ckbReviewTag = new QCheckBox(groupBox_4);
        ckbReviewTag->setObjectName("ckbReviewTag");

        verticalLayout_7->addWidget(ckbReviewTag);

        ckbAllowFollow = new QCheckBox(groupBox_4);
        ckbAllowFollow->setObjectName("ckbAllowFollow");

        verticalLayout_7->addWidget(ckbAllowFollow);

        ckbCauHinhTaiKhoan = new QCheckBox(groupBox_4);
        ckbCauHinhTaiKhoan->setObjectName("ckbCauHinhTaiKhoan");

        verticalLayout_7->addWidget(ckbCauHinhTaiKhoan);

        ckbLogOut = new QCheckBox(groupBox_4);
        ckbLogOut->setObjectName("ckbLogOut");

        verticalLayout_7->addWidget(ckbLogOut);


        horizontalLayout_11->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        ckbCheckSpam = new QCheckBox(groupBox_4);
        ckbCheckSpam->setObjectName("ckbCheckSpam");

        verticalLayout_8->addWidget(ckbCheckSpam);

        ckbBackupDB = new QCheckBox(groupBox_4);
        ckbBackupDB->setObjectName("ckbBackupDB");

        verticalLayout_8->addWidget(ckbBackupDB);

        ckbWallPost = new QCheckBox(groupBox_4);
        ckbWallPost->setObjectName("ckbWallPost");

        verticalLayout_8->addWidget(ckbWallPost);

        ckbBackupDataBase_3 = new QCheckBox(groupBox_4);
        ckbBackupDataBase_3->setObjectName("ckbBackupDataBase_3");

        verticalLayout_8->addWidget(ckbBackupDataBase_3);


        horizontalLayout_11->addLayout(verticalLayout_8);


        verticalLayout_6->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);


        horizontalLayout_12->addWidget(groupBox_4);


        gridLayout_7->addLayout(horizontalLayout_12, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        btnAdd = new QPushButton(widget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setMinimumSize(QSize(0, 30));
        btnAdd->setMaximumSize(QSize(150, 16777215));
        btnAdd->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background-color: rgb(53, 120, 229);\n"
"color:white;\n"
"font-weight:bold;"));

        horizontalLayout_13->addWidget(btnAdd);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setMinimumSize(QSize(0, 30));
        btnCancel->setMaximumSize(QSize(150, 16777215));
        btnCancel->setStyleSheet(QString::fromUtf8("background-color: darkred;\n"
"border-radius:20px;\n"
"color:white;\n"
"font-weight:bold;"));

        horizontalLayout_13->addWidget(btnCancel);


        gridLayout_7->addLayout(horizontalLayout_13, 1, 0, 1, 1);


        retranslateUi(fCauhinhtuongtac);

        QMetaObject::connectSlotsByName(fCauhinhtuongtac);
    } // setupUi

    void retranslateUi(QDialog *fCauhinhtuongtac)
    {
        fCauhinhtuongtac->setWindowTitle(QCoreApplication::translate("fCauhinhtuongtac", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "Tr\306\260\341\273\233c khi ch\341\272\241y", nullptr));
        ckbCreateProfile->setText(QCoreApplication::translate("fCauhinhtuongtac", "S\341\273\255 d\341\273\245ng profile chrome", nullptr));
        ckbXoaCache->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\263a cache chrome", nullptr));
        ckbCheckLiveUid->setText(QCoreApplication::translate("fCauhinhtuongtac", "Check wall account", nullptr));
        ckbRandonThuTuTaiKhoan->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\241o tr\341\273\231n th\341\273\251 t\341\273\261 t\303\240i kho\341\272\243n", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\304\203ng nh\341\272\255p", nullptr));
        label->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ki\341\273\203u \304\221\304\203ng nh\341\272\255p:", nullptr));
        label_2->setText(QCoreApplication::translate("fCauhinhtuongtac", "Web \304\221\304\203ng nh\341\272\255p:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "T\306\260\306\241ng t\303\241c", nullptr));
        label_3->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ch\341\273\215n k\341\273\213ch b\341\272\243n: ", nullptr));
        btnQuanlyKichBan->setText(QCoreApplication::translate("fCauhinhtuongtac", "Qu\341\272\243n l\303\275 k\341\273\213ch b\341\272\243n", nullptr));
        ckbRandomHanhDong->setText(QCoreApplication::translate("fCauhinhtuongtac", "X\303\241o tr\341\273\231n th\341\273\251 t\341\273\261 h\303\240nh \304\221\341\273\231ng", nullptr));
        ckbGioiHanThoiGianChayTaiKhoan->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i h\341\272\241n th\341\273\235i gian ch\341\272\241y/t\303\240i kho\341\272\243n (gi\303\242y)", nullptr));
        label_4->setText(QCoreApplication::translate("fCauhinhtuongtac", ">", nullptr));
        ckbGioiHanThoiGianChayKichBan->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i h\341\272\241n th\341\273\235i gian ch\341\272\241y/k\341\273\213ch b\341\272\243n (ph\303\272t)", nullptr));
        label_5->setText(QCoreApplication::translate("fCauhinhtuongtac", ">", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("fCauhinhtuongtac", "Sau khi t\306\260\306\241ng t\303\241c", nullptr));
        ckbGetCookie->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y cookie", nullptr));
        ckbGetToken->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y token", nullptr));
        ckbCapNhatThongTin->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\273\261 \304\221\341\273\231ng l\341\272\245y c\341\272\255p nh\341\272\255t th\303\264ng tin", nullptr));
        ckbCapNhatThongTinTruocKhiTuongTac->setText(QCoreApplication::translate("fCauhinhtuongtac", "Tr\306\260\341\273\233c khi t\306\260\306\241ng t\303\241c", nullptr));
        ckbName->setText(QCoreApplication::translate("fCauhinhtuongtac", "Name", nullptr));
        ckbGioiTinh->setText(QCoreApplication::translate("fCauhinhtuongtac", "Gi\341\273\233i t\303\255nh", nullptr));
        ckbBirthday->setText(QCoreApplication::translate("fCauhinhtuongtac", "Birthday", nullptr));
        ckbEmail->setText(QCoreApplication::translate("fCauhinhtuongtac", "Email", nullptr));
        ckbNgayTao->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ng\303\240y t\341\272\241o", nullptr));
        ckbFriend->setText(QCoreApplication::translate("fCauhinhtuongtac", "Friend", nullptr));
        ckbGroup->setText(QCoreApplication::translate("fCauhinhtuongtac", "Group", nullptr));
        ckbFollow->setText(QCoreApplication::translate("fCauhinhtuongtac", "Follow", nullptr));
        ckbPhone->setText(QCoreApplication::translate("fCauhinhtuongtac", "Phone", nullptr));
        ckbAvatar->setText(QCoreApplication::translate("fCauhinhtuongtac", "Avatar", nullptr));
        ckbPage->setText(QCoreApplication::translate("fCauhinhtuongtac", "Page", nullptr));
        ckbPagePro5->setText(QCoreApplication::translate("fCauhinhtuongtac", "Page pro5", nullptr));
        ckbBM->setText(QCoreApplication::translate("fCauhinhtuongtac", "BM", nullptr));
        ckbDating->setText(QCoreApplication::translate("fCauhinhtuongtac", "Dating", nullptr));
        ckbAds->setText(QCoreApplication::translate("fCauhinhtuongtac", "Ads", nullptr));
        ckbLocation->setText(QCoreApplication::translate("fCauhinhtuongtac", "Location", nullptr));
        ckbHomeTown->setText(QCoreApplication::translate("fCauhinhtuongtac", "Hometown, CurrentCity", nullptr));
        ckbFb_Block->setText(QCoreApplication::translate("fCauhinhtuongtac", "Fb Block", nullptr));
        ckbCongKhaiBanBe->setText(QCoreApplication::translate("fCauhinhtuongtac", "C\303\264ng khai danh s\303\241ch b\341\272\241n b\303\250", nullptr));
        ckbReviewTag->setText(QCoreApplication::translate("fCauhinhtuongtac", "B\341\272\255t duy\341\273\207t b\303\240i vi\341\272\277t tr\303\252n t\306\260\341\273\235ng", nullptr));
        ckbAllowFollow->setText(QCoreApplication::translate("fCauhinhtuongtac", "Cho ph\303\251p ng\306\260\341\273\235i kh\303\241c Follow", nullptr));
        ckbCauHinhTaiKhoan->setText(QCoreApplication::translate("fCauhinhtuongtac", "C\341\272\245u h\303\254nh t\303\240i kho\341\272\243n", nullptr));
        ckbLogOut->setText(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\304\203ng xu\341\272\245t t\303\240i kho\341\272\243n", nullptr));
        ckbCheckSpam->setText(QCoreApplication::translate("fCauhinhtuongtac", "Check spam", nullptr));
        ckbBackupDB->setText(QCoreApplication::translate("fCauhinhtuongtac", "Backup Database", nullptr));
        ckbWallPost->setText(QCoreApplication::translate("fCauhinhtuongtac", "Wall Post", nullptr));
        ckbBackupDataBase_3->setText(QCoreApplication::translate("fCauhinhtuongtac", "T\341\272\257t Popup Chat", nullptr));
        btnAdd->setText(QCoreApplication::translate("fCauhinhtuongtac", "L\306\260u", nullptr));
        btnCancel->setText(QCoreApplication::translate("fCauhinhtuongtac", "\304\220\303\263ng", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fCauhinhtuongtac: public Ui_fCauhinhtuongtac {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCAUHINHTUONGTAC_H
