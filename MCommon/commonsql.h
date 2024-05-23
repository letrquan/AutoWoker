#ifndef COMMONSQL_H
#define COMMONSQL_H
#include <QSqlTableModel>
#include <QStringList>
class CommonSQL
{
public:
    CommonSQL();
    static QVariantList* GetAllFilesFromDatabase(bool isShowAll = false, bool notAW = false);
    static QVariantList* GetAllFilesFromDatabaseForBin(bool isShowAll = false);
    static QVariantList* GetAllInfoFromAccount(QList<QString> lstIdFile, bool isGetActive = true,bool foraw=false);
    static bool CheckColumnIsExistInTable(QString table, QString column);
    static bool CheckExistTable(QString table);
    static bool AddColumnsIntoTable(QString table, QString columnName, int typeColumnData);
    static QVariantList* GetIdStatus();
    static QVariantList* GetAccFromFile(QList<QString>* lstIdFile = new QList<QString>(), QString info = "", bool isGetActive = true);
    static QString ConvertToSqlInsertAccount( QString& uid,  QString& pass, const QString& token, const QString& cookie, const QString& email, QString& name, const QString& friends, const QString& groups, const QString& birthday, const QString& gender, const QString& info, const QString& fa2, const QString& idFile, const QString& passMail, const QString& useragent, const QString& proxy, const QString& create, const QString& mailKp);
    static QList<QString> ConvertToSqlInsertAccount(const QList<QString>& lstSqlStatement);
    static bool CheckExitsFile(QString name);
    static bool InsertFileToDatabase(QString namefile,bool aw=false);
    static bool UpdateThuTuThuMuc(const QString& id1, const QString& id2);
};
#endif // COMMONSQL_H
