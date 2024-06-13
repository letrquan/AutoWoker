#include "minproxy.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QRegularExpression>
#include <QDateTime>
#include <QDebug>
#include "../Utils/Utils.h"
#include "requesthandle.h"
MinProxy::MinProxy(int type, const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent)
    : ProxyTool(parent), type(type), api_key(apiKey), typeProxy(typeProxy), limit_theads_use(limitThreadsUse), proxy(""), ip(""), port(0), next_change(0), timeout(0), dangSuDung(0), daSuDung(0), ip_allow(""), your_ip(""), lastRequest(0) {}

bool MinProxy::CheckApiProxy(int type, const QString &apiProxy) {
    QString url = (type != 0) ? "http://dash.minproxy.vn/api/rotating/v1/proxy_v4/get-status?api_key=" + apiProxy
                              : "http://dash.minproxy.vn/api/rotating/v1/proxy/get-status?api_key=" + apiProxy;
    QString response = (new RequestHandle("","","",0))->RequestGet(url);
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            return jsonObj["code"].toString() == "1";
        } catch (...) {
            // Handle error
        }
    }
    return false;
}

QString MinProxy::TryToGetMyIP() {
    QMutexLocker locker(&k1);
    if (dangSuDung == 0) {
        if (daSuDung > 0 && daSuDung < limit_theads_use) {
            if (GetTimeOut() < 30 && ChangeProxy() != 1) {
                return "0";
            }
        } else if (ChangeProxy() != 1) {
            return "0";
        }
    } else {
        if (daSuDung >= limit_theads_use) {
            return "2";
        }
        if (GetTimeOut() < 30 && ChangeProxy() != 1) {
            return "0";
        }
    }
    daSuDung++;
    dangSuDung++;
    return "1";
}

int MinProxy::GetTimeOut() {
    CheckStatusProxy();
    return timeout;
}

void MinProxy::DecrementDangSuDung() {
    QMutexLocker locker(&k);
    dangSuDung--;
    if (dangSuDung == 0 && daSuDung == limit_theads_use) {
        isBlock = true;
        daSuDung = 0;
    }
}

int MinProxy::ChangeProxy() {
    proxy = "";
    ip = "";
    port = 0;
    QString url = (type != 0) ? "http://dash.minproxy.vn/api/rotating/v1/proxy_v4/get-new-proxy?api_key=" + api_key
                              : "http://dash.minproxy.vn/api/rotating/v1/proxy/get-new-proxy?api_key=" + api_key;
    QString response = (new RequestHandle("","","",0))->RequestGet(url);
    if (!response.isEmpty()) {
        if (response.contains("api expired")) {
            return -1;
        }
        if (response.contains("api wrong") || response.contains("error")) {
            return -2;
        }
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            QString value = QRegularExpression("\\d+").match(jsonObj["data"].toObject()["next_request"].toString()).captured(0);
            next_change = value.isEmpty() ? 0 : value.toInt();
            if (jsonObj["code"].toString() == "2") {
                QJsonObject data = jsonObj["data"].toObject();
                ip_allow = data["ip_allow"].toString();
                your_ip = data["your_ip"].toString();
                if (type == 0) {
                    proxy = data["http_proxy"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                    return 1;
                } else {
                    if (typeProxy == 0) {
                        proxy = data["http_proxy_ipv4"].toString();
                    } else if (typeProxy == 1) {
                        proxy = data["http_proxy_ipv6"].toString();
                    } else if (typeProxy == 2) {
                        proxy = data["sock_proxy_ipv4"].toString();
                    } else {
                        proxy = data["sock_proxy_ipv6"].toString();
                    }
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                    return 1;
                }
            }
        } catch (...) {
            // Handle error
        }
    }
    next_change = 0;
    return 0;
}

bool MinProxy::CheckStatusProxy() {
    next_change = 0;
    proxy = "";
    ip = "";
    port = 0;
    timeout = 0;
    QString url = (type != 0) ? "http://dash.minproxy.vn/api/rotating/v1/proxy_v4/get-current-proxy?api_key=" + api_key
                              : "http://dash.minproxy.vn/api/rotating/v1/proxy/get-current-proxy?api_key=" + api_key;
    QString response = (new RequestHandle("","","",0))->RequestGet(url);
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            if (jsonObj["code"].toString() == "1") {
                QJsonObject data = jsonObj["data"].toObject();
                next_change = data["next_request"].toInt();
                timeout = data["timeout"].toInt();
                ip_allow = data["ip_allow"].toString();
                your_ip = data["your_ip"].toString();
                if (type == 0) {
                    proxy = data["http_proxy"].toString();
                    QStringList proxyParts = proxy.split(':');
                    ip = proxyParts[0];
                    port = proxyParts[1].toInt();
                } else {
                    if (typeProxy == 0) {
                        proxy = data["http_proxy_ipv4"].toString();
                    } else if (typeProxy == 1) {
                        proxy = data["http_proxy_ipv6"].toString();
                    } else if (typeProxy == 2) {
                        proxy = data["sock_proxy_ipv4"].toString();
                    } else {
                        proxy = data["sock_proxy_ipv6"].toString();
                    }
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

QString MinProxy::GetProxy() {
    while (!CheckStatusProxy()) {
  // Wait until proxy status is valid
    }
    return proxy;
}
