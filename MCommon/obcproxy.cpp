#include "obcproxy.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "../Utils/Utils.h"
ObcProxy::ObcProxy(const QString &servicesURL, const QString &proxy, int typeProxy, int limitThreadsUse, const QString &dcomId, QObject *parent)
    : ProxyTool(parent), ServicesURL(servicesURL), proxy(proxy), typeProxy(typeProxy), limit_theads_use(limitThreadsUse), dcomId(dcomId), ip(""), isProxyLive(true), dangSuDung(0), daSuDung(0) {}

void ObcProxy::ExportToFile(const QString &content) {

}

bool ObcProxy::ResetProxy() {
    bool result = false;
    try {
        ServicesURL =Utils::trimEnd(ServicesURL,'/');
        QString text = ServicesURL + "/reset?proxy=" + proxy;
        QString response =(new RequestHandle("","","",0))->RequestGet(text);
        ExportToFile(text + ": " + response);
        QJsonObject jsonObj = Utils::parseJsonString(response);
        if (jsonObj.contains("msg") && (jsonObj["msg"].toString() == "command_sent" || jsonObj["msg"].toString() == "OK" || jsonObj["msg"].toString().toLower() == "ok")) {
            result = true;
        } else if (jsonObj.contains("error_code") && jsonObj["error_code"].toString().toLower() == "0") {
            result = true;
        }
    } catch (...) {
        // Handle exception
    }
    return result;
}

bool ObcProxy::ChangeProxy() {
    bool result = false;
    try {
        ServicesURL = Utils::trimEnd(ServicesURL,'/');
        QString text = ServicesURL + "/reset?proxy=" + proxy;
        QString response = (new RequestHandle("","","",0))->RequestGet(text);
        ExportToFile(text + ": " + response);
        QJsonObject jsonObj = Utils::parseJsonString(response);
        bool flag = false;
        if (jsonObj.contains("msg") && (jsonObj["msg"].toString() == "command_sent" || jsonObj["msg"].toString() == "OK" || jsonObj["msg"].toString().toLower() == "ok")) {
            flag = true;
        } else if (jsonObj.contains("error_code") && jsonObj["error_code"].toString().toLower() == "0") {
            flag = true;
        }
        if (flag) {
            return CheckLiveProxy();
        }
    } catch (...) {
        // Handle exception
    }
    return result;
}

void ObcProxy::DecrementDangSuDung(int typeRun) {
    dangSuDung--;
    if (typeRun == 0 && dangSuDung == 0 && daSuDung == limit_theads_use) {
        daSuDung = 0;
    }
}

bool ObcProxy::CheckLiveProxy(int timeOut) {
    if (timeOut == -1) {
        timeOut = SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIPObcProxy", 5) * 60;
    }
    int tickCount = QDateTime::currentMSecsSinceEpoch();
    bool flag = false;
    try {
        ServicesURL = Utils::trimEnd(ServicesURL,'/');
        QString text = ServicesURL + "/status?proxy=" + proxy;
        RequestHandle requestHandle("","","",0);
        QString response;
        while (true) {
            response = requestHandle.RequestGet(text);
            ExportToFile(text + ": " + response);
            try {
                QJsonObject jsonObj = Utils::parseJsonString(response);
                if (!response.contains("public_ip_v6") && !response.contains("public_ip")) {
                    flag = jsonObj["status"].toBool();
                } else {
                    QString portPart = proxy.split(':')[1];
                    if (portPart.startsWith("4") || portPart.startsWith("5")) {
                        flag = (!jsonObj["public_ip"].toString().isEmpty() && jsonObj["public_ip"].toString() != "CONNECT_INTERNET_ERROR");
                    } else if (portPart.startsWith("6") || portPart.startsWith("7")) {
                        flag = (!jsonObj["public_ip_v6"].toString().isEmpty() && jsonObj["public_ip_v6"].toString() != "CONNECT_INTERNET_ERROR");
                    }
                }
            } catch (...) {
                QJsonObject jsonObj = QJsonDocument::fromJson(response.toUtf8()).object();
                flag = jsonObj["error_code"].toString() == "0";
            }
            QThread::sleep(1);
            if (!flag) {
                if (QDateTime::currentMSecsSinceEpoch() - tickCount >= timeOut) {
                    return flag;
                }
                continue;
            }
            break;
        }
    } catch (...) {
        // Handle exception
    }
    return flag;
}

QString ObcProxy::GetDcomId() const {
    return dcomId;
}

void ObcProxy::SetDcomId(const QString &rootId) {
    dcomId = rootId;
}

QString ObcProxy::GetServicesURL() const {
    return ServicesURL;
}

QString ObcProxy::GetPort() const {
    return proxy.split(':')[1];
}
