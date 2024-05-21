#ifndef CONNECTSQLITE_H
#define CONNECTSQLITE_H
#include <QString>
#include <QSqlDatabase>
class ConnectSqlite
{
public:
    ConnectSqlite(QString filepath);
    void CheckConnectServer();
    QSqlQuery ExecuteQuery(QString query);
    int ExecuteNonQuery(QString query);
private:
    QString connectionSTR;
    QSqlDatabase connection;
};

#endif // CONNECTSQLITE_H
