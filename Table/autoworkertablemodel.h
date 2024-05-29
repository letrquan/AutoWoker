#ifndef AUTOWORKERTABLEMODEL_H
#define AUTOWORKERTABLEMODEL_H
#include <QAbstractTableModel>
#include <QVector>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
class AutoWorkerTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit AutoWorkerTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void loadDataFromDatabase(QVector<QVector<QVariant> > data);

private:
    QVector<QVector<QVariant>> dataVector;
    QVector<bool> checkboxStates; // Separate vector for checkbox states
};
#endif // AUTOWORKERTABLEMODEL_H
