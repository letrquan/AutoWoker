#include "fcauhinhhienthi.h"
#include "Form/ui_fcauhinhhienthi.h"
#include "../maxcare/Language.h"
#include "../maxcare/SettingsTool.h"
fCauHinhHienThi::fCauHinhHienThi(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fCauHinhHienThi)
{
    ui->setupUi(this);
    Language::SetLanguage(this);
    fCauHinhHienThi_Load();
    this->setWindowTitle("Cấu hình hiển thị");
}

fCauHinhHienThi::~fCauHinhHienThi()
{
    delete ui;
}

void fCauHinhHienThi::fCauHinhHienThi_Load(){
    ui->ckbToken->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("cToken"));
    ui->ckbCookie->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbCookie"));
    ui->ckmEmail->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbEmail"));
    ui->ckbTen->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbTen"));
    ui->ckbBanBe->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBanBe"));
    ui->ckbNhom->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNhom"));
    ui->ckbPage->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPage"));
    ui->ckbNgaySinh->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNgaySinh"));
    ui->ckbGioiTinh->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbGioiTinh"));
    ui->ckbMatKhau->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMatKhau"));
    ui->ckbMatKhauMail->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMatKhauMail"));
    ui->ckbBackup->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBackup"));
    ui->ckbMa2FA->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMa2FA"));
    ui->ckbUserAgent->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbUseragent"));
    ui->ckbProxy->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbProxy"));
    ui->ckbNgayTao->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNgayTao"));
    ui->ckbAvatar->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbAvatar"));
    ui->ckbProfile->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbProfile"));
    ui->ckbTinhTrang->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbTinhTrang"));
    ui->ckbThuMuc->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbThuMuc"));
    ui->ckbGhiChu->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbGhiChu"));
    ui->ckbTheodoi->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbFollow"));
    ui->ckbTuongTacCuoi->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbInteractEnd"));
    ui->ckbMailKhoiPhuc->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMailRecovery"));
    ui->ckbPhone->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPhone"));
    ui->ckbLocation->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbLocation"));
    //
    ui->ckbJob->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbJob"));
    ui->ckbStatus282->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbStatus282"));
    ui->ckbFbBlock->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbFbBlock"));
    //
    ui->ckbLuongSo->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("cbLuongSo"));


    ui->ckbPagePro5->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPagePro5", false));
    ui->ckbHomeTown->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbHometown", false));
    ui->ckbCurrentCity->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbCurrentCity", false));
    ui->ckbDating->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbDating", false));
    ui->ckbAds->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbAds", false));
    ui->ckbBM->setChecked(SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBM", false));
}

void fCauHinhHienThi::on_btnLuu_clicked()
{
    SettingsTool::GetSettings("configDatagridview").Update("cToken", ui->ckbToken->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbCookie", ui->ckbCookie->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbEmail", ui->ckmEmail->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbTen", ui->ckbTen->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbBanBe", ui->ckbBanBe->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbNhom", ui->ckbNhom->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbPage", ui->ckbPage->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbNgaySinh", ui->ckbNgaySinh->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbGioiTinh", ui->ckbGioiTinh->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbMatKhau", ui->ckbMatKhau->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbMatKhauMail", ui->ckbMatKhauMail->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbBackup", ui->ckbBackup->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbMa2FA", ui->ckbMa2FA->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbUseragent", ui->ckbUserAgent->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbProxy", ui->ckbProxy->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbNgayTao", ui->ckbNgayTao->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbAvatar", ui->ckbAvatar->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbProfile", ui->ckbProfile->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbTinhTrang", ui->ckbTinhTrang->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbThuMuc", ui->ckbThuMuc->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbGhiChu", ui->ckbGhiChu->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbFollow", ui->ckbTheodoi->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbInteractEnd", ui->ckbTuongTacCuoi->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbMailRecovery", ui->ckbMailKhoiPhuc->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbPhone", ui->ckbPhone->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbLocation", ui->ckbLocation->isChecked());

    SettingsTool::GetSettings("configDatagridview").Update("ckbFbBlock", ui->ckbFbBlock->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbJob", ui->ckbJob->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbStatus282", ui->ckbStatus282->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbPagePro5", ui->ckbPagePro5->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbHometown", ui->ckbHomeTown->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbCurrentCity", ui->ckbCurrentCity->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbDating", ui->ckbDating->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbAds", ui->ckbAds->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("ckbBM", ui->ckbBM->isChecked());
    SettingsTool::GetSettings("configDatagridview").Update("cbLuongSo", ui->ckbLuongSo->isChecked());
    if(ui->ckbMa2FA->isChecked() && !Base::CheckPassword()){
        SettingsTool::GetSettings("configDatagridview").Update("ckbMa2FA", false);
    }
    SettingsTool::SaveSettings("configDatagridview");
    this->close();
}



void fCauHinhHienThi::on_btnDong_clicked()
{
    this->close();
}

