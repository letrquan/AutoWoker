#include "datagridviewhelper.h"
#include <QHeaderView>
#include "../maxcare/updatestatus.h"
#include "../Utils/Utils.h"
#include "qsqlquerymodel.h"
DatagridviewHelper::DatagridviewHelper() {}

void DatagridviewHelper::LoadDtgvAccFromDatatable(QTableView* dgv, QSqlQueryModel* tableAccount, bool isUseForBin){

    if(!isUseForBin){
        dgv->setModel(Utils::transferData(tableAccount,"Chọn"));
        int columnCount = dgv->model()->columnCount();
        for (int i = 0; i < columnCount; ++i) {
            QString columnHeader = dgv->model()->headerData(i, Qt::Horizontal).toString();
            if (!numToHeaderMap.contains(columnHeader)) {
                dgv->hideColumn(i);
            }
        }
    }else{
        dgv->setModel(Utils::transferData(tableAccount,"Chọn"));
        int columnCount = dgv->model()->columnCount();
        for (int i = 0; i < columnCount; ++i) {
            QString columnHeader = dgv->model()->headerData(i, Qt::Horizontal).toString();
            if (!numToHeaderMapBin.contains(columnHeader)) {
                dgv->hideColumn(i);
            }
        }
    }
    dgv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
QList<QString> DatagridviewHelper::numToHeaderMap = {
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
    { "friends"},
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

QString DatagridviewHelper::GetStatusDataGridView(QTableView* dgv, int row, QString colName){
    QString output ="";
    int col=Utils::findColumnByHeader(dgv,colName);
    try {
        if(col !=-1){
            if (!dgv->model()->index(row,col).data().isNull()) {
                // Check if the item has a checkbox
                QVariant checkState = dgv->model()->index(row,col).data(Qt::CheckStateRole);
                if (checkState.isValid()) {
                    // Return "true" or "false" based on the checkbox state
                    output = (checkState.toInt() == Qt::Checked) ? "true" : "false";
                } else {
                    output = dgv->model()->index(row,col).data().toString();
                }
            }
        }
    } catch (...) {
    }
    return output;
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
            dgv->model()->setData(item, status, Qt::DisplayRole);
        }

    } catch (...) {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableView* dgv, int row, QString colName, QVariant status){
    try {
        if(UpdateStatus::isSaveSettings && colName == "Trạng thái"){
            UpdateStatus::SetStatusById(GetStatusDataGridView(dgv,row,"Id"), status.toString());
        }
        try {
            dgv->model()->setData(dgv->model()->index(row,Utils::findColumnByHeader(dgv,colName)), status, Qt::DisplayRole);
        } catch (...) {
        }
    } catch (...) {
    }
}
