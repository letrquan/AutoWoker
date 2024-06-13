#include "datagridviewhelper.h"
#include <QHeaderView>
#include <mutex>
#include "../maxcare/updatestatus.h"
#include "../Utils/Utils.h"
#include "../MCommon/Common.h"
#include "../Table/customtablemodel.h"
DatagridviewHelper::DatagridviewHelper() {}

void DatagridviewHelper::LoadDtgvAccFromDatatable(QTableView* dgv, CustomTableModel* model, bool isUseForBin){
    dgv->setModel(model);
}
QStringList DatagridviewHelper::numToHeaderMap = {
    {"Select"},
    {"STT"},
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
    {"job"},
    {"Trạng thái"}
};
QStringList DatagridviewHelper::numToHeaderMapBin = {
    {"Select"},
    {"STT"},
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
    {"Trạng thái"}
};

QString DatagridviewHelper::GetStatusDataGridView(QTableView* dgv, int row, QString colName)
{
    QString output ="";
    int col=Utils::GetIndexByColumnHeader(dgv,colName);
    try {
        if(col !=-1){
            if (!dgv->model()->index(row,col).data().isNull()) {
                // Check if the item has a checkbox
                output = dgv->model()->index(row,col).data().toString();
            }
        }
    } catch (...) {
    }
    return output;
}

void DatagridviewHelper::SetStatusDataGridViewWithWait(QTableView* dgv, int row, QString colName, int timeWait, QString status){
    try
    {
        int time_start = QDateTime::currentSecsSinceEpoch();
        while ((QDateTime::currentSecsSinceEpoch() - time_start) / 1 - timeWait < 0)
        {
            dgv->model()->setData(dgv->model()->index(row,Utils::GetIndexByColumnHeader(dgv,colName)),status.replace("{time}", QString::number((timeWait - (GetTickCount() - time_start) / 1))),Qt::DisplayRole);
            Common::DelayTime(0.5);
        }
    }
    catch(...)
    {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableView* dgv, int row, int col, QVariant status){
    try {
        auto item = dgv->model()->index(row,col);
        if(dgv->model()->data(item, Qt::CheckStateRole).isValid()){
            if(status.toBool() == true){
                dgv->model()->setData(item,Qt::Checked, Qt::CheckStateRole);
            }else{
                dgv->model()->setData(item,Qt::Unchecked, Qt::CheckStateRole);
            }
        }else{
            dgv->model()->setData(item, status, Qt::EditRole);
        }

    } catch (...) {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableView* dgv, int row, QString colName, QVariant status){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    try {
        if(UpdateStatus::isSaveSettings && colName == "Trạng thái"){
            UpdateStatus::SetStatusById(GetStatusDataGridView(dgv,row,"Id"), status.toString());
        }
        try {
            if(colName == "Select"){
                dgv->model()->setData(dgv->model()->index(row,Utils::GetIndexByColumnHeader(dgv,colName)),status,Qt::CheckStateRole);
            }else{
                dgv->model()->setData(dgv->model()->index(row,Utils::GetIndexByColumnHeader(dgv,colName)),status,Qt::EditRole);
            }
        } catch (...) {
        }
    } catch (...) {
    }
}
