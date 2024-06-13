#ifndef PROXYV6NET_H
#define PROXYV6NET_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QJsonObject>
#include "ProxyTool.h"

class ProxyV6Net : public ProxyTool {
    Q_OBJECT

public:
    explicit ProxyV6Net(const QString &apiKey, int limitThreadsUse, QObject *parent = nullptr);

    static bool CheckApiProxy(const QString &apiProxy);
    bool ChangeProxy();
    void DecrementDangSuDung();

    int typeProxy;
    QString apiKey;
    QString proxy;
    QString ip;
    int dangSuDung;
    int daSuDung;
    int limitThreadsUse;

private:
    QMutex k;
    QMutex k1;
};

#endif // PROXYV6NET_H
