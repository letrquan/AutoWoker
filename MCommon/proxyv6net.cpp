#include "proxyv6net.h"
#include "qjsondocument.h"
#include "requesthandle.h"
#include "../Utils/Utils.h"
ProxyV6Net::ProxyV6Net(const QString &apiKey, int limitThreadsUse, QObject *parent)
    : ProxyTool(parent), apiKey(apiKey), limitThreadsUse(limitThreadsUse), proxy(""), ip(""), dangSuDung(0), daSuDung(0) {}

bool ProxyV6Net::CheckApiProxy(const QString &apiProxy) {
    try {
        QString url = "https://api.proxyv6.net/key/get-current-ip?api_key_rotating=" + apiProxy;
        QString response = (new RequestHandle("","","",0))->RequestGet(url);
        return response.contains("SUCCESS");
    } catch (...) {
        // Handle exception
    }
    return false;
}

bool ProxyV6Net::ChangeProxy() {
    bool result = false;
    try {
        QString url = "https://api.proxyv6.net/key/get-new-ip?api_key_rotating=" + apiKey;
        QString response = (new RequestHandle("","","",0))->RequestGet(url);
        try {
            QJsonObject jsonObj = Utils::parseJsonString(response);
            if (jsonObj["message"].toString() == "SUCCESS") {
                QJsonObject data = jsonObj["data"].toObject();
                proxy = data["host"].toString() + ":" + data["port"].toString();
                ip = data["ip"].toString();
                result = true;
            }
        } catch (...) {
            // Handle exception
        }
    } catch (...) {
        // Handle exception
    }
    return result;
}

void ProxyV6Net::DecrementDangSuDung() {
    QMutexLocker locker(&k);
    dangSuDung--;
    if (dangSuDung == 0 && daSuDung == limitThreadsUse) {
        daSuDung = 0;
    }
}

