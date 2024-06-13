#ifndef XPROXYPROXY_H
#define XPROXYPROXY_H
#include <QObject>
#include "ProxyTool.h"
#include "qmutex.h"
class XproxyProxy : public ProxyTool
{
    Q_OBJECT
public:
    explicit XproxyProxy(QObject *parent = nullptr);
    XproxyProxy(const QString &servicesURL, const QString &proxy, int typeProxy, int limitThreadsUse);

    int resetProxy();
    int changeProxy();
    bool checkLiveProxy(int timeOut = -1);
    void decrementDangSuDung();
    void method_3(int int_4);

    int typeProxy;
    QString servicesURL;
    QString proxy;
    QString ip;
    bool isProxyLive = true;
    int dangSuDung;
    int daSuDung;
    int limitThreadsUse;
    int int_1 = 0;
    int int_2 = 0;
    int int_3 = 3;

private:
    QMutex mutex;
    void exportToFile(const QString &content);
    QString httpRequestGet(const QString &url);

signals:
    void requestFinished();
};

#endif // XPROXYPROXY_H
