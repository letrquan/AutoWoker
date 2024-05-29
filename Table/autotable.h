#ifndef AUTOTABLE_H
#define AUTOTABLE_H

#include <QSqlQueryModel>

class AutoTable : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit AutoTable(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setCustomColumnData(int column, const QVector<QVariant> &data);

private:
    int customColumn;
    QVector<QVariant> customData;
};


#endif // AUTOTABLE_H
