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
    QString checkChromeClose(int instanceId);
    QString delayTime(int instanceId, int timeDelay);
    QString GetPageSource(int instanceId);
    bool isApiRunningExternally() const;
    QString close(int instanceId);
    QString GetUrl(int instanceId);
    QString checkExistElement(int instanceId, QString cssSelectorsOrXpath, double timeWait_Second = 0.0);
    QString checkExistElements(int instanceId, double timeOut, const QStringList &lstCssSelectors);
    QString GetAttributeValue(int instanceId, QString cssSelectorsOrXpath, QString attributeName);
    QString findAndClick(int instanceId, double timeWait_Second, int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    QString sendKeysWithSpeed(int instanceId, int tocDo, int typeAttribute, QString attributeValue, QString content, double timeDelay_Second, bool isClick, double timeDelayAfterClick);
    QString click(int instanceId,int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0, int times = 1);
    QString sendEnter(int instanceId, int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    QString sendKeys(int instanceId, int typeAttribute, QString attributeValue, QString content, bool isClick = true, double timeDelayAfterClick = 0.1);
    QString clickJs(int instanceId, int timeOut=0,const QStringList &lstCssSelectors = {});
    QString clickJs(int instanceId, QString cssSelectorsOrXpath);
    QString CountElement(int instanceId, QString querySelector);
    QString ClickWithAction(int instanceId, int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    QString sendEnter(int instanceId, QString cssSelectorsOrXpath);
    QString ScreenCapture(int instanceId, QString imagePath, QString fileName);
    QString GetUid(int instanceId);
    QString GetCookie(int instanceId, QString domain = "facebook");
    QString ClickWithAction(int instanceId,QString cssSelectorsOrXpath);
    QString click(int instanceId,QString cssSelectorsOrXpath);
    QString GotoURLIfNotExist(int instanceId, QString url);
    QString AddCookieIntoChrome(int instanceId, QString cookie, QString domain = ".facebook.com");
    QString Refresh(int instanceId);
    QString ClearText(int instanceId);
    QString SetSize(int instanceId, int width = 500, int height = 700);
    bool switch_to_alert_accept(int instanceId);
    bool SendKeys(int instanceId, QString csselectorsOrXPath, QString keys);
    bool sendKeysWithSpeed(int instanceId, QString elementSelector, QString text, double speed, bool click_before = true, double click_delay = 0.1);
    bool Clear(int instanceId,QString elementSelector);
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
