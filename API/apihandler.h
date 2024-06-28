// apihandler.h
#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcess>
#include <QSize>
#include <QPoint>
#include <QJsonObject>

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    explicit ApiHandler(QObject *parent = nullptr);
    ~ApiHandler();

    void startApiProcess();
    void stopApiProcess();

    QString createInstance(int indexChrome, bool disableImage, const QString &userAgent, const QString &profilePath, const QPoint &size, const QPoint &position, int timeWaitForSearchingElement, int timeWaitForLoadingPage, const QString &proxy, int typeProxy, bool disableSound, const QString &appUrl, bool isUsePortable, const QString &pathToPortableZip);
    QString openBrowser(int instanceId);
    QString gotoUrl(int instanceId, const QString &url);
    QString executeScript(int instanceId, const QString &script);
    void checkChromeClose(int instanceId);
    QString delayTime(int instanceId, int timeDelay);
    QString GetPageSource(int instanceId);
    bool isApiRunningExternally() const;
    QString close(int instanceId);
signals:
    void apiStarted();
    void apiStopped();
    void urlOpened(const QString &message);
    void errorOccurred(const QString &errorString);

private:
    QJsonObject sendRequest(const QString &endpoint, const QJsonObject &jsonObject);
    QJsonObject sendRequest(const QString &endpoint);

    QNetworkAccessManager *m_networkManager;
    QProcess *m_apiProcess;
};

#endif // APIHANDLER_H
