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
        QSqlQueryModel* map = CommonSQL::GetIdStatus();
        for (int i =0; i<map->rowCount();i++){

            dicIdStatus.insert(map->index(i,0).data().toString(),map->index(i,1).data().toString());
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

