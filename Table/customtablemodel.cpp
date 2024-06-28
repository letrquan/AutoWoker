#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include "customtablemodel.h"
#include "../maxcare/updatestatus.h"
#include "qcolor.h"
QMap<QString, QString> headerNameToDisplayText = {
    {"Select", "Chọn"},
    {"STT", "STT"},
    {"id","Id"},
    {"uid", "Uid"},
    {"token", "Token"},
    {"cookie1", "Cookies"},
    {"email", "Email"},
    {"phone", "Phone"},
    {"name", "Tên"},
    {"page", "Page"},
    {"friends", "Bạn Bè"},
    {"groups", "Nhóm"},
    {"pagePro5", "PagePro5"},
    {"birthday", "Ngày sinh"},
    {"gender", "Giới tính"},
    {"pass", "Mật khẩu"},
    {"mailrecovery", "Mail Khôi Phục"},
    {"passmail", "Mật khẩu Mail"},
    {"backup", "Backup"},
    {"fa2", "Mã 2FA"},
    {"useragent", "Useragent"},
    {"proxy", "Proxy"},
    {"dateCreateAcc", "Ngày tạo tài khoản"},
    {"avatar", "Avatar"},
    {"profile", "Profile"},
    {"nameFile", "Thư Mục"},
    {"interactEnd", "Lần Tương Tác Cuối"},
    {"info", "Tình Trạng"},
    {"ghiChu", "Ghi Chú"},
    {"status282", "Status282"},
    {"location", "Location"},
    {"hometown", "Home Town"},
    {"currentCity", "Current City"},
    {"dating", "Dating"},
    {"ads", "Ads"},
    {"bm", "BM"},
    {"fbBlock", "FbBlock"},
    {"job", "Job"},
    {"Trạng thái", "Trạng thái"}
};
CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

void CustomTableModel::loadDataFromDatabase(QVariantList* data) {
    if (data->isEmpty()) {
        beginResetModel();
        dataStorage.clear();
        headerLabels.clear();
        endResetModel();
        return;
    }

    // Clear existing data
    dataStorage.clear();
    headerLabels.clear();

    // Extract header labels from the first record
    QVariantMap firstRow = data->first().toMap();
    headerLabels.push_back("Select");
    headerLabels.push_back("STT");
    for (auto it = firstRow.constBegin(); it != firstRow.constEnd(); ++it) {
        if(headerNameToDisplayText.contains(it.key())){
            headerLabels.push_back(headerNameToDisplayText[it.key()]);
        }
    }
    headerLabels.push_back("Trạng thái");
    // Populate data storage
    int stt = 1;
    for (const QVariant &record : *data) {
        QVariantMap rowMap = record.toMap();
        QVector<QVariant> row;
        row.push_back(false); // Initialize the checkbox as unchecked
        row.push_back(stt++);
        for (auto it = rowMap.constBegin(); it != rowMap.constEnd(); ++it) {
            if(headerNameToDisplayText.contains(it.key())){
                row.push_back(it.value());
            }
        }
        row.push_back(UpdateStatus::GetStatusById(rowMap["id"].toString()));
        dataStorage.push_back(row);
    }
    beginResetModel();
    endResetModel();
}

void CustomTableModel::addColumn(const QString &name, int columnNumber, const QVector<QVariant> &data ) {
    int columnPos = columnNumber + 1;  // Insert the new column to the right of the specified column number
    beginInsertColumns(QModelIndex(), columnPos, columnPos);  // Notify that a column is being inserted
    headerLabels.insert(columnPos, name);  // Insert the new column header
    for (int i = 0; i < dataStorage.size(); ++i) {
        dataStorage[i].insert(columnPos, data.value(i));  // Insert the new column data in each row
    }
    endInsertColumns();  // Notify that the column insertion is done
}

int CustomTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return dataStorage.size();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return dataStorage.isEmpty() ? 0 : dataStorage[0].size();
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == Qt::BackgroundRole) {
        if (rowColors.contains(index.row())) {
            return rowColors[index.row()];
        }
    }
    if (role == Qt::DisplayRole && index.column() != 0) {
        return dataStorage[index.row()][index.column()];
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        return dataStorage[index.row()][index.column()].toBool() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::CheckStateRole && index.column() == 0) {
        dataStorage[index.row()][index.column()] = (value == Qt::Checked);
        emit dataChanged(index, index, {role});
        int checkedCount = 0;
        for (const auto &row : dataStorage) {
            if (row[0].toBool()) {
                checkedCount++;
            }
        }
        emit checkedCountChanged();
        return true;
    }
    if (index.isValid() && role == Qt::EditRole && index.column() != 0) {
        dataStorage[index.row()][index.column()] = value;
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}
QVariant CustomTableModel::getData(int row, int column) const {
    if (row < 0 || row >= dataStorage.size() || column < 0 || column >= dataStorage[0].size()) {
        return QVariant();  // Return invalid QVariant if the indices are out of range
    }
    return dataStorage[row][column];
}
Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() == 0) {
        flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;  // Allow user to check/uncheck the checkbox
    }
    return flags;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headerLabels.value(section);
    }
    return QVariant();
}
void CustomTableModel::setRowColor(int row, const QColor &color) {
    if (row >= 0 && row < dataStorage.size()) {
        rowColors[row] = color;
        emit dataChanged(index(row, 0), index(row, columnCount() - 1), {Qt::BackgroundRole});
    }
}

void CustomTableModel::clearRows() {
    beginResetModel();
    dataStorage.clear();
    endResetModel();
}

void CustomTableModel::addRow(const QVector<QVariant> &rowData) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    dataStorage.append(rowData);
    endInsertRows();
}
