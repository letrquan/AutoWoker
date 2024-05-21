#ifndef INTERACTSQL_H
#define INTERACTSQL_H
#include <QString>
class InteractSQL
{
public:
    InteractSQL();
    static bool CheckColumnIsExistInTable(QString table, QString column);
    static bool AddColumnsIntoTable(QString table, QString columnName, int typeColumnData);
};

#endif // INTERACTSQL_H
