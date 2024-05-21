#ifndef DATAGRIDVIEWHELPER_H
#define DATAGRIDVIEWHELPER_H
#include "qsqlquerymodel.h"
#include <QTableWidget>
#include <QSqlQuery>
class DatagridviewHelper
{
public:
    DatagridviewHelper();
    static void LoadDtgvAccFromDatatable(QTableView *dgv, QSqlQueryModel *tableAccount, bool isUseForBin = false);
    static QString GetStatusDataGridView(QTableView* dgv, int row, QString colName);
    static void SetStatusDataGridView(QTableView* dgv, int row, int col, QVariant status);
    static void SetStatusDataGridView(QTableView* dgv, int row, QString colName, QVariant status);
    static QList<QString> numToHeaderMap;
    static QList<QString> numToHeaderMapBin;
};

#endif // DATAGRIDVIEWHELPER_H
