#include "AutoWorkerTableModel.h"

AutoWorkerTableModel::AutoWorkerTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int AutoWorkerTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return dataVector.size();
}

int AutoWorkerTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return dataVector.isEmpty() ? 0 : dataVector[0].size() + 1; // +1 for the checkbox column
}

QVariant AutoWorkerTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0) {
            return checkboxStates[index.row()];
        } else {
            return dataVector[index.row()][index.column() - 1]; // Adjust for checkbox column
        }
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        return checkboxStates[index.row()] ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

bool AutoWorkerTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
            checkboxStates[index.row()] = value.toBool();
        } else {
            dataVector[index.row()][index.column() - 1] = value; // Adjust for checkbox column
        }
        emit dataChanged(index, index, {role});
        return true;
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        checkboxStates[index.row()] = (value.toInt() == Qt::Checked);
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

Qt::ItemFlags AutoWorkerTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() == 0)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void AutoWorkerTableModel::loadDataFromDatabase(QVector<QVector<QVariant>> data) {
    dataVector.clear();
    checkboxStates.clear();
    for (const QVector<QVariant>& row : data) {
        checkboxStates.append(false); // Initialize checkboxes to unchecked
        dataVector.append(row);
    }
    emit layoutChanged();
}
