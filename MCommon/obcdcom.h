#ifndef OBCDCOM_H
#define OBCDCOM_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include "ObcProxy.h"

class ObcDcom : public QObject {
    Q_OBJECT

public:
    explicit ObcDcom(const QString &dcomId, QObject *parent = nullptr);

    QString GetDcomId() const;
    void AddProxy(ObcProxy *proxy); // Change to accept pointer
    QList<ObcProxy *> GetListProxy() const;
    QList<ObcProxy *> GetListProxyCanUse() const;
    bool ResetDcom();
    bool IsCanReset() const;

    static QMap<QString, QList<QString>> GetListDcomPort(const QString &url);
    static ObcDcom* GetExistObcDcom(QList<ObcDcom*> &listObcDcom, const QString &dcomId);

    ~ObcDcom(); // Destructor to clean up dynamically allocated proxies

private:
    QString url;
    QString port;
    QString dcomId;
    QList<ObcProxy*> lst;
};

#endif // OBCDCOM_H
