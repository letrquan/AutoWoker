#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QObject>
#include <QRunnable>
#include <QTableWidget>

class BaseWorker : public QObject, public QRunnable {
    Q_OBJECT
public:
    BaseWorker(int row, QTableWidget *tableWidget, QObject *parent = nullptr);
    virtual void run() override = 0;

signals:
    void setStatusAccount(int row, QString value, int timeWait = -1);
    void setInfoAccount(int indexRow, QString value);
    void setRowColor(int indexRow, int typeColor);

protected:
    int row;
    QTableWidget *tableWidget;
};

#endif // BASEWORKER_H
