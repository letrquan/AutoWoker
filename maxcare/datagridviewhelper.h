#ifndef DATAGRIDVIEWHELPER_H
#define DATAGRIDVIEWHELPER_H
#include <QTableWidget>
#include <QSqlQuery>
#include "../Table/autotable.h"
class DatagridviewHelper
{
public:
    DatagridviewHelper();
    static void LoadDtgvAccFromDatatable(QTableView *dgv, AutoTable *tableAccount, bool isUseForBin = false);
    static QString GetStatusDataGridView(QTableWidget* dgv, int row, QString colName);
    static void SetStatusDataGridView(QTableWidget* dgv, int row, int col, QVariant status);
    static void SetStatusDataGridView(QTableWidget* dgv, int row, QString colName, QVariant status);
    static QList<QString> numToHeaderMap;
    static QMap<int,QString> numToHeaderMapBin;
    static void SetStatusDataGridViewWithWait(QTableWidget* dgv, int row, QString colName, int timeWait = 0, QString status = "Đơ\u0323i {time} giây...");
};

#endif // DATAGRIDVIEWHELPER_H
