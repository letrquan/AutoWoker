#include "emailhelper.h"
#include "../MCommon/requesthandle.h"

#include "../MCommon/Common.h"
#include <QJsonDocument>
EmailHelper::EmailHelper() {}

QString EmailHelper::getOtpFromDomain(int type, QString& url, const QString& mail, const QString& uidFb, int timeOut){
    RequestHandle request("","","",0);
    url = url.left(url.lastIndexOf("=")+1) + mail;
    // int tickCount = QDateTime::currentSecsSinceEpoch();
    // do {
        QByteArray text = request.RequestGet(url);
        try {
            text = "{\"data\":" + text + "}";
            QJsonDocument doc = QJsonDocument::fromJson(text);
            QJsonObject jObject = doc.object();
            QJsonArray dataArray = jObject["data"].toArray();
            for(int num =dataArray.count(); num >=0;num--){
                QJsonObject dataObject = dataArray[num].toObject();
                QString createAt = dataObject["created_at"].toString();
                QString otp = getOtp(dataObject["body"].toString(),type,uidFb);
                if(otp!= ""){
                    return otp;
                }
            }
        } catch (...) {
        }
        Common::DelayTime(3.0);
    // } while (QDateTime::currentSecsSinceEpoch() -tickCount < timeOut);
    return "";
}

QString EmailHelper::getOtp(const QString& body, int type, const QString& uidFb)
{
    QString text = "";
    switch (type)
    {
    case 0:
    {
        QRegularExpression re("https://www.facebook.com/confirmcontact.php(.*?)\"");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(0).trimmed().replace("&", "&").replace("\"", "");
        }
        break;
    }
    case 1:
    {
        QRegularExpression re(">(\\d{8})<");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(1).trimmed();
        }
        if (uidFb.startsWith(text))
        {
            text = "";
        }
        break;
    }
    case 2:
    {
        QRegularExpression re1("\\?n=(.*?)&");
        QRegularExpressionMatch match1 = re1.match(body);
        QString value = match1.hasMatch() ? match1.captured(1) : "";

        QRegularExpression re2(";id=(.*?)&");
        QRegularExpressionMatch match2 = re2.match(body);
        QString text2 = match2.hasMatch() ? match2.captured(1) : uidFb;

        if (!value.isEmpty() && !text2.isEmpty())
        {
            text = "https://m.facebook.com/recover/password/?u=" + text2 + "&n=" + value + "&fl=default_recover&sih=0&msgr=0";
        }
        break;
    }
    case 3:
    {
        QRegularExpression re(">\\d+<");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(0).trimmed().replace(">", "").replace("<", "");
        }
        break;
    }
    case 4:
    {
        QRegularExpression re("c=(\\d+)&");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(1);
        }
        break;
    }
    case 5:
    {
        QRegularExpression re("code=(\\d+)&");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(1);
        }
        break;
    }
    case 6:
    {
        QRegularExpression re("\n\n(\\d+)\n\n");
        QRegularExpressionMatch match = re.match(body);
        if (match.hasMatch())
        {
            text = match.captured(1);
        }
        break;
    }
    }
    return text;
}

QList<QString>* EmailHelper::getListMailDomain(){
    QList<QString>* listRange = new QList<QString>();
    QString url = "https://cdn.autoworker.me/maildomain/get_domains";
    RequestHandle request("","","",0);
    long int tickCount = QDateTime::currentSecsSinceEpoch();
    // do {
        QByteArray text = request.RequestGet(url);
        try {
            QJsonDocument doc = QJsonDocument::fromJson(text);
            QJsonObject jObject = doc.object();
            int status = jObject["status"].toInt();
            if(status == 200){
                QJsonObject result = jObject["result"].toObject();
                if (!result["domains"].toString().isEmpty())
                {
                    QJsonArray domain = result["domains"].toArray();

                    for (const QJsonValue &item : domain)
                    {
                        listRange->append(item.toString());
                    }

                    return listRange;
                }
            }
        } catch (...) {
        }
        Common::DelayTime(3.0);
    // } while (QDateTime::currentSecsSinceEpoch() - tickCount < 60);
    return listRange;
}
