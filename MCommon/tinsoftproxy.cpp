#include "tinsoftproxy.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "requesthandle.h"
#include "../Utils/Utils.h"
#include <QObject>
TinsoftProxy::TinsoftProxy(QObject *parent)
    : ProxyTool(parent), svUrl("http://api.proxyfb.com"), lastRequest(0), canChangeIP(true), dangSuDung(0), daSuDung(0), limitThreadsUse(3), port(0), timeout(0), nextChange(0), location(0) {}

TinsoftProxy::TinsoftProxy(const QString &url, const QString &apiKey, int limitThreadsUse, int location, QObject *parent)
    : ProxyTool(parent), svUrl(url), apiKey(apiKey), lastRequest(0), canChangeIP(true), dangSuDung(0), daSuDung(0), limitThreadsUse(limitThreadsUse), port(0), timeout(0), nextChange(0), location(location) {}

void TinsoftProxy::decrementDangSuDung() {
    QMutexLocker locker(&mutex);
    dangSuDung--;
    if (dangSuDung == 0 && daSuDung == limitThreadsUse) {
        daSuDung = 0;
    }
}

bool TinsoftProxy::changeProxy() {
    if (checkLastRequest()) {
        try {
            QString response = (new RequestHandle("", "", "", 0))->RequestGet(svUrl+"/api/changeProxy.php?key="+apiKey+"&location="+QString::number(location));
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
            if (jsonDoc["success"].toString().toLower() == "true") {
                return checkStatusProxy(response);
            }
        } catch (...) {
            // Handle exception
        }
    } else {
        errorCode = "Request so fast!";
    }
    return false;
}

QString TinsoftProxy::getProxy() {
    while (!checkStatusProxy()) {
        // Wait until proxy status is valid
    }
    return proxy;
}

bool TinsoftProxy::checkStatusProxy(const QString &svContent) {
    errorCode = "";
    nextChange = 0;
    proxy = "";
    ip = "";
    port = 0;
    timeout = 0;
    try {
        QString content = svContent.isEmpty() ? (new RequestHandle("", "", "", 0))->RequestGet(svUrl + "/api/getProxy.php?key=" + apiKey) : svContent;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj["success"].toBool()) {
            proxy = jsonObj["proxy"].toString();
            QStringList proxyParts = proxy.split(':');
            if (proxyParts.size() == 2) {
                ip = proxyParts[0];
                port = proxyParts[1].toInt();
                timeout = jsonObj["timeout"].toInt();
                nextChange = jsonObj["next_change"].toInt();
                errorCode = "";
                return true;
            }
        }
        errorCode = jsonObj["description"].toString();
        if (jsonObj.contains("next_change")) {
            nextChange = jsonObj["next_change"].toInt();
        }
    } catch (...) {
    }

    return false;
}

bool TinsoftProxy::checkLastRequest() {
    try {
        QDateTime epoch(QDate(2001, 1, 1), QTime(0, 0));
        QDateTime currentTime = QDateTime::currentDateTime();
        qint64 secondsSinceEpoch = epoch.secsTo(currentTime);

        if (secondsSinceEpoch - lastRequest >= 10) {
            lastRequest = static_cast<int>(secondsSinceEpoch);
            return true;
        }
    } catch (...) {
        // Handle exceptions if necessary
    }
    return false;
}

QString TinsoftProxy::getSVContent(const QString &url) {
    QString text = "";
    try {
        text = (new RequestHandle("","","",0))->RequestGet(url);

    } catch (...) {
    }
    if (text.isEmpty() || text.isNull())
    {
        text = "";
    }
    return text;
}

bool TinsoftProxy::checkApiProxy(const QString &apiProxy) {
    QString content = getSVContent(QString("http://proxy.tinsoftsv.com/api/getKeyInfo.php?key=%1").arg(apiProxy));
    QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    return jsonObj["success"].toBool();
}

QList<QString> TinsoftProxy::getListKey(const QString &apiUser) {
    QList<QString> list;
    try {
        auto dataArray= Utils::parseJsonString(((new RequestHandle("", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;)", "", 0))->RequestGet("http://proxy.tinsoftsv.com/api/getUserKeys.php?key=" + apiUser)))["data"].toArray();
        for (const QJsonValue &value : dataArray) {
            QJsonObject item = value.toObject();
            if (item["success"].toBool()) {
                list.append(item["key"].toString());
            }
        }
    } catch (...) {
        // Handle exception
    }
    return list;
}
