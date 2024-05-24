#ifndef COMMONREQUEST_H
#define COMMONREQUEST_H
#include <QString>
#include "../MCommon/requesthandle.h"
#include "../maxcare/setupfolder.h"
#include "qregularexpression.h"
#include "../MCommon/CommonChrome.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "../Utils/Utils.h"
class CommonRequest{
public:
    static QString CheckInfoUsingUid(QString uid, QString proxy = "", int typeProxy = 0){
        RequestHandle gclass("", "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) AppleWebKit/603.2.4 (KHTML, like Gecko) Mobile/14F89", proxy, typeProxy);
        try {
            auto json =  Utils::parseJsonString(gclass.RequestPost("https://www.facebook.com/api/graphql", "q=node(" + uid + "){name}"));
            if(!json.contains(uid) && json[uid].toString().isEmpty()){
                return "0|";
            }
            auto text = json[uid].toObject()["name"].toString();
            json = Utils::parseJsonString(gclass.RequestPost("https://www.facebook.com/api/graphql", "q=node(" + uid + "){friends{count}}"));
            if(!json.contains(uid) && json[uid].toString().isEmpty()){
                return "0|";
            }
            auto text2 = json[uid].toObject()["friends"].toObject()["count"].toString();
            json = Utils::parseJsonString(gclass.RequestPost("https://www.facebook.com/api/graphql", "q=node(" + uid + "){created_time}"));
            if(!json.contains(uid) && json[uid].toString().isEmpty()){
                return "0|";
            }
            auto text3 = tut8(json[uid].toObject()["created_time"].toDouble()).toString();
            QString result = "1|" + text + "|" + text2 + "|" + text3;
            return result;
        } catch (...) {
        }
        return "2|";
    }
    static QDateTime tut8(double timestamp) {
        // Create a QDateTime object set to the epoch time (1970-01-01T00:00:00 UTC)
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(timestamp), Qt::UTC);

        // Convert the time to the local time zone
        dateTime = dateTime.toLocalTime();

        return dateTime;
    }
    static QString CheckLiveWall(QString uid){
        RequestHandle* gclass = new RequestHandle("datr=WZJvYiyKfkXCQUnre2uko636; fr=0oqi8uvi6J1Ke1hP4.AWWnEdQcAIbqvuADKlxidQffUOA.BiXNNR._x.AAA.0.0.Bi14Bb.AWWzPrNJL6o; sb=UNNcYqIKRmV0qebQb9n77CHo",SetupFolder::smethod_88(),"",0);
        try {
            QString text = gclass->RequestGet("https://graph.facebook.com/" + uid + "/picture?type=normal&redirect=false");
            if (text.contains("height") && text.contains("width"))
            {
                return "1|";
            }
            try {
                text = gclass->RequestGet("https://graph.facebook.com/" + uid + "/picture?width=500&access_token=6628568379%7Cc1e620fa708a1d5696fb991c1bde5662&redirect=false");
                if (text.contains(".gif") || text.contains("error"))
                {
                    return "0|";
                }
                return "1|";
            } catch (...) {
            }
        } catch (...) {
        }
        return "2|";
    }
    static bool CheckLiveToken(QString cookie, QString token, QString useragent, QString proxy, int typeProxy = 0)
    {
        bool result = false;
        try
        {
            (new RequestHandle(cookie, useragent, proxy, typeProxy))->RequestGet("https://graph.facebook.com/me?access_token=" + token);
            result = true;
            return result;
        }
        catch(...)
        {
            return result;
        }
    }
    static QString CheckLiveCookie(const QString &cookie, const QString &userAgent, const QString &proxy, int typeProxy) {
        QString result = "0|0";
        QRegularExpression re("c_user=(\\d+)");
        QRegularExpressionMatch match = re.match(cookie);
        QString value = match.hasMatch() ? match.captured(1) : "";

        try {
            RequestHandle requestXNet(cookie, "Mozilla/5.0 (iPhone; CPU iPhone OS 13_2 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) CriOS/102.0.5005.63 Mobile/15E148 Safari/604.1", proxy, typeProxy);
            if (!value.isEmpty()) {
                QString content = requestXNet.RequestGet("https://m.facebook.com/home.php");
                QStringList lstKeyword = { "/friends/", "/logout.php?button_location=settings&amp;button_name=logout" };
                if (CommonChrome::CheckStringContainKeyword(content, lstKeyword)) {
                    return "1|1";
                }
                return result;
            }
            return result;
        } catch (...) {
            return result;
        }
    }
};
#endif // COMMONREQUEST_H
