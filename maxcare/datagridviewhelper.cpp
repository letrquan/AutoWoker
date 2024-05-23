#include "datagridviewhelper.h"
#include <QHeaderView>
#include "../maxcare/updatestatus.h"
#include "../Utils/Utils.h"
#include "../MCommon/Common.h"
DatagridviewHelper::DatagridviewHelper() {}

void DatagridviewHelper::LoadDtgvAccFromDatatable(QTableWidget* dgv, QVariantList* tableAccount, bool isUseForBin){
    dgv->setRowCount(tableAccount->size());
    if(!isUseForBin){
        auto row =0;
        for(const QVariant &item:*tableAccount){
            QVariantMap rowMap = item.toMap();
            for(int col =0;col<dgv->columnCount();col++){
                auto item = new QTableWidgetItem();
                if(col ==0){
                    item->setCheckState(Qt::Unchecked);
                }else if(col==1){
                    item->setData(Qt::DisplayRole,row+1);
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }else if(col == 38){
                    item->setData(Qt::DisplayRole,UpdateStatus::GetStatusById(rowMap["id"].toString()));
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }else{
                    item->setData(Qt::DisplayRole,rowMap[numToHeaderMap[col]].toString());
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                }
                dgv->setItem(row,col,item);
            }
            row++;
        }
    }else{
        auto row =0;
        for(const QVariant &item:*tableAccount){
            QVariantMap rowMap = item.toMap();
            for(int col =0;col<dgv->columnCount();col++){
                auto item = new QTableWidgetItem();
                if(col ==0){
                    item->setCheckState(Qt::Unchecked);
                }else if(col==1){
                    item->setData(Qt::DisplayRole,row+1);
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }else if(col == 38){
                    item->setData(Qt::DisplayRole,UpdateStatus::GetStatusById(rowMap["id"].toString()));
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }else{
                    item->setData(Qt::DisplayRole,rowMap[numToHeaderMap[col]].toString());
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                }
                dgv->setItem(row,col,item);
            }
            row++;
        }
    }
    dgv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
QMap<int,QString> DatagridviewHelper::numToHeaderMap = {
    {2, "id"},
    {3, "uid"},
    {4, "token"},
    {5, "cookie1"},
    {6, "email"},
    {7, "phone"},
    {8, "name"},
    {9, "follow"},
    {10, "friends"},
    {11, "groups"},
    {12, "pagePro5"},
    {13, "birthday"},
    {14, "gender"},
    {15, "pass"},
    {16, "mailrecovery"},
    {17, "passmail"},
    {18, "backup"},
    {19, "fa2"},
    {20, "useragent"},
    {21, "proxy"},
    {22, "dateCreateAcc"},
    {23, "avatar"},
    {24, "profile"},
    {25, "nameFile"},
    {26, "interactEnd"},
    {27, "info"},
    {28, "ghiChu"},
    {29, "status282"},
    {30, "location"},
    {31, "hometown"},
    {32, "currentCity"},
    {33, "dating"},
    {34, "ads"},
    {35, "bm"},
    {36, "fbBlock"},
    {37, "job"}
};
QMap<int,QString> DatagridviewHelper::numToHeaderMapBin = {
    {2, "id"},
    {3, "uid"},
    {4, "token"},
    {5, "cookie1"},
    {6, "email"},
    {7, "phone"},
    {8, "name"},
    {9, "follow"},
    {10, "friends"},
    {11, "groups"},
    {12, "birthday"},
    {13, "gender"},
    {14, "pass"},
    {15, "mailrecovery"},
    {16, "passmail"},
    {17, "backup"},
    {18, "fa2"},
    {19, "useragent"},
    {20, "proxy"},
    {21, "dateCreateAcc"},
    {22, "avatar"},
    {23, "profile"},
    {24, "nameFile"},
    {25, "interactEnd"},
    {26, "info"},
    {27, "ghiChu"},
    {28, "dateDelete"},
};

QString DatagridviewHelper::GetStatusDataGridView(QTableWidget* dgv, int row, QString colName){
    QString output ="";
    int col=Utils::GetIndexByColumnHeader(dgv,colName);
    try {
        if(col !=-1){
            if (dgv->item(row,col)) {
                // Check if the item has a checkbox
                QVariant checkState = dgv->item(row,col)->data(Qt::CheckStateRole);
                if (checkState.isValid()) {
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
        auto item = dgv->item(row,col);
        if(item && (item->flags() & Qt::ItemIsUserCheckable)){
            if(status.toBool() == true){
                item->setCheckState(Qt::Checked);
            }else{
                item->setCheckState(Qt::Unchecked);
            }
        }else{
            item->setData(Qt::DisplayRole,status);
        }

    } catch (...) {
    }
}
void DatagridviewHelper::SetStatusDataGridView(QTableWidget* dgv, int row, QString colName, QVariant status){
    try {
        if(UpdateStatus::isSaveSettings && colName == "Trạng thái"){
            UpdateStatus::SetStatusById(GetStatusDataGridView(dgv,row,"Id"), status.toString());
        }
        try {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setData(Qt::DisplayRole,status);
            dgv->setItem(row, Utils::GetIndexByColumnHeader(dgv,colName),item);
        } catch (...) {
        }
    } catch (...) {
    }
}
