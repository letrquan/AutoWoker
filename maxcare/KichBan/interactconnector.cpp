#include "interactconnector.h"
#include <QException>
#include "../../MCommon/Common.h"
#include "qsqlquery.h"
#include <QSqlRecord>
#include <QSqlError>
#include <mutex>
InteractConnector& InteractConnector::getInstance(){
    static InteractConnector instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
    return instance;
}

void InteractConnector::CheckConnectServer(){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    try {
        QString text = "D:/AutoWorker/XWorker/AutoWoker/build/Desktop_Qt_6_7_1_MinGW_64_bit-Debug/interact/interact.sqlite";
        if(text != connectionSTR){
            if(connection.isOpen()){
                connection.close();
            }
            connectionSTR = text;
            connection.setDatabaseName(connectionSTR);
            connection.open();
        }else{
            if(connection.databaseName().isEmpty()){
                connection.setDatabaseName(connectionSTR);
            }
            if(!connection.isOpen()){
                connection.open();
            }
        }
    } catch (const QException& ex) {
        Common::ExportError(&ex, "CheckConnectServer");
    }
}
QVariantList* InteractConnector::ExecuteQuery(QString query){
    QVariantList* resultList = new QVariantList();
    QSqlQuery dataList(connection);
    try {
        CheckConnectServer();
        QStringList queries = query.split(';', Qt::SkipEmptyParts);
        for (const QString& singleQuery : queries) {
            if (dataList.exec(singleQuery)) {
                if(dataList.isSelect()){
                    while (dataList.next()) {
                        QVariantMap rowMap;
                        for (int i = 0; i < dataList.record().count(); ++i) {
                            rowMap.insert(dataList.record().fieldName(i), dataList.value(i));
                        }
                        resultList->append(rowMap);
                    }
                }
            }else{
                qDebug() << "Error at executequery:" << dataList.lastError() ;
            }
        }
        // if(dataList.exec(query)){
        //     while (dataList.next()) {
        //         QVariantMap rowMap;
        //         for (int i = 0; i < dataList.record().count(); ++i) {
        //             rowMap.insert(dataList.record().fieldName(i), dataList.value(i));
        //         }
        //         resultList->append(rowMap);
        //     }
        // }else{
        //     qDebug() << "Error at executequery:" << dataList.lastError() ;
        // }
    } catch (...) {

    }
    connection.close();
    return resultList;
}

int InteractConnector::ExecuteNonQuery(QString query){
    int result = 0;
    try {
        CheckConnectServer();
        QSqlQuery nonQ(connection);
        connection.transaction();
        if(nonQ.exec(query)){
            if(nonQ.numRowsAffected() != -1){
                result = nonQ.numRowsAffected();
            } else {
                qDebug() << "ExecuteNonQuery: numRowsAffected() returned -1";
            }
            connection.commit();
        } else {
            qDebug() << "ExecuteNonQuery failed: " << nonQ.lastError().text();
            connection.rollback();
        }
    } catch (const QException& ex) {
        qDebug() << "Exception caught in ExecuteNonQuery: " << ex.what();
    } catch (...) {
        qDebug() << "Unknown exception caught in ExecuteNonQuery";
    }
    connection.close();
    return result;
}
int InteractConnector::ExecuteScalar(QString query){
    int result = 0;
    try {
        CheckConnectServer();
        QSqlQuery sca(connection);
        if(sca.exec(query)){
            if(sca.next()){
                result = sca.value(0).toInt();
            }
        }
    } catch (...) {
    }
    connection.close();
    return result;
}
