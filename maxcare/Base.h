#ifndef BASE_H
#define BASE_H
#include<QString>
#include<QDir>
#include <QRandomGenerator>

class Base{
private:
    static QString domain;
    static QString softIndex;

public:
    static QRandomGenerator rd;
    static QString base64_anhmau;
    static bool isLam ;
    static bool isTuan ;
    static QList<QString> lstLink;
    static QString GetPathDatabase();
    static QString pathDataBase;
    static QString GetLanguage();

    static QString GetServer();

    static void SetLanguage(QString language = "VN");
    static bool CheckPassword();
    static QMap<QString, QString> GetServers();
    static QString GetDomain();
    static QString GetSoftIndex();
};
#endif // BASE_H
