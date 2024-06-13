#include "obcdcom.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "../Utils/Utils.h"
#include "RequestHandle.h"

ObcDcom::ObcDcom(const QString &dcomId, QObject *parent)
    : QObject(parent), dcomId(dcomId) {}

QString ObcDcom::GetDcomId() const {
    return dcomId;
}

void ObcDcom::AddProxy(ObcProxy *proxy) {
    if (proxy) {
        url = proxy->GetServicesURL();
        port = proxy->GetPort();
        lst.append(proxy); // Append the pointer to the list
    }
}

QList<ObcProxy*> ObcDcom::GetListProxy() const {
    return lst;
}

QList<ObcProxy*> ObcDcom::GetListProxyCanUse() const {
    QList<ObcProxy*> list;
    for (const auto &obcProxy : lst) {
        if (obcProxy->isProxyLive && obcProxy->daSuDung < obcProxy->limit_theads_use) {
            list.append(obcProxy);
        }
    }
    return list;
}

bool ObcDcom::ResetDcom() {
    bool result = false;
    try {
        QString text = Utils::trimEnd(url,'/') + "/reset?proxy=" + port + "&type=deep";
        QString json = (new RequestHandle("","","",0))->RequestGet(text);
        QJsonObject jObject = Utils::parseJsonString(json);
        if (jObject.contains("msg") && (jObject["msg"].toString() == "command_sent" || jObject["msg"].toString() == "OK" || jObject["msg"].toString().toLower() == "ok")) {
            result = true;
        } else if (jObject.contains("error_code") && jObject["error_code"].toString().toLower() == "0") {
            result = true;
        }
    } catch (...) {
        // Handle exception
    }
    for (auto &item : lst) {
        item->daSuDung = 0;
    }
    return result;
}

bool ObcDcom::IsCanReset() const {
    for (const auto &obcProxy : lst) {
        if (obcProxy->isProxyLive && (obcProxy->daSuDung != obcProxy->limit_theads_use || obcProxy->dangSuDung != 0)) {
            return false;
        }
    }
    return true;
}

QMap<QString, QList<QString>> ObcDcom::GetListDcomPort(const QString &url) {
    QMap<QString, QList<QString>> dictionary;
    try {
        QString apiUrl = Utils::trimEnd(url,'/') + "/api/v1/dongles/all";
        QString text = (new RequestHandle("", "", "", 0))->RequestGet(apiUrl);
        text = "{ \"data\": " + text + " }";  // Adjust JSON format
        QJsonObject jsonObj = QJsonDocument::fromJson(text.toUtf8()).object();
        QJsonArray dataArray = jsonObj["data"].toArray();
        for (const auto &item : dataArray) {
            QJsonObject obj = item.toObject();
            QString key = obj["rootId"].toString();
            QString itemValue = obj["httpPortV6"].toString();
            dictionary[key].append(itemValue);
        }
    } catch (...) {
        // Handle exception
    }
    return dictionary;
}

ObcDcom* ObcDcom::GetExistObcDcom(QList<ObcDcom*> &listObcDcom, const QString &dcomId) {
    for (auto &obcDcom : listObcDcom) {
        if (obcDcom->GetDcomId() == dcomId) {
            return obcDcom;
        }
    }
    return nullptr;
}

// Destructor to clean up dynamically allocated proxies
ObcDcom::~ObcDcom() {
    for (ObcProxy* proxy : lst) {
        delete proxy;
    }
    lst.clear();
}
