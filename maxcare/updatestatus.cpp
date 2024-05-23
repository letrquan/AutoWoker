#include "updatestatus.h"
#include <QMap>
#include "../MCommon/commonsql.h"
UpdateStatus::UpdateStatus(){}

bool UpdateStatus::isSaveSettings = false;
QMap<QString, QString> UpdateStatus::dicIdStatus;
QString UpdateStatus::GetStatusById(QString id)
{
    if (!isSaveSettings)
    {
        return "";
    }
    QString result = "";
    if (dicIdStatus.contains(id))
    {
        result = dicIdStatus[id];
    }
    return result;
}

void UpdateStatus::GetValueFromDatabase(){
    if (isSaveSettings)
    {
        QVariantList* map = CommonSQL::GetIdStatus();
        for (auto item:*map){
            auto rowMap = item.toMap();
            dicIdStatus.insert(rowMap["id"].toString(),rowMap["status"].toString());
        }
    }
}

void UpdateStatus::SetStatusById(QString id, QString status){
    if(isSaveSettings){
        if(dicIdStatus.contains(id)){
            dicIdStatus[id] = status;
        }else{
            dicIdStatus.insert(id,status);
        }
    }
}

