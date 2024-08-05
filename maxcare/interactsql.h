#ifndef INTERACTSQL_H
#define INTERACTSQL_H
#include <QString>
class InteractSQL
{
public:
    InteractSQL();
    static bool CheckColumnIsExistInTable(QString table, QString column);
    static bool AddColumnsIntoTable(QString table, QString columnName, int typeColumnData);
    static QVariantList* GetAllKichBan();
    static QVariantList* GetAllHanhDongByKichBan(QString idKichBan);
    static QStringList GetIdHanhDongByIdKichBanAndTenTuongTac(QString Id_KichBan, QString tenTuongTac);
    static QString GetCauHinhFromHanhDong(QString Id_HanhDong);
    static QString GetCauHinhFromKichBan(QString Id_KichBan);
    static QVariantList* GetHanhDongById(QString id);
};

#endif // INTERACTSQL_H
