#include "xproxyproxy.h"
#include "qjsonobject.h"
#include "qthread.h"
#include <QFile>
#include <QTextStream>
#include "../maxcare/SettingsTool.h"
#include "requesthandle.h"
#include "../Utils/Utils.h"
XproxyProxy::XproxyProxy(QObject *parent)
    : ProxyTool(parent), servicesURL(""), proxy(""), ip(""), typeProxy(0), limitThreadsUse(3) {}

XproxyProxy::XproxyProxy(const QString &servicesURL, const QString &proxy, int typeProxy, int limitThreadsUse)
    : ProxyTool(nullptr), servicesURL(servicesURL), proxy(proxy), ip(""), typeProxy(typeProxy), limitThreadsUse(limitThreadsUse) {}

void XproxyProxy::exportToFile(const QString &content) {
    // QFile file("exported.txt");
    // if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
    //     QTextStream out(&file);
    //     out << content << "\n";
    // }
    // file.close();
}


int XproxyProxy::resetProxy() {
    bool flag = false;
    try {
        servicesURL = Utils::trimEnd(servicesURL,'/');
        QString text = servicesURL + "/reset?proxy=" + proxy.split(':')[0] + ":" + proxy.split(':')[1];
        QString text2 = (new RequestHandle("", "", "", 0))->RequestGet(text);
        if (text2.contains("reset_too_much")) {
            QThread::sleep(5);
            return 2;
        }
        QJsonObject jsonObj = Utils::parseJsonString(text2);

        if (jsonObj.contains("msg") && (jsonObj["msg"].toString() == "command_sent" || jsonObj["msg"].toString() == "OK" || jsonObj["msg"].toString().toLower() == "ok")) {
            flag = true;
        } else if (jsonObj.contains("error_code") && jsonObj["error_code"].toString().toLower() == "0") {
            flag = true;
        } else {
            exportToFile(text + ": " + text2);
        }
    } catch (...) {
        // Handle exception
    }

    return flag ? 1 : 0;
}

int XproxyProxy::changeProxy() {
    try {
        int num = 0;
        for (int i = 0; i < 5; ++i) {
            num = resetProxy();
            if (num == 1) {
                num = checkLiveProxy() ? 1 : 0;
            }
            if (num == 1) {
                break;
            }
        }
        return num;
    } catch (...) {
        // Handle exception
    }
    return 0;
}

bool XproxyProxy::checkLiveProxy(int timeOut) {
    if (timeOut == -1) {
        timeOut = SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayResetXProxy", 5) * 60;
    }

    int startTime = QDateTime::currentSecsSinceEpoch();
    bool flag = false;

    try {
        servicesURL = Utils::trimEnd(servicesURL,'/');
        QString url = servicesURL + "/status?proxy=" + proxy.split(':')[0] + ":" + proxy.split(':')[1];
        RequestHandle requestHandle("", "", "", 0);
        QString response;

        while (true) {
            response = requestHandle.RequestGet(url);
            try {
                QJsonObject jsonObj = Utils::parseJsonString(response);

                if (!response.contains("public_ip_v6") && !response.contains("public_ip")) {
                    flag = jsonObj["status"].toBool();
                } else {
                    QString portPart = proxy.split(':').at(1);
                    if (portPart.startsWith("4") || portPart.startsWith("5")) {
                        flag = (jsonObj["public_ip"].toString() != "" && jsonObj["public_ip"].toString() != "CONNECT_INTERNET_ERROR");
                    } else if (portPart.startsWith("6") || portPart.startsWith("7")) {
                        flag = (jsonObj["public_ip_v6"].toString() != "" && jsonObj["public_ip_v6"].toString() != "CONNECT_INTERNET_ERROR");
                    } else {
                        flag = jsonObj["status"].toBool();
                    }
                }
            } catch (...) {
                flag = Utils::parseJsonString(response)["error_code"].toString() == "0";
            }

            QThread::sleep(1);

            if (!flag) {
                if (QDateTime::currentSecsSinceEpoch() - startTime >= timeOut) {
                    return flag;
                }
                continue;
            }
            break;
        }
        return flag;
    } catch (...) {
        return flag;
    }
}

void XproxyProxy::decrementDangSuDung() {
    QMutexLocker locker(&mutex);
    dangSuDung--;
    if (SettingsTool::GetSettings("configGeneral").GetValueInt("typeRunXproxy") == 0 && dangSuDung == 0 && daSuDung == limitThreadsUse) {
        daSuDung = 0;
    }
}

void XproxyProxy::method_3(int int_4) {
    QMutexLocker locker(&mutex);
    int_1--;
    if (int_4 == 0 && int_1 == 0 && int_2 == int_3) {
        int_2 = 0;
    }
}
