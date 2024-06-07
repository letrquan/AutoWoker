#include "fcauhinhchung.h"
#include "ui_fcauhinhchung.h"
#include "../maxcare/Language.h"
fCauHinhChung::fCauHinhChung(JSON_Settings &data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fCauHinhChung), settings(data)
{
    ui->setupUi(this);
    Language::SetLanguage(this);
    this->setWindowTitle("Cấu hình chung");
    fCauhinhChung_Load();
}

fCauHinhChung::~fCauHinhChung()
{
    delete ui;
}
void fCauHinhChung::fCauhinhChung_Load(){
    LoadCbbTocDoGoVanBan();
    LoadCbbChangeIP();
}
void fCauHinhChung::LoadCbbTocDoGoVanBan(){
    ui->cbbTocDoGoVanBan->clear();
    QStringList lstItem = {
        "Chậm",
        "Bình thường", "Nhanh"
    };
    for (int var = 0; var < lstItem.count(); ++var) {
        Language::GetValue(lstItem[var]),QString::number(var);
    }
}
void fCauHinhChung::LoadCbbChangeIP(){
    QMap<QString, QString> dictionary;

    dictionary.insert("0", "Không đổi IP");
    dictionary.insert("2", "Dcom");
    dictionary.insert("1", "HMA");
    dictionary.insert("9", "Proxy");
    dictionary.insert("13", "https://minproxy.vn/");
    dictionary.insert("7", "https://tinsoftproxy.com/");
    dictionary.insert("8", "Xproxy, Mobi, Eager, S Proxy, OBC proxy");
    dictionary.insert("14", "OBC Proxy");
    dictionary.insert("11", "https://proxyv6.net/");
    dictionary.insert("12", "http://proxy.shoplike.vn/");
    dictionary.insert("15", "https://proxyfb.com/");
    dictionary.insert("10", "https://tmproxy.com/");

    // Example usage
    for (auto it = dictionary.constBegin(); it != dictionary.constEnd(); ++it) {
        ui->cbbChangeIP->addItem(Language::GetValue(it.value()),it.key());
    }
}
void fCauHinhChung::LoadCbbProxy(){
    QMap<QString, QString> dictionary;

    dictionary.insert("0", "Đã gán vào mỗi tài khoản");
    dictionary.insert("1", "Ngẫu nhiên trong danh sách");

    // Example usage
    for (auto it = dictionary.constBegin(); it != dictionary.constEnd(); ++it) {
        ui->cbbChangeIP->addItem(Language::GetValue(it.value()),it.key());
    }
}
void fCauHinhChung::on_btnCancel_clicked()
{
    this->close();
}

