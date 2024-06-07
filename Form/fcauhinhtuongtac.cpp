#include "fcauhinhtuongtac.h"
#include "Form/ui_fcauhinhtuongtac.h"
#include "../maxcare/interactsql.h"
#include "../maxcare/MessageBoxHelper.h"
#include <QMessageBox>
#include "../maxcare/SettingsTool.h"
#include "fdanhsachkichban_old.h"
#include "../MCommon/Common.h"
fCauhinhtuongtac::fCauhinhtuongtac(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fCauhinhtuongtac)
{
    ui->setupUi(this);
    fCauhinhtuongtac_Load();
    this->setWindowTitle("Cấu hình tương tác");
}

fCauhinhtuongtac::~fCauhinhtuongtac()
{
    delete ui;
}
void fCauhinhtuongtac::fCauhinhtuongtac_Load(){
    LoadcbbKichBan();
    LoadSettings();
    CheckedChangedFull();
}

void fCauhinhtuongtac::LoadcbbKichBan(){
    int num = -1;
    if(ui->cbbKichban->currentIndex() != -1){
        num = ui->cbbKichban->currentIndex();
    }
    QVariantList allKichBan = *InteractSQL::GetAllKichBan();
    for (int i = 0; i < allKichBan.size(); ++i) {
        auto rowMap = allKichBan[i].toMap();
        ui->cbbKichban->addItem(rowMap["Ten"].toString() , rowMap["Id_KichBan"].toString());
    }
    if (num != -1 && num != 0 && ui->cbbKichban->count() >= num + 1)
    {
        ui->cbbKichban->setCurrentIndex(num);
    }
    else if (ui->cbbKichban->count() > 0)
    {
        ui->cbbKichban->setCurrentIndex(0);
    }
}


void fCauhinhtuongtac::on_ckbCapNhatThongTin_stateChanged(int arg1)
{
    ui->plCapNhatThongTin->setEnabled(ui->ckbCapNhatThongTinTruocKhiTuongTac->checkState());
    ui->ckbCapNhatThongTinTruocKhiTuongTac->setVisible(ui->ckbCapNhatThongTin->checkState());
    if (!(ui->ckbCapNhatThongTinTruocKhiTuongTac->checkState() == Qt::Checked))
    {
        ui->ckbCapNhatThongTinTruocKhiTuongTac->setCheckState(Qt::Unchecked);
    }
}
void fCauhinhtuongtac::LoadSettings(){
    try
    {
        ui->cbbTypeLogin->setCurrentIndex(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("typeLogin"));
        ui->cbbFaceBookWeb->setCurrentIndex(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("typeBrowserLogin"));
        ui->ckbCreateProfile->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCreateProfile"));
        ui->ckbGetToken->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGetToken"));
        ui->cbbGetToken->setCurrentIndex(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("typeToken"));
        ui->ckbGetCookie->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGetCookie"));
        ui->ckbCapNhatThongTin->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCapNhatThongTin"));
        //
        ui->ckbCapNhatThongTinTruocKhiTuongTac->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCapNhatThongTinTruocKhiTuongTac", false));
        //
        ui->ckbName->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbName", true));
        ui->ckbGioiTinh->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGender", true));
        ui->ckbBirthday->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBirthday", true));
        ui->ckbNgayTao->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbNgayTao", true));
        ui->ckbEmail->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbEmail"));
        ui->ckbFriend->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbFriend", true));
        ui->ckbGroup->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGroup", true));
        ui->ckbPage->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbPage", true));
        ui->ckbFollow->setChecked (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbFollow", true));
        ui->ckbPhone->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbPhone", true));
        ui->ckbAvatar->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbAvatar", true));
        //
        ui->ckbDating->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbDating", false));
        ui->ckbAds->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbAds", false));
        ui->ckbBM->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBM", false));
        ui->ckbHomeTown->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbHometown", false));
        ui->ckbPagePro5->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbPagePro5", false));
        string_0 = SettingsTool::GetSettings("configInteractGeneral").GetValue("txtBackupDBPath", QString::fromUtf8(qgetenv("LocalAppData")) + "\\database");
        //
        ui->ckbFb_Block->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbFbBlock", false));
        //
        ui->ckbLocation->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbLocation", true));
        ui->ckbCheckLiveUid->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCheckLiveUid"));
        // ui->ckbDontSaveBrowser->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbDontSaveBrowser");
        // ui->ckbRepeatAll->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRepeatAll"));
        // ui->nudDelayTurnFrom.Value = SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudDelayTurnFrom");
        // ui->nudDelayTurnTo.Value = SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudDelayTurnTo");
        // ui->nudSoLuotChay.Value(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudSoLuotChay");
        ui->ckbLogOut->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbLogOut"));
        ui->ckbAllowFollow->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbAllowFollow"));
        ui->ckbReviewTag->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbReviewTag"));
        // ui->ckbBatThongBaoDangNhap->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBatThongBaoDangNhap");
        //
        ui->ckbWallPost->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbWallPosts", false));
        //
        ui->ckbCauHinhTaiKhoan->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCauHinhTaiKhoan"));
        ui->ckbCheckSpam->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCheckSpam"));
        ui->ckbCongKhaiBanBe->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCongKhaiBanBe"));
        ui->ckbBackupDB->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBackupDB", true));
        ui->ckbRandonThuTuTaiKhoan->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRandomThuTuTaiKhoan"));
        ui->cbbKichban->setCurrentText(SettingsTool::GetSettings("configInteractGeneral").GetValue("cbbKichBan"));
        ui->ckbRandomHanhDong->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRandomHanhDong"));
        ui->ckbXoaCache->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbXoaCache"));
        // ui->ckbCheckBanBeGoiY->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCheckBanBeGoiY"));
        ui->ckbGioiHanThoiGianChayTaiKhoan->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGioiHanThoiGianChayTaiKhoan"));
        ui->nudThoiGianChayTaiKhoanFrom->setValue(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayTaiKhoanFrom", 1));
        ui->nudThoiGianChayTaiKhoanTo->setValue(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayTaiKhoanTo", 1));
        ui->ckbGioiHanThoiGianChayKichBan->setChecked(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGioiHanThoiGianChayKichBan"));
        ui->nudThoiGianChayKichBanFrom->setValue(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayKichBanFrom", 1));
        ui->nudThoiGianChayKichBanTo->setValue(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayKichBanTo", 1));
    }
    catch(...)
    {
    }
}



void fCauhinhtuongtac::on_checkBox_9_clicked()
{
    if (ui->ckbGetToken->checkState() == Qt::Checked && MessageBoxHelper::ShowYesNo("Sư\u0309 du\u0323ng ti\u0301nh năng na\u0300y co\u0301 thê\u0309 dâ\u0303n đê\u0301n ta\u0300i khoa\u0309n Facebook bi\u0323 kho\u0301a!\r\nBa\u0323n co\u0301 chă\u0301c vâ\u0303n muô\u0301n sư\u0309 du\u0323ng?") == QMessageBox::No)
    {
        ui->ckbGetToken->setCheckState(Qt::Unchecked);
    }
}



void fCauhinhtuongtac::on_ckbGioiHanThoiGianChayTaiKhoan_stateChanged(int arg1)
{
    if(ui->ckbGioiHanThoiGianChayTaiKhoan->checkState() == Qt::Checked){
        ui->plGioiHanThoiGianChayTaiKhoan->setEnabled(true);
    }else{
        ui->plGioiHanThoiGianChayTaiKhoan->setEnabled(false);
    }
}




void fCauhinhtuongtac::on_ckbGioiHanThoiGianChayKichBan_stateChanged(int arg1)
{
    if(ui->ckbGioiHanThoiGianChayKichBan->checkState() == Qt::Checked){
        ui->plGioiHanThoiGianChayKichBan->setEnabled(true);
    }else{
        ui->plGioiHanThoiGianChayKichBan->setEnabled(false);
    }
}


void fCauhinhtuongtac::on_ckbGetToken_stateChanged(int arg1)
{
    ui->cbbGetToken->setEnabled(((ui->ckbGetToken->checkState() == Qt::Checked) ? true :false));
}


void fCauhinhtuongtac::on_ckbGroup_clicked()
{
    if (ui->ckbGroup->checkState() == Qt::Checked && MessageBoxHelper::ShowYesNo("Sư\u0309 du\u0323ng ti\u0301nh năng na\u0300y co\u0301 thê\u0309 dâ\u0303n đê\u0301n ta\u0300i khoa\u0309n Facebook bi\u0323 kho\u0301a!\r\nBa\u0323n co\u0301 chă\u0301c vâ\u0303n muô\u0301n sư\u0309 du\u0323ng?") == QMessageBox::No)
    {
        ui->ckbGroup->setCheckState(Qt::Unchecked);
    }
}


void fCauhinhtuongtac::on_btnAdd_clicked()
{
    SettingsTool::GetSettings("configInteractGeneral").Update("typeLogin", ui->cbbTypeLogin->currentIndex());
    SettingsTool::GetSettings("configInteractGeneral").Update("typeBrowserLogin", ui->cbbFaceBookWeb->currentIndex());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCreateProfile", ui->ckbCreateProfile->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGetToken", ui->ckbGetToken->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("typeToken", ui->cbbGetToken->currentIndex());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGetCookie", ui->ckbGetCookie->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCapNhatThongTin", ui->ckbCapNhatThongTin->isChecked());
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCapNhatThongTinTruocKhiTuongTac", ui->ckbCapNhatThongTinTruocKhiTuongTac->isChecked());
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbName", ui->ckbName->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGender", ui->ckbGioiTinh->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbBirthday", ui->ckbBirthday->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbNgayTao", ui->ckbNgayTao->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbEmail", ui->ckbEmail->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbFriend", ui->ckbFriend->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGroup", ui->ckbGroup->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbPage", ui->ckbPage->isChecked());
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbPagePro5", ui->ckbPagePro5->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbDating", ui->ckbDating->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbAds", ui->ckbAds->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbBM", ui->ckbBM->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbHometown", ui->ckbHomeTown->isChecked());
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbFbBlock", ui->ckbFb_Block->isChecked());
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbWallPosts", ui->ckbWallPost->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("txtBackupDBPath", string_0);
    //
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbFollow", ui->ckbFollow->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbPhone", ui->ckbPhone->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbLocation", ui->ckbLocation->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbAvatar", ui->ckbAvatar->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCheckLiveUid", ui->ckbCheckLiveUid->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("RepeatAllVIP", "false");
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbLogOut", ui->ckbLogOut->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbAllowFollow", ui->ckbAllowFollow->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbReviewTag", ui->ckbReviewTag->isChecked());
    // SettingsTool::GetSettings("configInteractGeneral").Update("ckbBatThongBaoDangNhap", ui->ckbBatThongBaoDangNhap->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCauHinhTaiKhoan", ui->ckbCauHinhTaiKhoan->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCheckSpam", ui->ckbCheckSpam->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbCongKhaiBanBe", ui->ckbCongKhaiBanBe->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbBackupDB", ui->ckbBackupDB->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbRandomThuTuTaiKhoan", ui->ckbRandonThuTuTaiKhoan->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("cbbKichBan", ui->cbbKichban->currentData());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbRandomHanhDong", ui->ckbRandomHanhDong->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbXoaCache", ui->ckbXoaCache->isChecked());
    // SettingsTool::GetSettings("configInteractGeneral").Update("ckbCheckBanBeGoiY", ckbCheckBanBeGoiY->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGioiHanThoiGianChayTaiKhoan",ui->ckbGioiHanThoiGianChayTaiKhoan->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("nudThoiGianChayTaiKhoanFrom", ui->nudThoiGianChayTaiKhoanFrom->value());
    SettingsTool::GetSettings("configInteractGeneral").Update("nudThoiGianChayTaiKhoanTo", ui->nudThoiGianChayTaiKhoanTo->value());
    SettingsTool::GetSettings("configInteractGeneral").Update("ckbGioiHanThoiGianChayKichBan", ui->ckbGioiHanThoiGianChayKichBan->isChecked());
    SettingsTool::GetSettings("configInteractGeneral").Update("nudThoiGianChayKichBanFrom", ui->nudThoiGianChayKichBanFrom->value());
    SettingsTool::GetSettings("configInteractGeneral").Update("nudThoiGianChayKichBanTo", ui->nudThoiGianChayKichBanTo->value());
    SettingsTool::SaveSettings("configInteractGeneral");
    if (MessageBoxHelper::ShowYesNo("Lưu thành công, ba\u0323n co\u0301 muô\u0301n đo\u0301ng cư\u0309a sô\u0309?") == QMessageBox::Yes)
    {
        close();
    }
}

void fCauhinhtuongtac::CheckedChangedFull(){
    on_ckbCapNhatThongTin_stateChanged(0);
    on_ckbGioiHanThoiGianChayKichBan_stateChanged(0);
    on_ckbGioiHanThoiGianChayKichBan_stateChanged(0);
    on_ckbGetToken_stateChanged(0);
}


void fCauhinhtuongtac::on_btnQuanlyKichBan_clicked()
{
    QString kickBan = "";
    try
    {
        if (ui->cbbKichban->count() > 0)
        {
            kickBan = ui->cbbKichban->currentText().mid(ui->cbbKichban->currentText().indexOf('.') + 1).trimmed();
        }
    }
    catch(...)
    {
    }
    Common::ShowForm(new fDanhSachKichBan_Old(kickBan));
    LoadcbbKichBan();
}


void fCauhinhtuongtac::on_btnCancel_clicked()
{
    this->close();
}

