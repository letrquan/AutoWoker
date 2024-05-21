#include "connectsqlite.h"
#include <QException>
#include <QSqlQuery>
ConnectSqlite::ConnectSqlite(QString filepath) {
    connectionSTR = filepath;
}

void ConnectSqlite::CheckConnectServer(){
    try {
        if(connection.databaseName().isEmpty()){
            connection.setDatabaseName(connectionSTR);
        }
        if(!connection.isOpen()){
            connection.open();
        }
    } catch (const QException& ex) {

    }
}

QSqlQuery ConnectSqlite::ExecuteQuery(QString query){
    QSqlQuery dataTable(connection);
    try {
        CheckConnectServer();
        dataTable.exec(query);
    } catch (...) {
    }
    connection.close();
    return dataTable;
}

int ConnectSqlite::ExecuteNonQuery(QString query){
    int result = 0;
    try {
        CheckConnectServer();
        QSqlQuery dataTable(connection);
        dataTable.exec(query);
        result = dataTable.numRowsAffected();
    } catch (...) {
    }
    connection.close();
    return result;
}
