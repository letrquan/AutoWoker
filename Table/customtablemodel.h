#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QSet>

class CustomTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit CustomTableModel(QObject *parent = nullptr);

    void loadDataFromDatabase(QVariantList* data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant getData(int row, int column) const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addColumn(const QString &name, int columnNumber, const QVector<QVariant> &data = QVector<QVariant>());
    void setRowColor(int row, const QColor &color);
    void clearRows();
    void addRow(const QVector<QVariant> &rowData);
private:
    QVector<QVector<QVariant>> dataStorage;
    QVector<QString> headerLabels;
    QMap<int, QColor> rowColors;
};
#endif // CUSTOMTABLEMODEL_H
