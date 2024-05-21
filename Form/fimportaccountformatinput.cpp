#include "fimportaccountformatinput.h"
#include "Form/ui_fimportaccountformatinput.h"
#include "../maxcare/MessageBoxHelper.h"
#include "../Utils/Utils.h"
fImportAccountFormatInput::fImportAccountFormatInput(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fImportAccountFormatInput)
{
    ui->setupUi(this);
    this->setWindowTitle("Thêm định dạng nhập tài khoản");
}

fImportAccountFormatInput::~fImportAccountFormatInput()
{
    delete ui;
}

void fImportAccountFormatInput::on_btnAdd_clicked()
{
    QList<QComboBox*> list = {
        ui->cbbDinhDang1, ui->cbbDinhDang2, ui->cbbDinhDang3, ui->cbbDinhDang4, ui->cbbDinhDang5, ui->cbbDinhDang6, ui->cbbDinhDang7, ui->cbbDinhDang8, ui->cbbDinhDang9, ui->cbbDinhDang10,
        ui->cbbDinhDang11
    };
    for(int i =0; i<list.size();i++){
        format = format + list[i]->currentText()+"|";
    }
    format = Utils::trimEnd(format,'|');
    if(format ==""){
        MessageBoxHelper::Show("Vui lòng chọn định dạng tài khoản!", 3);
    }else{
        close();
    }
}


void fImportAccountFormatInput::on_btnCancel_clicked()
{
    this->close();
}

