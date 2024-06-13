#ifndef TMPROXY_H
#define TMPROXY_H
#include "ProxyTool.h"
#include "qmutex.h"
class TMProxy : public ProxyTool {
    Q_OBJECT

public:
    explicit TMProxy(const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent = nullptr);

    static bool CheckApiProxy(const QString &apiProxy);
    QString TryToGetMyIP();
    int GetTimeOut();
    void DecrementDangSuDung();
    bool ChangeProxy();
    bool CheckStatusProxy();
    QString GetProxy();

    QString api_key;
    QString proxy;
    QString ip;
    int typeProxy;
    int timeout;
    int port;
    int next_change;
    int dangSuDung;
    int daSuDung;
    int limit_theads_use;

private:
    QMutex k1;
    QMutex k;
};

#endif // TMPROXY_H
