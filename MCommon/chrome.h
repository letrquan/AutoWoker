#ifndef CHROME_H
#define CHROME_H
#include <QString>
#include <QPoint>
#include "../maxcare/Enum/StatusChromeAccount.h"
#include "qdir.h"
#include "qprocess.h"
#include "../API/apihandler.h"
#include <QException>
#include <QRandomGenerator>
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
    QString A9015F2E();
    QString GetCookie(QString domain = "facebook");
    int ClickWithAction(QString cssSelectorsOrXpath);
    bool click(QString cssSelectorsOrXpath);
    int GotoURLIfNotExist(QString url);
    int AddCookieIntoChrome(QString cookie, QString domain = ".facebook.com");
    int Refresh();
    void AcceptCookie();
    QString method_113();
    QString method_112(QString string_10, QString string_11, QString string_12, QString string_13);
    bool SendKeysWithSpeedNew(QString elementSelector, QString text, double speed, bool click_before = true, double click_delay = 0.1);
    bool Clear(QString elementSelector);
    int ScrollSmoothv2(QString jsPath);
    QString method_110(QString string_10);
    QString ConvertCssSelectorToJSDom(const QString& cssSelectorsOrXpath);
    QString GetDomainFb(const QString& url);
    int SetFbLanguage(const QString& language = "en_US");
    QString RequestGet(QString url, QString currentUrl = "");
    QString checkExistElements(double timeOut, const QStringList& lstCssSelectors);
    bool SendKeysIWebElement(QString csselectorOrXPath, QString keys);
    int SendKeys(QString cssSelectorsOrXpath, QString content, bool isSpinText = true);
    bool switch_to_alert_accept();
    QList<QString> method_76();
    QString method_72(QString B686CD07, QString DF35EF25);
    void method_75();
    bool ClearText();
    int ClearText(int typeAttribute, QString attributeValue);
    QString CheckExistElementsString(double timeOut,const QStringList &lstCssSelectors);
    void SetSize(int width = 500, int height = 700);
    QPoint GetSize();
    void ClosePopup();
    void DelayRandom(int timeFrom, int timeTo);
    int SendKeysv2(int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex, QString content, bool isClick = true, double timeDelayAfterClick = 0.1);
    void DelayThaoTacNho(int timeAdd = 0);
    int scrollSmooth(int distance);
    bool GotoBackPage();
    QString GetFbdtsg();
    int CheckExistElementv2(QString JSPath, double timeWait_Second = 0.0);
    int ScrollSmoothIfNotExistOnScreen(QString JSpath);
    QString ConvertFbUrl(QString url, QString currentUrl = "");
    QString GetCssSelector(QString querySelector, QString attributeName, QString attributeValue);
    int CheckExistElementOnScreen(QString JSpath, int timeOut = 0);
    int WaitForSearchElement(QString querySelector, int typeSearch = 0, double timeWait_Second = 0.0);
    QString RequestPost(QString url, QString data, QString contentType = "application/x-www-form-urlencoded", QString currentUrl = "");
    static void ExportError(Chrome* chrome, const QException& ex, const QString& error = "") {
        try {
            if (error != "chrome.Open()") {
                return;
            }

            QDir dir;
            if (!dir.exists("log")) {
                dir.mkdir("log");
            }
            if (!dir.exists("log/html")) {
                dir.mkdir("log/html");
            }
            if (!dir.exists("log/images")) {
                dir.mkdir("log/images");
            }

            QDateTime now = QDateTime::currentDateTime();
            QString text = QString("%1_%2_%3_%4_%5_%6_%7")
                               .arg(now.date().day())
                               .arg(now.date().month())
                               .arg(now.date().year())
                               .arg(now.time().hour())
                               .arg(now.time().minute())
                               .arg(now.time().second())
                               .arg(QRandomGenerator::global()->bounded(1000, 10000));

            if (chrome != nullptr) {
                QString contents = chrome->ExecuteScript("var markup = document.documentElement.innerHTML;return markup;");
                chrome->ScreenCapture("log/images/", text);
                QFile file(QString("log/html/%1.html").arg(text));
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(&file);
                    out << contents;
                    file.close();
                }
            }

            QFile logFile("log/log.txt");
            if (logFile.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&logFile);
                out << "-----------------------------------------------------------------------------\n";
                out << "Date: " << now.toString("dd/MM/yyyy HH:mm:ss") << "\n";
                out << "File: " << text << "\n";
                if (!error.isEmpty()) {
                    out << "Error: " << error << "\n";
                }
                out << "\n";

                if (!ex.what()) {
                    out << "Type: " << typeid(ex).name() << "\n";
                    out << "Message: " << ex.what() << "\n";
                    // Note: StackTrace is not directly available in Qt/C++
                    // You might need to implement a custom solution for stack traces
                }
                logFile.close();
            }
        } catch (...) {
            // Handle any exceptions
        }
    }
private:
    const QString background_js =  "\r\n            function callbackFn(details)\r\n            {\r\n\t            return {\r\n\t\t            {Auth}\r\n\t            };\r\n            }\r\n            chrome.webRequest.onAuthRequired.addListener(\r\n\t            callbackFn,\r\n\t            { urls:[\"<all_urls>\"] },\r\n                ['blocking']\r\n            );";
    const QString manifest_json = "\r\n            {\r\n                \"version\": \"1.0.0\",\r\n                \"manifest_version\": 2,\r\n                \"name\": \"Chrome Proxy\",\r\n                \"permissions\": [\r\n                    \"proxy\",\r\n                    \"tabs\",\r\n                    \"unlimitedStorage\",\r\n                    \"storage\",\r\n                    \"<all_urls>\",\r\n                    \"webRequest\",\r\n                    \"webRequestBlocking\"\r\n                ],\r\n                \"background\": {\r\n                    \"scripts\": [\"background.js\"]\r\n\t            },\r\n                \"minimum_chrome_version\":\"22.0.0\"\r\n            }";
    int width;
    int height;
    QString url = "";
    ApiHandler*api;
};

#endif // CHROME_H
