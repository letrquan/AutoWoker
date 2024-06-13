#ifndef COLLECTIONHELPER_H
#define COLLECTIONHELPER_H
#include <QString>
#include <QList>
#include <QRandomGenerator>
class CollectionHelper
{
public:
    CollectionHelper();
    static QList<QString> CloneList(QList<QString> lstFrom);
    static int GetRandomIndex(QList<QString> lst){
        if (lst.isEmpty()){
            return -1;
        }
        return QRandomGenerator::global()->bounded(lst.size());
    }
    static QString GetRandomItem(QList<QString> lst){
        if(lst.isEmpty() || lst.count() == 0){
            return nullptr;
        }
        return lst[GetRandomIndex(lst)];
    }
};

#endif // COLLECTIONHELPER_H
