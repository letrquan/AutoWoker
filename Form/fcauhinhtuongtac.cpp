#include "fcauhinhtuongtac.h"
#include "Form/ui_fcauhinhtuongtac.h"
#include "../maxcare/interactsql.h"
fCauhinhtuongtac::fCauhinhtuongtac(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fCauhinhtuongtac)
{
    ui->setupUi(this);
}

fCauhinhtuongtac::~fCauhinhtuongtac()
{
    delete ui;
}

void fCauhinhtuongtac::LoadcbbKichBan(){
    int num = -1;
    if(ui->cbbKichban->currentIndex() != -1){
        num = ui->cbbKichban->currentIndex();
    }
    QVariantList allKichBan = *InteractSQL::GetAllKichBan();
}
