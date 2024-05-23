#ifndef COMMONREQUEST_H
#define COMMONREQUEST_H
#include <QString>
#include "../MCommon/requesthandle.h"
#include "../maxcare/setupfolder.h"
#include "qregularexpression.h"
#include "../MCommon/CommonChrome.h"
class CommonRequest{
public:
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
