#ifndef SHOPLIKE_H
#define SHOPLIKE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QJsonObject>
#include "ProxyTool.h"

class ShopLike : public ProxyTool {
    Q_OBJECT

public:
    explicit ShopLike(const QString &apiKey, int typeProxy, int limitThreadsUse, QObject *parent = nullptr);

    void DecrementDangSuDung();
    bool ChangeProxy();
    bool CheckStatusProxy();
    QString GetProxy();

    int typeProxy;
    QString api_key;
    QString proxy;
    QString ip;
    int port;
    int dangSuDung;
    int daSuDung;
    int limitThreadsUse;

private:
    QMutex k;
};

#endif // SHOPLIKE_H
