#ifndef OBCPROXY_H
#define OBCPROXY_H

#include <QObject>
#include <QString>
#include <QThread>
#include "ProxyTool.h"
#include "RequestHandle.h"
#include "../maxcare/SettingsTool.h"

class ObcProxy : public ProxyTool {
    Q_OBJECT

public:
    explicit ObcProxy(const QString &servicesURL, const QString &proxy, int typeProxy, int limitThreadsUse, const QString &dcomId, QObject *parent = nullptr);

    bool ResetProxy();
    bool ChangeProxy();
    void DecrementDangSuDung(int typeRun = 1);
    bool CheckLiveProxy(int timeOut = -1);

    QString GetDcomId() const;
    void SetDcomId(const QString &rootId);
    QString GetServicesURL() const;
    QString GetPort() const;

    int typeProxy;
    QString ServicesURL;
    QString proxy;
    QString ip;
    bool isProxyLive;
    int dangSuDung;
    int daSuDung;
    int limit_theads_use;

private:
    QString dcomId;
    void ExportToFile(const QString &content);
};

#endif // OBCPROXY_H
