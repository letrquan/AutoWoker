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
#include "../MCommon/Common.h"
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

    static QString GetTokenEAAAAU(QString uid, QString password, QString fa2, QString cookie, QString proxy = "", int typeProxy = 0){
        QString result = "";
        try {
            RequestHandle requestHttp(cookie, "", proxy, typeProxy);
            static const QRegularExpression re("datr=(.*?);");
            QString text = re.match(cookie + ";").captured(1);
            if (text == "")
            {
                text = Common::CreateRandomString(8, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(12, "0_a_A");
            }
            QString value = Common::CreateRandomString(8, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(12, "0_a_A");
            QString value2 = Common::CreateRandomString(8, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(12, "0_a_A");
            QString value3 = Common::CreateRandomString(8, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(4, "0_a_A") + "-" + Common::CreateRandomString(12, "0_a_A");
            QString data = QString("adid=%1&format=json&device_id=%2&email=%3&password=%4&generate_analytics_claim=1&community_id=&cpl=true&try_num=1&family_device_id=%2&secure_family_device_id=%5&credentials_type=password&fb4a_shared_phone_cpl_experiment=fb4a_shared_phone_nonce_cpl_at_risk_v3&fb4a_shared_phone_cpl_group=enable_v3_at_risk&enroll_misauth=false&generate_session_cookies=1&error_detail_type=button_with_disabled&source=login&machine_id=%6&jazoest=22421&meta_inf_fbmeta=&advertiser_id=%1&encrypted_msisdn=&currently_logged_in_userid=0&locale=vi_VN&client_country_code=VN&fb_api_req_friendly_name=authenticate&fb_api_caller_class=Fb4aAuthHandler&api_key=882a8490361da98702bf97a021ddc14d&access_token=350685531728|62f8ce9f74b12f84c123cc23437a4a32")
                               .arg(value2, value, uid, password, value3, text);
            QString text2 = requestHttp.RequestPost("https://b-graph.facebook.com/auth/login", data);
            if (text2.contains("Invalid username or password"))
            {
                return "Invalid username or password";
            }
            auto jObject = Utils::parseJsonString(text2);
            QJsonValueRef js = jObject["error"].toObject()["error_subcode"];
            try {
                if(!js.isNull()){
                    if(js.toString() == "1348077"){
                        return result;
                    }
                    if(js.toString() == "1348131"){
                        return result;
                    }
                }
            } catch (...) {

            }
            try {
                if(js.toString() == "1348162" || js.toString() == "1348199"){
                    QString value4 = jObject["error"].toObject()["error_data"].toObject()["login_first_factor"].toString();
                    QString value5 = jObject["error"].toObject()["error_data"].toObject()["uid"].toString();
                    QString totp = Common::GetTotp(fa2);
                    data = QString("adid=%1&format=json&device_id=%2&email=%3&password=%4&generate_analytics_claim=1&community_id=&cpl=true&try_num=2&family_device_id=%2&secure_family_device_id=%5&sim_serials=[]&credentials_type=two_factor&fb4a_shared_phone_cpl_experiment=fb4a_shared_phone_nonce_cpl_at_risk_v3&fb4a_shared_phone_cpl_group=enable_v3_at_risk&enroll_misauth=false&generate_session_cookies=1&error_detail_type=button_with_disabled&source=login&machine_id=%6&jazoest=22327&meta_inf_fbmeta=&twofactor_code=%4&userid=%7&first_factor=%8&advertiser_id=%1&encrypted_msisdn=&currently_logged_in_userid=0&locale=vi_VN&client_country_code=VN&fb_api_req_friendly_name=authenticate&fb_api_caller_class=Fb4aAuthHandler&api_key=882a8490361da98702bf97a021ddc14d&access_token=350685531728|62f8ce9f74b12f84c123cc23437a4a32")
                                       .arg(value2, value, uid, totp, value3, text, value5, value4);
                    text2 = requestHttp.RequestPost("https://b-graph.facebook.com/auth/login", data);
                    if (text2.contains("\"code\":401"))
                    {
                        return result;
                    }
                    jObject = Utils::parseJsonString(text2);
                }
            } catch (...) {
            }
            result = jObject["access_token"].toString();
            return result;
        } catch (...) {
            return result;
        }
    }
};
#endif // COMMONREQUEST_H
