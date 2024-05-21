#ifndef DATAGRIDVIEWHELPER_H
#define DATAGRIDVIEWHELPER_H
#include <QTableWidget>
#include <QSqlQuery>
class DatagridviewHelper
{
public:
    DatagridviewHelper();
    static void LoadDtgvAccFromDatatable(QTableView *dgv, QVariantList *tableAccount, bool isUseForBin = false);
    static QString GetStatusDataGridView(QTableView* dgv, int row, QString colName);
    static void SetStatusDataGridView(QTableView* dgv, int row, int col, QVariant status);
    static void SetStatusDataGridView(QTableView* dgv, int row, QString colName, QVariant status);
    static QMap<int,QString> numToHeaderMap;
    static QMap<int,QString> numToHeaderMapBin;
};

#endif // DATAGRIDVIEWHELPER_H
