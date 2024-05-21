#ifndef CLONEDATABASE_H
#define CLONEDATABASE_H
#include <QString>
class CloneDatabase
{
public:
    CloneDatabase();
    static void Excute(const QString& pathDb = "database\\db_maxcare.sqlite");
};

#endif // CLONEDATABASE_H
