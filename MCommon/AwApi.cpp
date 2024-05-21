#include "AwApi.h"
#include "requesthandle.h"

QString AwApi::LoginTool(QString username, QString password){
    QString html="";
    try {
        RequestHandle *requestHttp = new RequestHandle("","","",0);
        QByteArray postData;
        postData.append("phone=" + QUrl::toPercentEncoding(username));
        postData.append("&password=" + QUrl::toPercentEncoding(password));
        html = requestHttp->RequestPost("https://api02.app88.me/api/v1/auth/checkToken", "phone="+username+"&password="+password);
        requestHttp->deleteLater();
    } catch (...) {
    }
    return html;
}

QString AwApi::checkUpdate(QString namesoft){
    QString contentc;
    RequestHandle* gclass = new RequestHandle("datr=WZJvYiyKfkXCQUnre2uko636; fr=0oqi8uvi6J1Ke1hP4.AWWnEdQcAIbqvuADKlxidQffUOA.BiXNNR._x.AAA.0.0.Bi14Bb.AWWzPrNJL6o; sb=UNNcYqIKRmV0qebQb9n77CHo", "","",0);
    try {
        return contentc = gclass->RequestGet("https://giau.cc/update/" + namesoft);
    } catch (...) {
    }
    return "";
}
