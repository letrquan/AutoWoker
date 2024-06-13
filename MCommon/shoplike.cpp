#include "shoplike.h"
#include "requesthandle.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>
#include "requesthandle.h"
#include "../Utils/Utils.h"
ShopLike::ShopLike(const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent)
    : ProxyTool(parent), api_key(apiKey), typeProxy(typeProxy), limitThreadsUse(limitThreadsUse), proxy(""), ip(""), port(0), dangSuDung(0), daSuDung(0) {}

void ShopLike::DecrementDangSuDung() {
    QMutexLocker locker(&k);
    dangSuDung--;
    if (dangSuDung == 0 && daSuDung == limitThreadsUse) {
        daSuDung = 0;
    }
}

bool ShopLike::ChangeProxy() {
    try {
        proxy = "";
        ip = "";
        port = 0;
        QString url = "http://proxy.shoplike.vn/Api/getNewProxy?access_token=" + api_key;
        QString response = (new RequestHandle("","","",0))->RequestGet(url);
        if (!response.isEmpty()) {
            try {
                QJsonObject jsonObj = Utils::parseJsonString(response);
                if (jsonObj["status"].toString() == "success") {
                    if (typeProxy == 0) {
                        proxy = jsonObj["data"].toObject()["proxy"].toString();
                        QStringList proxyParts = proxy.split(':');
                        ip = proxyParts[0];
                        port = proxyParts[1].toInt();
                    }
                    return true;
                }
            } catch (...) {
                // Handle exception
            }
        }
    } catch (...) {
        // Handle exception
    }
    return false;
}

bool ShopLike::CheckStatusProxy() {
    proxy = "";
    ip = "";
    port = 0;
    QString url = "http://proxy.shoplike.vn/Api/getCurrentProxy?access_token=" + api_key;
    QString response = (new RequestHandle("","","",0))->RequestGet(url);
    if (!response.isEmpty()) {
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            if (jsonObj["status"].toString() == "success") {
                proxy = jsonObj["data"].toObject()["proxy"].toString();
                QStringList proxyParts = proxy.split(':');
                ip = proxyParts[0];
                port = proxyParts[1].toInt();
                return true;
            }
        } catch (...) {
            // Handle exception
        }
    }
    return false;
}

QString ShopLike::GetProxy() {
    while (!CheckStatusProxy()) {  // Wait until proxy status is valid
    }
    return proxy;
}
