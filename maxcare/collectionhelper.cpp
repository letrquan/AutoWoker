#include "collectionhelper.h"
#include <QList>
CollectionHelper::CollectionHelper() {}

QList<QString> CollectionHelper::CloneList(QList<QString> lstFrom){
    QList<QString> list;
    try {
        for(int i =0 ; i< lstFrom.count();i++){
            list.append(lstFrom[i]);
        }
    } catch (...) {
    }
    return list;
}

