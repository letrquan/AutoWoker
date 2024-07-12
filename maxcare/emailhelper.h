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
#include "../MCommon/RequestHandle.h"
class EmailHelper
{
public:
    EmailHelper();
    static QString getOtpFromDomain(int type, QString& url, const QString& mail, const QString& uidFb = "", int timeOut = 60);
    static QString getOtp(const QString& body, int type, const QString& uidFb = "");
    static QList<QString>* getListMailDomain();
    QString GetOtpByDomainGIAU(int type, const QString& email, int timeOut = 60, const QString& uidFb = "")
    {
        try
        {
            RequestHandle requestHttp("","","",0);
            QElapsedTimer timer;
            timer.start();

            do
            {
                QString text = requestHttp.RequestGet("https://api01.app88.me/api/v1/maildomain/fbcode?email=" + email);
                if (!text.isEmpty())
                {
                    try
                    {
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(text.toUtf8());
                        QJsonObject jsonObject = jsonDoc.object();

                        if (!jsonObject["result"].toObject()["mail_very"].toString().isEmpty())
                        {
                            QString otp = jsonObject["result"].toObject()["mail_very"].toObject()["verify_code"].toString();
                            if (!otp.isEmpty())
                            {
                                return otp;
                            }
                            // QJsonArray domain = jsonObject["result"].toObject()["mails"].toArray();
                            // for (const QJsonValue& item : domain)
                            // {
                            //     QString body = item.toObject()["body"].toString();
                            //     QString otp = GetOtp(body, type, uidFb);
                            //     if (!otp.isEmpty())
                            //     {
                            //         return otp;
                            //     }
                            // }
                        }
                    }
                    catch (...)
                    {
                        // Catch any exception and continue
                    }
                }
                QThread::msleep(3000); // Equivalent to Common.DelayTime(3.0)
            }
            while (timer.elapsed() <= timeOut * 1000);
        }
        catch (...)
        {
            // Catch any exception
        }
        return QString();
    }
private:
    static QString firstMatchingGroup(const QString& text, const QString& pattern) ;
};

#endif // EMAILHELPER_H
