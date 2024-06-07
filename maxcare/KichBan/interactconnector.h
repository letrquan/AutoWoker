#ifndef INTERACTCONNECTOR_H
#define INTERACTCONNECTOR_H
#include "qmutex.h"
#include "qsqldatabase.h"
#include <QString>
class InteractConnector
{
public:
    static InteractConnector& getInstance();

private:
    static InteractConnector instance;
    QString connectionSTR = "Data Source=D:\\AutoWorker\\XWorker\\AutoWoker\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\interact\\interact.sqlite";
    QSqlDatabase connection =  QSqlDatabase::addDatabase("QSQLITE", "interactConnector");
    InteractConnector(){};
    void CheckConnectServer();
    QMutex mutex;
public:
    InteractConnector(InteractConnector const&) = delete;
    void operator=(InteractConnector const&) = delete;
    QVariantList *ExecuteQuery(QString query);
    int ExecuteNonQuery(QString query);
    int ExecuteScalar(QString query);
};

#endif // INTERACTCONNECTOR_H
