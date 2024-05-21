#ifndef AWAPI_H
#define AWAPI_H
#include <QString>
#include <QVariant>
#include <QList>
#include <QPair>

class AwApi{
    QString domaingetmail = "https://cdn.autoworker.me/";
public:
    static QString LoginTool(QString username, QString password);
    static QString checkUpdate(QString namesoft);
};



#endif // AWAPI_H
