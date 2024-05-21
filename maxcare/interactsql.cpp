#include "interactsql.h"
#include "../MCommon/connector.h"
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
