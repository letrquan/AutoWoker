#ifndef EMAILHELPER_H
#define EMAILHELPER_H
#include <QString>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonDocument>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <sysinfoapi.h>
class EmailHelper
{
public:
    EmailHelper();
    static QString getOtpFromDomain(int type, QString& url, const QString& mail, const QString& uidFb = "", int timeOut = 60);
    static QString getOtp(const QString& body, int type, const QString& uidFb = "");
    static QList<QString>* getListMailDomain();
private:
    static QString firstMatchingGroup(const QString& text, const QString& pattern) ;
};

#endif // EMAILHELPER_H
