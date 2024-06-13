#ifndef TINSOFTPROXY_H
#define TINSOFTPROXY_H
#include "ProxyTool.h"
#include "qmutex.h"
#include <QObject>

class TinsoftProxy : public ProxyTool
{
    Q_OBJECT
public:
    explicit TinsoftProxy(QObject *parent = nullptr);
    TinsoftProxy(const QString &url, const QString &apiKey, int limitThreadsUse, int location = 0, QObject *parent = nullptr);

    void decrementDangSuDung();
    bool changeProxy();
    QString getProxy();
    bool checkStatusProxy(const QString &svContent = "");
    static bool checkApiProxy(const QString &apiProxy);
    static QList<QString> getListKey(const QString &apiUser);

    QString apiKey;
    QString proxy;
    QString ip;
    int port;
    int timeout;
    int nextChange;
    int location;
    QString errorCode;
    bool canChangeIP;
    int dangSuDung;
    int daSuDung;
    int limitThreadsUse;

private:
    QMutex mutex;
    QString svUrl;
    int lastRequest;

    bool checkLastRequest();
    static QString getSVContent(const QString &url);
    QString httpRequestGet(const QString &url);

signals:
    void requestFinished();
};

#endif // TINSOFTPROXY_H
