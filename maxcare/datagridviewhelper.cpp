#include "datagridviewhelper.h"
#include <QHeaderView>
#include <mutex>
#include "../maxcare/updatestatus.h"
#include "../Utils/Utils.h"
#include "../MCommon/Common.h"
DatagridviewHelper::DatagridviewHelper() {}

void DatagridviewHelper::LoadDtgvAccFromDatatable(QTableView* dgv, AutoTable* tableAccount, bool isUseForBin){
    dgv->setModel(tableAccount);
    if(!isUseForBin){

    }


    // dgv->setRowCount(tableAccount->size());
    // if(!isUseForBin){
    //     auto row =0;
    //     for(const QVariant &item:*tableAccount){
    //         QVariantMap rowMap = item.toMap();
    //         for(int col =0;col<dgv->columnCount();col++){
    //             auto item = new QTableWidgetItem();
    //             if(col ==0){
    //                 item->setCheckState(Qt::Unchecked);
    //             }else if(col==1){
    //                 item->setData(Qt::DisplayRole,row+1);
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }else if(col == 38){
    //                 item->setData(Qt::DisplayRole,UpdateStatus::GetStatusById(rowMap["id"].toString()));
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }else{
    //                 item->setData(Qt::DisplayRole,rowMap[numToHeaderMap[col]].toString());
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }
    //             dgv->setItem(row,col,item);
    //         }
    //         row++;
    //     }
    // }else{
    //     auto row =0;
    //     for(const QVariant &item:*tableAccount){
    //         QVariantMap rowMap = item.toMap();
    //         for(int col =0;col<dgv->columnCount();col++){
    //             auto item = new QTableWidgetItem();
    //             if(col ==0){
    //                 item->setCheckState(Qt::Unchecked);
    //             }else if(col==1){
    //                 item->setData(Qt::DisplayRole,row+1);
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }else if(col == 37){
    //                 item->setData(Qt::DisplayRole,UpdateStatus::GetStatusById(rowMap["id"].toString()));
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }else{
    //                 item->setData(Qt::DisplayRole,rowMap[numToHeaderMapBin[col]].toString());
    //                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //             }
    //             dgv->setItem(row,col,item);
    //         }
    //         row++;
    //     }
    // }
    // dgv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
QList<QString> DatagridviewHelper::numToHeaderMap = {
    {"id"},
    {"uid"},
    {"token"},
    {"cookie1"},
    {"email"},
    {"phone"},
    {"name"},
    {"page"},
    {"friends"},
    {"groups"},
    {"pagePro5"},
    {"birthday"},
    {"gender"},
    {"pass"},
    {"mailrecovery"},
    {"passmail"},
    {"backup"},
    {"fa2"},
    {"useragent"},
    {"proxy"},
    {"dateCreateAcc"},
    {"avatar"},
    {"profile"},
    {"nameFile"},
    {"interactEnd"},
    {"info"},
    {"ghiChu"},
    {"status282"},
    {"location"},
    {"hometown"},
    {"currentCity"},
    {"dating"},
    {"ads"},
    {"bm"},
    {"fbBlock"},
    {"job"}
};
QList<QString> DatagridviewHelper::numToHeaderMapBin = {
    {"id"},
    {"uid"},
    {"token"},
    {"cookie1"},
    {"email"},
    {"phone"},
    {"name"},
    {"follow"},
    {"friends"},
    {"groups"},
    {"birthday"},
    {"gender"},
    {"pass"},
    {"mailrecovery"},
    {"passmail"},
    {"backup"},
    {"fa2"},
    {"useragent"},
    {"proxy"},
    {"dateCreateAcc"},
    {"avatar"},
    {"profile"},
    {"nameFile"},
    {"interactEnd"},
    {"info"},
    {"ghiChu"},
    {"dateDelete"},
};

QString DatagridviewHelper::GetStatusDataGridView(QTableWidget* dgv, int row, QString colName)
{
    QString output ="";
    int col=Utils::GetIndexByColumnHeader(dgv,colName);
    try {
        if(col !=-1){
            if (!dgv->item(row,col)->text().isNull()) {
                // Check if the item has a checkbox
                QVariant checkState = dgv->item(row,col)->checkState();
                if (col==0) {
                    // Return "true" or "false" based on the checkbox state
                    output = (checkState.toInt() == Qt::Checked) ? "true" : "false";
                } else {
                    output = dgv->item(row,col)->text();
                }
            }
        }
    } catch (...) {
    }
    return output;
}

void DatagridviewHelper::SetStatusDataGridViewWithWait(QTableWidget* dgv, int row, QString colName, int timeWait, QString status){
    try
    {
        int time_start = GetTickCount();
        while ((GetTickCount() - time_start) / 1000 - timeWait < 0)
        {
            dgv->item(row,Utils::GetIndexByColumnHeader(dgv,colName))->setText(status.replace("{time}", QString::number((timeWait - (GetTickCount() - time_start) / 1000))));
            Common::DelayTime(0.5);
        }
    }
    catch(...)
    {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableWidget* dgv, int row, int col, QVariant status){
    try {
        auto item = dgv->model()->index(row,col);
        if(dgv->model()->data(item, Qt::CheckStateRole).isValid()){
            if(status.toBool() == true){
                dgv->model()->setData(item,Qt::Checked, Qt::CheckStateRole);
            }else{
                dgv->model()->setData(item,Qt::Unchecked, Qt::CheckStateRole);
            }
        }else{
            dgv->model()->setData(item, status, Qt::DisplayRole);
        }

    } catch (...) {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableWidget* dgv, int row, QString colName, QVariant status){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    try {
        if(UpdateStatus::isSaveSettings && colName == "Trạng thái"){
            UpdateStatus::SetStatusById(GetStatusDataGridView(dgv,row,"Id"), status.toString());
        }
        try {
            dgv->item(row,Utils::GetIndexByColumnHeader(dgv,colName))->setData(Qt::DisplayRole , status);
        } catch (...) {
        }
    } catch (...) {
    }
}
