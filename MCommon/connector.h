#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include "../maxcare/Base.h"
#include <QSqlTableModel>
class Connector
{
public:
    static Connector& getInstance();

private:
    static Connector instance;
    QString connectionSTR = "Data Source=" + Base::pathDataBase + "\\database\\db_maxcare.sqlite;Version=3;";
    QSqlDatabase connection =  QSqlDatabase::addDatabase("QSQLITE");
    Connector(){};
    void CheckConnectServer();
public:
    Connector(Connector const&) = delete;
    void operator=(Connector const&) = delete;
    QSqlQueryModel *ExecuteQuery(QString query);
    int ExecuteNonQuery(QString query);
    int ExecuteScalar(QString query);
};

#endif // CONNECTOR_H
