#include "fchonthumuc.h"
#include "Form/ui_fchonthumuc.h"
#include "../maxcare/Language.h"
#include "../MCommon/commonsql.h"
#include "../maxcare/datagridviewhelper.h"
#include <QMessageBox>
#include "../MCommon/Common.h"
#include "../maxcare/MessageBoxHelper.h"
#include "qstandarditemmodel.h"
#include <QKeyEvent>
#include <qsqlrecord.h>
#include "../Utils/Utils.h"
fChonThuMuc::fChonThuMuc(bool isFromBin,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fChonThuMuc)
{
    ui->setupUi(this);
    isAdd = false;
    this->isFromBin = isFromBin;
    Language::SetLanguage(this);
    fChonThuMuc_Load();
}

fChonThuMuc::~fChonThuMuc()
{
    delete ui;
}
QList<QString> fChonThuMuc::lstChooseIdFiles;
QList<QString> fChonThuMuc::lstChooseIdFilesFromBin;
bool fChonThuMuc::isAdd;
void fChonThuMuc::on_button5_clicked()
{
    int index = ui->dtgvAcc->currentRow();
    QString statusDataGridView = DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, index - 1, "Id");
    QString statusDataGridView2 = DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, index, "Id");
    if (!statusDataGridView.isEmpty() || !statusDataGridView2.isEmpty()) {
        if (CommonSQL::UpdateThuTuThuMuc(statusDataGridView, statusDataGridView2)) {
            Common::SwapTableWidgetRows(ui->dtgvAcc, index, index - 1, 2);
            ui->dtgvAcc->clearSelection();
            ui->dtgvAcc->selectRow(index - 1);
        } else {
            QMessageBox::warning(ui->dtgvAcc, "Error", "Có lỗi xảy ra, vui lòng thử lại sau!");
        }
    }
}


void fChonThuMuc::on_btnAdd_clicked()
{
    isAdd =true;
    if(isFromBin){
        lstChooseIdFilesFromBin = *new QList<QString>();
        for(int i =0;i<ui->dtgvAcc->rowCount();i++){
            if(ui->dtgvAcc->item(i,0)->checkState()){
                lstChooseIdFilesFromBin.append(DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc,i,"Id"));
            }
        }
        if(lstChooseIdFilesFromBin.count()==0){
            MessageBoxHelper::Show("Vui lòng chọn ít nhất 1 thư mục!", 2);
            return;
        }
    }else{
        lstChooseIdFiles = *new QList<QString>();
        for(int j = 0;j<ui->dtgvAcc->rowCount();j++){
            if(ui->dtgvAcc->item(j,0)->checkState()){
                lstChooseIdFiles.append(DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, j, "Id"));
            }
        }
        if(lstChooseIdFiles.count()==0){
            MessageBoxHelper::Show("Vui lòng chọn ít nhất 1 thư mục!", 2);
            return;
        }
    }
    close();
}
void fChonThuMuc::LoadListFiles(const QList<QString> &lstIdFile){
    try {
        QVariantList* dataTable =  ((!isFromBin) ? CommonSQL::GetAllFilesFromDatabase() : CommonSQL::GetAllFilesFromDatabaseForBin());
        ui->dtgvAcc->insertRow(dataTable->size());
        int row = 0;
        if(!lstIdFile.isEmpty()){
            for(const QVariant &item : *dataTable){
                QVariantMap rowMap = item.toMap();
                if(lstIdFile.contains(rowMap["id"].toString())){
                    QTableWidgetItem *checkboxItem = new QTableWidgetItem();
                    checkboxItem->setFlags(checkboxItem->flags() | Qt::ItemIsUserCheckable);
                    checkboxItem->setCheckState(Qt::Checked);
                    ui->dtgvAcc->setItem(row,0, checkboxItem);
                    QTableWidgetItem *id = new QTableWidgetItem(rowMap["id"].toString());
                    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
                    QTableWidgetItem *name = new QTableWidgetItem(rowMap["name"].toString());
                    QTableWidgetItem *stt = new QTableWidgetItem(row+1);
                    name->setFlags(name->flags() & ~Qt::ItemIsEditable);
                    stt->setFlags(stt->flags() & ~Qt::ItemIsEditable);
                    ui->dtgvAcc->setItem(row,3, id);
                    ui->dtgvAcc->setItem(row,2, name);
                    ui->dtgvAcc->setItem(row,1,stt);
                }else{
                    QTableWidgetItem *checkboxItem = new QTableWidgetItem();
                    checkboxItem->setFlags(checkboxItem->flags() | Qt::ItemIsUserCheckable);
                    checkboxItem->setCheckState(Qt::Unchecked);
                    ui->dtgvAcc->setItem(row,0, checkboxItem);
                    QTableWidgetItem *id = new QTableWidgetItem(rowMap["id"].toString());
                    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
                    QTableWidgetItem *name = new QTableWidgetItem(rowMap["name"].toString());
                    QTableWidgetItem *stt = new QTableWidgetItem(row+1);
                    name->setFlags(name->flags() & ~Qt::ItemIsEditable);
                    stt->setFlags(stt->flags() & ~Qt::ItemIsEditable);
                    ui->dtgvAcc->setItem(row,3, id);
                    ui->dtgvAcc->setItem(row,2, name);
                    ui->dtgvAcc->setItem(row,1,stt);
                }
                row++;
            }
        }else{

        }
        UpdateSelectCountRecord();
        UpdateTotalCountRecord();
        if(CountSelectRow() == ui->dtgvAcc->rowCount()){
            ui->checkBox1->setCheckState(Qt::Checked);
        }else{
            ui->checkBox1->setCheckState(Qt::Unchecked);
        }
    } catch (...) {
    }
}
void fChonThuMuc::UpdateSelectCountRecord(){
    try {
        ui->lblCountChoose->setText(QString::number(CountSelectRow()));
    } catch (...) {
    }
}
int fChonThuMuc::CountSelectRow(){
    int num = 0;
    for (int i = 0; i < ui->dtgvAcc->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->dtgvAcc->item(i, 0);
        if (item->checkState() == Qt::Checked) {
            num++;
        }
    }
    return num;
}
void fChonThuMuc::fChonThuMuc_Load(){
    if(isFromBin){
        LoadListFiles(lstChooseIdFilesFromBin);
    }else{
        LoadListFiles(lstChooseIdFiles);
    }
}
void fChonThuMuc::UpdateTotalCountRecord(){
    try {
        ui->lblCountTotal->setText(QString::number(ui->dtgvAcc->rowCount()));
    } catch (...) {
    }
}

void fChonThuMuc::on_btnCancel_clicked()
{
    this->close();
}


void fChonThuMuc::on_dtgvAcc_cellChanged(int row, int column)
{
    if(row >-1 && column ==0){
        UpdateSelectCountRecord();
        if(CountSelectRow() == ui->dtgvAcc->rowCount()){
            ui->checkBox1->setCheckState(Qt::Checked);
        }else{
            ui->checkBox1->setCheckState(Qt::Unchecked);
        }
    }
}


void fChonThuMuc::on_dtgvAcc_cellDoubleClicked(int row, int column)
{
    try {
        QTableWidgetItem *checkboxItem = new QTableWidgetItem();
        checkboxItem->setFlags(checkboxItem->flags() | Qt::ItemIsUserCheckable);

        if(ui->dtgvAcc->item(ui->dtgvAcc->currentRow(),0)->checkState() == Qt::Checked){
            checkboxItem->setCheckState(Qt::Unchecked);
            ui->dtgvAcc->setItem(ui->dtgvAcc->currentRow(),0,checkboxItem);
        }else{
            checkboxItem->setCheckState(Qt::Checked);
            ui->dtgvAcc->setItem(ui->dtgvAcc->currentRow(),0,checkboxItem);
        }
    } catch (...) {
    }
}


void fChonThuMuc::on_dtgvAcc_cellClicked(int row, int column)
{
    // if(column !=0 || row <= -1){
    //     return;
    // }
    // try {
    //     QTableWidgetItem *checkboxItem = new QTableWidgetItem();
    //     checkboxItem->setFlags(checkboxItem->flags() | Qt::ItemIsUserCheckable);
    //     if(ui->dtgvAcc->item(ui->dtgvAcc->currentRow(),0)){
    //         checkboxItem->setCheckState(Qt::Unchecked);
    //         ui->dtgvAcc->setItem(ui->dtgvAcc->currentRow(),0,checkboxItem);
    //     }else{
    //         checkboxItem->setCheckState(Qt::Checked);
    //         ui->dtgvAcc->setItem(ui->dtgvAcc->currentRow(),0,checkboxItem);
    //     }
    // } catch (...) {
    // }
}



void fChonThuMuc::on_checkBox1_clicked(bool checked)
{
    if(checked == true){
        for (int i = 0; i < ui->dtgvAcc->rowCount(); i++)
        {
            DatagridviewHelper::SetStatusDataGridView(ui->dtgvAcc, i, 0, true);
        }
    }else{
        for (int i = 0; i < ui->dtgvAcc->rowCount(); i++)
        {
            DatagridviewHelper::SetStatusDataGridView(ui->dtgvAcc, i, 0, false);
        }
    }
}


void fChonThuMuc::on_button4_clicked()
{
    auto selectedRows = ui->dtgvAcc->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int index = selectedRows.first().row();
        if(index == ui->dtgvAcc->rowCount()-1){
            return;
        }
        QString statusDataGridView = DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, index + 1, "Id");
        QString statusDataGridView2 = DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, index, "Id");
        if(statusDataGridView + statusDataGridView2 != ""){
            if(CommonSQL::UpdateThuTuThuMuc(statusDataGridView,statusDataGridView2)){
                Common::SwapTableWidgetRows(ui->dtgvAcc,index,index+1,2);
                ui->dtgvAcc->clearSelection();
                ui->dtgvAcc->selectRow(index + 1);
            }else{
                MessageBoxHelper::Show("Co\u0301 lô\u0303i xa\u0309y ra, vui lo\u0300ng thư\u0309 la\u0323i sau!", 2);
            }
        }
        qDebug() << "First selected row index:" << index;
    }
}

void fChonThuMuc::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        auto selectedRanges = ui->dtgvAcc->selectedRanges();
        for (const auto &range : selectedRanges)
        {
            for (int row = range.topRow(); row <= range.bottomRow(); ++row)
            {
                QString currentStatus = DatagridviewHelper::GetStatusDataGridView(ui->dtgvAcc, row, "Id");
                DatagridviewHelper::SetStatusDataGridView(ui->dtgvAcc,row,"",(currentStatus.toLower() == "true" || currentStatus == "1"));
            }
        }
        CountSelectRow();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}
