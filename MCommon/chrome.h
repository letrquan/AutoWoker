#ifndef CHROME_H
#define CHROME_H
#include <QString>
#include <QPoint>
#include "../maxcare/Enum/StatusChromeAccount.h"
#include "qprocess.h"
#include "../API/apihandler.h"
class Chrome
{
public:
    Chrome();
    int indexChrome;
    QProcess process;
    bool HideBrowser;
    bool Incognito;
    bool DisableImage;
    bool DisableSound;
    bool AutoPlayVideo;
    QString UserAgent;
    int PixelRatio;
    QString ProfilePath;
    QPoint Size;
    QPoint Position;
    int TimeWaitForSearchingElement;
    int TimeWaitForLoadingPage;
    QString Proxy;
    int TypeProxy;
    QString App;
    QString LinkToOtherBrowser;
    QString PathExtension;
    bool IsUseEmulator;
    bool IsUsePortable;
    QString PathToPortableZip;
    double Scale;
    QPoint Size_Emulator;
    int E82A933C;
    StatusChromeAccount Status;
    QString String_5;
    int Int32_2;
    bool EA173000;
    bool D5084A9D;
    bool Boolean_3;
    QString ACB9092E;
    int Int32_1;
    bool Open();
    bool GotoURL(QString url);
    bool DelayTime(double seconds);
    QString GetPageSource();
    QString GetUrl();
    int Close();
    int gotoLogin(int typeWeb);
    QString ExecuteScript(QString script);
    int CheckExistElement(QString cssSelectorsOrXpath, double timeWait_Second = 0.0);
    int CheckExistElements(double timeOut,const QStringList &lstCssSelectors);
    QString GetAttributeValue(QString cssSelectorsOrXpath, QString attributeName);
    bool CheckChromeClose();
    bool findAndClick(double timeWait_Second, int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    int sendKeysWithSpeed(int tocDo, int typeAttribute, QString attributeValue, QString content, double timeDelay_Second, bool isClick = true, double timeDelayAfterClick = 0.1);
    int click(int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0, int times = 1);
    int sendEnter(int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    int sendKeys(int typeAttribute, QString attributeValue, QString content, bool isClick = true, double timeDelayAfterClick = 0.1);
    int ClickJs(int timeOut = 0, const QStringList &lstCssSelectors = QStringList());
    bool ClickJs(QString cssSelectorsOrXpath);
    int CountElement(QString querySelector);
    int ClickWithAction(int typeAttribute, QString attributeValue, int index = 0, int subTypeAttribute = 0, QString subAttributeValue = "", int subIndex = 0);
    int sendEnter(QString cssSelectorsOrXpath);
    int GetFbWeb(QString url = "");
    int ScreenCapture(QString imagePath, QString fileName);
    QString GetUid();
    QString GetCookie(QString domain = "facebook");
    int ClickWithAction(QString cssSelectorsOrXpath);
    bool click(QString cssSelectorsOrXpath);
    int GotoURLIfNotExist(QString url);
    int AddCookieIntoChrome(QString cookie, QString domain = ".facebook.com");
    int Refresh();
private:
    const QString background_js =  "\r\n            function callbackFn(details)\r\n            {\r\n\t            return {\r\n\t\t            {Auth}\r\n\t            };\r\n            }\r\n            chrome.webRequest.onAuthRequired.addListener(\r\n\t            callbackFn,\r\n\t            { urls:[\"<all_urls>\"] },\r\n                ['blocking']\r\n            );";
    const QString manifest_json = "\r\n            {\r\n                \"version\": \"1.0.0\",\r\n                \"manifest_version\": 2,\r\n                \"name\": \"Chrome Proxy\",\r\n                \"permissions\": [\r\n                    \"proxy\",\r\n                    \"tabs\",\r\n                    \"unlimitedStorage\",\r\n                    \"storage\",\r\n                    \"<all_urls>\",\r\n                    \"webRequest\",\r\n                    \"webRequestBlocking\"\r\n                ],\r\n                \"background\": {\r\n                    \"scripts\": [\"background.js\"]\r\n\t            },\r\n                \"minimum_chrome_version\":\"22.0.0\"\r\n            }";
    int width;
    int height;
    QString url = "";
    ApiHandler*api;
};

#endif // CHROME_H
