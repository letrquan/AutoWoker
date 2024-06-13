#ifndef MINPROXY_H
#define MINPROXY_H

#include <QObject>
#include <QMutex>
#include "ProxyTool.h"

class MinProxy : public ProxyTool {
    Q_OBJECT

public:
    explicit MinProxy(int type, const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent = nullptr);

    static bool CheckApiProxy(int type, const QString &apiProxy);
    QString TryToGetMyIP();
    int GetTimeOut();
    void DecrementDangSuDung();
    int ChangeProxy();
    bool CheckStatusProxy();
    QString GetProxy();
    int typeProxy;
    int type;
    QString api_key;
    QString proxy;
    QString ip;
    int timeout;
    int port;
    int next_change;
    QString ip_allow;
    QString your_ip;
    int dangSuDung;
    int daSuDung;
    int limit_theads_use;
    bool isBlock = true;

private:
    QMutex k;
    QMutex k1;
    int lastRequest;
};

#endif // MINPROXY_H
