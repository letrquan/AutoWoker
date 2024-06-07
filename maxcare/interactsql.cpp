#include "interactsql.h"
#include "../MCommon/connector.h"
#include "../maxcare/KichBan/interactconnector.h"
InteractSQL::InteractSQL() {}
bool InteractSQL::CheckColumnIsExistInTable(QString table, QString column){
    bool result = false;
    try {
        if(Connector::getInstance().ExecuteScalar("SELECT COUNT(*) AS count FROM pragma_table_info('"+table+"') WHERE name='{column}'") >0){
            result = true;
        }
    } catch (...) {
    }
    return result;
}

bool InteractSQL::AddColumnsIntoTable(QString table, QString columnName, int typeColumnData){
    bool result =false;
    try {
        QString type = (typeColumnData == 0) ? "INT" : "TEXT";
        if(Connector::getInstance().ExecuteNonQuery("ALTER TABLE "+table+" ADD COLUMN '"+columnName+"' "+type+";") >0){
            result = true;
        }
    } catch (...) {

    }
    return result;
}

QVariantList* InteractSQL::GetAllKichBan()
{
    QVariantList* result = new QVariantList();
    try
    {
        QString query = "DROP TABLE IF EXISTS tmp;CREATE TEMPORARY TABLE tmp(Stt INTEGER PRIMARY KEY AUTOINCREMENT, Id_KichBan INTEGER, TenKichBan TEXT);INSERT INTO tmp (Id_KichBan, TenKichBan) SELECT Id_KichBan, TenKichBan FROM Kich_Ban;SELECT Id_KichBan, TenKichBan, (Stt||'. '||TenKichBan) AS Ten FROM tmp;";
        result = InteractConnector::getInstance().ExecuteQuery(query);
        return result;
    }
    catch(...)
    {
        return result;
    }
}
QVariantList* InteractSQL::GetAllHanhDongByKichBan(QString idKichBan)
{
    QVariantList* result = new QVariantList();
    try
    {
        QString query = "SELECT t1.Id_HanhDong, t1.TenHanhDong,t2.Id_TuongTac,t2.TenTuongTac, t2.MoTa FROM Hanh_Dong t1 JOIN Tuong_Tac t2 ON t1.Id_TuongTac = t2.Id_TuongTac WHERE t1.Id_KichBan = " + idKichBan + " ORDER BY t1.STT";
        result = InteractConnector::getInstance().ExecuteQuery(query);
        return result;
    }
    catch(...)
    {
        return result;
    }
}
