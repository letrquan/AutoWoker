#include "autotable.h"

AutoTable::AutoTable(QObject *parent)
    : QSqlQueryModel(parent), customColumn(-1)
{
}

void AutoTable::setCustomColumnData(int column, const QVector<QVariant> &data)
{
    customColumn = column;
    customData = data;
}

QVariant AutoTable::data(const QModelIndex &index, int role) const
{
    if (index.column() == customColumn && role == Qt::DisplayRole) {
        if (index.row() < customData.size()) {
            return customData.at(index.row());
        }
    }
    return QSqlQueryModel::data(index, role);
}

int AutoTable::columnCount(const QModelIndex &parent) const
{
    return QSqlQueryModel::columnCount(parent) + (customColumn != -1 ? 1 : 0);
}
