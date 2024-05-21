#include "faddfile.h"
#include "Form/ui_faddfile.h"
#include "../maxcare/Language.h"
#include "../maxcare/MessageBoxHelper.h"
#include "../MCommon/commonsql.h"
fAddFile::fAddFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fAddFile)
{
    ui->setupUi(this);
    isAdd = false;
    Language::SetLanguage(this);
    this->setWindowTitle("Add file");
}

fAddFile::~fAddFile()
{
    delete ui;
}

bool fAddFile::isAdd;
void fAddFile::on_btnAdd_clicked()
{
    QString text = ui->txbNameFile->text().trimmed();
    if(text ==""){
        MessageBoxHelper::Show("Vui lòng điền tên thư mục!");
        ui->txbNameFile->setFocus();
    }else if(CommonSQL::CheckExitsFile(text)){
        MessageBoxHelper::Show("Tên thư mục này đã tồn tại, vui lòng nhập tên khác!");
        ui->txbNameFile->setFocus();
    }else if(CommonSQL::InsertFileToDatabase(text)){
        isAdd = true;
        if(MessageBoxHelper::ShowYesNo("Thêm thành công, ba\u0323n co\u0301 muô\u0301n đo\u0301ng cư\u0309a sô\u0309?")){
            this->close();
        }
    }else{
        MessageBoxHelper::Show("Thêm thư mục lỗi!");
    }
}




void fAddFile::on_btnCancel_clicked()
{
   this->close();
}


