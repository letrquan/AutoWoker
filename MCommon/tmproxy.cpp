#include "TMProxy.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QThread>
#include <QRegularExpression>
#include <QDateTime>
#include <QDebug>
#include "../MCommon/requesthandle.h"
#include "../Utils/Utils.h"
TMProxy::TMProxy(const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent)
    : ProxyTool(parent), api_key(apiKey), typeProxy(typeProxy), limit_theads_use(limitThreadsUse), proxy(""), ip(""), port(0), next_change(0), timeout(0), dangSuDung(0), daSuDung(0) {}

bool TMProxy::CheckApiProxy(const QString &apiProxy) {
    QString data = QString("{\"api_key\": \"%1\"}").arg(apiProxy);
    QString response = (new RequestHandle("","","",0))->RequestPost("https://tmproxy.com/api/proxy/stats", data,"application/json");
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            QString expiredAt = jsonObj["data"].toObject()["expired_at"].toString();
            QDateTime expiryTime = QDateTime::fromString(expiredAt, "HH:mm:ss dd/MM/yyyy");
            if (expiryTime > QDateTime::currentDateTime()) {
                return true;
            }
        } catch (...) {
            // Handle error
        }
    }
    return false;
}

QString TMProxy::TryToGetMyIP() {
    QMutexLocker locker(&k1);
    if (dangSuDung == 0) {
        if (daSuDung > 0 && daSuDung < limit_theads_use) {
            if (GetTimeOut() < 30 && !ChangeProxy()) {
                return "0";
            }
        } else if (!ChangeProxy()) {
            return "0";
        }
    } else {
        if (daSuDung >= limit_theads_use) {
            return "2";
        }
        if (GetTimeOut() < 30 && !ChangeProxy()) {
            return "0";
        }
    }
    daSuDung++;
    dangSuDung++;
    return "1";
}

int TMProxy::GetTimeOut() {
    CheckStatusProxy();
    return timeout;
}

void TMProxy::DecrementDangSuDung() {
    QMutexLocker locker(&k);
    dangSuDung--;
    if (dangSuDung == 0 && daSuDung == limit_theads_use) {
        daSuDung = 0;
    }
}

bool TMProxy::ChangeProxy() {
    next_change = 0;
    proxy = "";
    ip = "";
    port = 0;
    QString data = "{\"api_key\": \"" + api_key + "\"}";
    QString response = (new RequestHandle("","","",0))->RequestPost("https://tmproxy.com/api/proxy/get-new-proxy", data,"application/json");
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            QString message = jsonObj["message"].toString();
            QRegularExpression regex("\\d+");
            QRegularExpressionMatch match = regex.match(message);
            if (match.hasMatch()) {
                next_change = match.captured(0).toInt();
            }
            if (next_change == 0) {
                if (typeProxy == 0) {
                    proxy = jsonObj["data"].toObject()["https"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                } else {
                    proxy = jsonObj["data"].toObject()["socks5"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                }
                return true;
            }
        } catch (...) {
            // Handle error
        }
    }
    return false;
}

bool TMProxy::CheckStatusProxy() {
    next_change = 0;
    proxy = "";
    ip = "";
    port = 0;
    timeout = 0;
    QString data = QString("{\"api_key\": \"%1\"}").arg(api_key);
    QString response = (new RequestHandle("","","",0))->RequestPost("https://tmproxy.com/api/proxy/get-current-proxy", data,"application/json");
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            if (jsonObj["code"].toString() == "0") {
                next_change = jsonObj["data"].toObject()["next_request"].toInt();
                timeout = jsonObj["data"].toObject()["timeout"].toInt();
                if (typeProxy == 0) {
                    proxy = jsonObj["data"].toObject()["https"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                } else {
                    proxy = jsonObj["data"].toObject()["socks5"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                }
                return true;
            }
        } catch (...) {
            // Handle error
        }
    }
    return false;
}

QString TMProxy::GetProxy() {
    while (!CheckStatusProxy()) {
    }
    return proxy;
}

