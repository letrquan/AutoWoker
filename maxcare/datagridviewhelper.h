#ifndef DATAGRIDVIEWHELPER_H
#define DATAGRIDVIEWHELPER_H
#include <QTableWidget>
#include <QSqlQuery>
#include "../Table/customtablemodel.h"
class DatagridviewHelper
{
public:
    DatagridviewHelper();
    static void LoadDtgvAccFromDatatable(QTableView *dgv, CustomTableModel *tableAccount, bool isUseForBin = false);
    static QString GetStatusDataGridView(QTableView *dgv, int row, QString colName);
    static void SetStatusDataGridView(QTableView* dgv, int row, int col, QVariant status);
    static void SetStatusDataGridView(QTableView* dgv, int row, QString colName, QVariant status);
    static QStringList numToHeaderMap;
    static QStringList numToHeaderMapBin;
    static void SetStatusDataGridViewWithWait(QTableView* dgv, int row, QString colName, int timeWait = 0, QString status = "Đơ\u0323i {time} giây...");

};

#endif // DATAGRIDVIEWHELPER_H
