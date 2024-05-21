#ifndef COLLECTIONHELPER_H
#define COLLECTIONHELPER_H
#include <QString>
class CollectionHelper
{
public:
    CollectionHelper();
    static QList<QString> CloneList(QList<QString> lstFrom);
};

#endif // COLLECTIONHELPER_H
