#include "chrome.h"
#include "qdir.h"
#include <QRandomGenerator>
#include "../maxcare/setupfolder.h"
#include "../MCommon/Common.h"
#include "../maxcare/Base.h"
#include "../Utils/Utils.h"
#include "../MCommon/CommonChrome.h"
Chrome::Chrome() {
    indexChrome = 0;
    HideBrowser = false;
    DisableImage = false;
    DisableSound = true;
    Incognito = false;
    UserAgent = "";
    ProfilePath = "";
    Size = *new QPoint(300, 300);
    Size = *new QPoint(Size.x(), Size.y());
    Proxy = "";
    TypeProxy = 0;
    Position = *new QPoint(Position.x(), Position.y());
    App = "";
    AutoPlayVideo = false;
    LinkToOtherBrowser = "";
    PathExtension = "data\\extension";
    IsUseEmulator = false;
    Size_Emulator = *new QPoint(300, 300);
    Status = StatusChromeAccount::Empty;
    IsUsePortable = false;
    PathToPortableZip = "";
    Scale = 1.0;
    api = new ApiHandler();
    api->startApiProcess();
}
bool Chrome::Open(){
    QString create = api->createInstance(indexChrome,DisableImage,UserAgent,ProfilePath,Size, Position,TimeWaitForSearchingElement,TimeWaitForLoadingPage,Proxy,TypeProxy,DisableSound,App,IsUsePortable,PathToPortableZip);
    if(create != "success" && !create.contains("Instance already exists")){
        return false;
    }
    QString open = api->openBrowser(indexChrome);
    if(open != "success"){
        return false;
    }
    return true;
}

int Chrome::ClearText(int typeAttribute, QString attributeValue){
    QString clea = api->ClearText(indexChrome,typeAttribute, attributeValue);
    if(clea.contains("errorHandler") || clea == "Unexpected response format"){
        if(clea.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(clea == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

QString Chrome::method_112(QString string_10, QString string_11, QString string_12, QString string_13)
{
    if (!this->GetUrl().startsWith("https://graph.facebook.com/"))
    {
        this->GotoURL("https://graph.facebook.com/");
    }
    QString text = QString("\n\tasync function RequestGet(url) {\n\t\tvar output = '';\n\t\ttry {\n\t\t\tvar response = await fetch(url);\n\t\t\tif (response.ok) {\n\t\t\t\tvar body = await response.text();\n\t\t\t\treturn body;\n\t\t\t}\n\t\t} catch { }\n\t\treturn output;\n\t};\n\n\tfriend = '{friend}'\n\tpage = '{page}'\n\tads = '{ads}'\n\tfields = ''\n\tif (friend == '')\n\t\tfields += 'friends.limit(0).summary(1),'\n\tif (page == '')\n\t\tfields += 'accounts.limit(0).summary(1),'\n\tif (ads == '')\n\t\tfields += 'adaccounts.limit(2){account_status,adtrust_dsl,currency,min_billing_threshold{amount}},'\n\tif (fields == '')\n\t\treturn ''\n\tfields = fields.slice(0, -1)\n\turl = 'https://graph.facebook.com/v14.0/me?fields='+fields+'&access_token={token}';\n\tc = await RequestGet(url);\n\n\tif (page == '')\n\t\tpage = JSON.parse(c)['accounts']['summary']['total_count']\n\tif (friend == '')\n\t\tfriend = JSON.parse(c)['friends']['summary']['total_count']\n\tif (ads == ''){\n\t\taccount_status = JSON.parse(c)['adaccounts']['data'][0]['account_status'].toString()\n\t\tswitch (account_status) {\n\t\t\tcase '1':\n\t\t\t\tads = 'Live|'\n\t\t\t\tbreak;\n\t\t\tcase '2':\n\t\t\t\tads = 'Die|'\n\t\t\t\tbreak;\n\t\t\tcase '100':\n\t\t\t\tads = 'Pending closed|'\n\t\t\t\tbreak;\n\t\t\tcase '101':\n\t\t\t\tads = 'Closed|'\n\t\t\t\tbreak;\n\t\t\tdefault:\n\t\t\t\tads = 'Unknow|'\n\t\t\t\tbreak;\t\n\t\t}\n\n\t\tcurrency = JSON.parse(c)['adaccounts']['data'][0]['currency']\n\t\tnguong = JSON.parse(c)['adaccounts']['data'][0]['min_billing_threshold']['amount']\n\t\tads += nguong + \" \"+currency\n\t\tads += \"|\"\n\n\t\tadtrust_dsl = JSON.parse(c)['adaccounts']['data'][0]['adtrust_dsl']\n\t\tif (adtrust_dsl == \"-1\")\n\t\t\tads += \"Nolimit\";\n\t\telse\n\t\t\tads += adtrust_dsl + \" \" + currency;\n\t}\n\n\tconst obj = {\n\t\tfriend: friend,\n\t\tpage: page,\n\t\tads: ads\n\t};\n\treturn JSON.stringify(obj)\n\t").replace("{token}", string_10).replace("{friend}", string_11).replace("{page}", string_12)
                      .replace("{ads}", string_13);
    return this->ExecuteScript(text);
}

QString Chrome::A9015F2E()

{
    QString text = "";
    try
    {
        if (!this->GetUrl().startsWith("https://www.facebook.com") || this->GetUrl().contains("https://www.facebook.com/api/graphql"))
        {
            this->GotoURL("https://www.facebook.com/");
        }
        QString text2 = "CheckLocation";
        text = this->ExecuteScript(text2);
    }
    catch(QException)
    {
    }
    return text;
}


QString Chrome::method_110(QString string_10)
{
    if (!GetUrl().startsWith("https://graph.facebook.com/"))
    {
        this->GotoURL("https://graph.facebook.com/");
    }
    QString text = QString("\n\tasync function RequestGet(url) {\n\t\tvar output = '';\n\t\ttry {\n\t\t\tvar response = await fetch(url);\n\t\t\tif (response.ok) {\n\t\t\t\tvar body = await response.text();\n\t\t\t\treturn body;\n\t\t\t}\n\t\t} catch { }\n\t\treturn output;\n\t};\n\n\turl = 'https://graph.facebook.com/v3.0/me/businesses?fields=id&limit=5000&access_token={token}';\n\tc = await RequestGet(url);\n\treturn JSON.parse(c)['data'].length\n\t").replace("{token}", string_10);
    return this->ExecuteScript(text);
}

bool Chrome::GotoURL(QString url){
    QString go = api->gotoUrl(indexChrome,url);
    if(go != "success"){
        return false;
    }
    return true;
}

bool Chrome::DelayTime(double seconds){
    QString de = api->delayTime(indexChrome,seconds);
    if(de != "success"){
        return false;
    }
    return true;
}

QString Chrome::GetPageSource(){
    QString pageSource = api->GetPageSource(indexChrome);
    if(pageSource.contains("errorHandler") || pageSource == "Unexpected response format"){
        return "";
    }else{
        return pageSource;
    }
}
QString Chrome::GetUrl(){
    QString url = api->GetUrl(indexChrome);
    if(url.contains("errorHandler") || url == "Unexpected response format"){
        return "";
    }else{
        return url;
    }
}


int Chrome::Close(){
    QString close = api->close(indexChrome);
    if(close.contains("errorHandler") || close == "Unexpected response format"){
        return -2;
    }else{
        if(close == "true"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::CheckExistElement(QString cssSelectorsOrXpath, double timeWait_Second){
    QString check = api->checkExistElement(indexChrome,cssSelectorsOrXpath,timeWait_Second);
    if(check.contains("errorHandler") || check == "Unexpected response format"){
        if(check.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        return check.toInt();
    }
}

int Chrome::CheckExistElements(double timeOut,const QStringList &lstCssSelectors){
    QString check = api->checkExistElements(indexChrome,timeOut,lstCssSelectors);
    if(check.contains("errorHandler") || check == "Unexpected response format"){
        if(check.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        return check.toInt();
    }
}



QString Chrome::GetAttributeValue(QString cssSelectorsOrXpath, QString attributeName){
    QString value = api->GetAttributeValue(indexChrome,cssSelectorsOrXpath,attributeName);
    if(value.contains("errorHandler") || value == "Unexpected response format"){
        return "";
    }else{
        return value;
    }
}

QString Chrome::ExecuteScript(QString script){
    QString ex = api->executeScript(indexChrome,script);
    if(ex.contains("errorHandler") || ex == "Unexpected response format"){
        return "";
    }else{
        return ex;
    }
}

int Chrome::ScrollSmoothv2(QString jsPath){
    if(CheckChromeClose()){
        return -2;
    }
    try {
        QString excute = ExecuteScript(jsPath + ".scrollIntoView({ behavior: 'smooth', block: 'center'});");
        if(excute.contains("errorHandler") || excute == "Unexpected response format"){
            return 0;
        }else{
            return 1;
        }
    } catch (QException &ex) {
        ExportError(nullptr, ex, "chrome.ScrollSmooth(" + jsPath + ")");
        return 0;
    }
}


bool Chrome::CheckChromeClose(){
    QString ccc = api->checkChromeClose(indexChrome);
    if(ccc.contains("errorHandler") || ccc == "Unexpected response format"){
        return false;
    }else{
        if(ccc == "True"){
            return true;
        }else{
            return false;
        }
    }
}

bool Chrome::findAndClick(double timeWait_Second, int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QString fnc = api->findAndClick(indexChrome,timeWait_Second,typeAttribute,attributeValue,index,subTypeAttribute, subAttributeValue, subIndex);
    if(fnc.contains("errorHandler") || fnc == "Unexpected response format"){
        return false;
    }else{
        if(fnc == "success"){
            return true;
        }else{
            return false;
        }
    }
}

int Chrome::sendKeysWithSpeed(int tocDo, int typeAttribute, QString attributeValue, QString content, double timeDelay_Second, bool isClick, double timeDelayAfterClick){
    QString skws = api->sendKeysWithSpeed(indexChrome,tocDo,typeAttribute,attributeValue,content,timeDelay_Second,isClick,timeDelayAfterClick);
    if(skws.contains("errorHandler") || skws == "Unexpected response format"){
        if(skws.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(skws == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::click(int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex, int times){
    QString cl = api->click(indexChrome,typeAttribute,attributeValue,index,subTypeAttribute,subAttributeValue,subIndex,times);
    if(cl.contains("errorHandler") || cl == "Unexpected response format"){
        if(cl.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(cl == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::sendEnter(int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QString sendenter = api->sendEnter(indexChrome,typeAttribute,attributeValue,index,subTypeAttribute,subAttributeValue,subIndex);
    if(sendenter.contains("errorHandler") || sendenter == "Unexpected response format"){
        if(sendenter.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(sendenter == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

bool Chrome::SendKeysIWebElement(QString csselectorOrXPath, QString keys){
    return api->SendKeys(indexChrome,csselectorOrXPath,keys);
}

int Chrome::SendKeys(QString cssSelectorsOrXpath, QString content, bool isSpinText){
    bool flag = false;
    if (CheckChromeClose())
    {
        return -2;
    }
    try {
        if (isSpinText)
        {
            content = Common::SpinText(content);
        }
        if (Common::CheckStringIsContainIcon(content))
        {
            click(cssSelectorsOrXpath);
            content = content.replace("\r\n", "*rr*nn").replace("\n", "*rr*nn");
            content = content.replace("*rr*nn", "\\r\\n").replace("\"", "\\\"");
            ExecuteScript(ConvertCssSelectorToJSDom(cssSelectorsOrXpath) + ".value=\"" + content + "\"");
            SendKeysIWebElement(cssSelectorsOrXpath," ");
        }else
        {
            SendKeysIWebElement(cssSelectorsOrXpath,content);
            if (content.contains(" "))
            {
                SendKeysIWebElement(cssSelectorsOrXpath," ");
            }
        }
        flag = true;
    } catch (...) {
    }
}

QString Chrome::ConvertCssSelectorToJSDom(const QString& cssSelectorsOrXpath)
{
    if (cssSelectorsOrXpath.startsWith("/") || cssSelectorsOrXpath.startsWith("(/"))
    {
        QString escapedXpath = cssSelectorsOrXpath;
        escapedXpath.replace("'", "\\'");
        return QString("document.evaluate('%1', document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue")
            .arg(escapedXpath);
    }

    QString text, text2;
    int value = 0, num = 0;

    QStringList parts = cssSelectorsOrXpath.split('|');

    switch (parts.size())
    {
    case 1:
        text = parts[0].trimmed();
        break;
    case 2:
        text = parts[0].trimmed();
        value = parts[1].trimmed().toInt();
        break;
    case 3:
        text = parts[0].trimmed();
        value = parts[1].trimmed().toInt();
        text2 = parts[2].trimmed();
        break;
    case 4:
        text = parts[0].trimmed();
        value = parts[1].trimmed().toInt();
        text2 = parts[2].trimmed();
        num = parts[3].trimmed().toInt();
        break;
    }

    text.replace("'", "\\'");
    text2.replace("'", "\\'");

    if (num != 0)
    {
        return QString("document.querySelectorAll('%1')[%2].querySelectorAll('%3')[%4]")
            .arg(text).arg(value).arg(text2).arg(num);
    }

    return QString("document.querySelectorAll('%1')[%2]")
        .arg(text).arg(value);
}

QList<QString> Chrome::method_76() {
    QList<QString> list;

    if (!GetUrl().startsWith("https://www.facebook.com")) {
        GotoURL("https://www.facebook.com/api/graphql");
    }

    QString text = "GetPagePro5";
    QString text2 = ExecuteScript(text);

    QStringList stringList = text2.split('|', Qt::SkipEmptyParts);
    list = stringList.toList();

    return list;
}

bool Chrome::ClearText(){
    QString response = api->ClearText(indexChrome);
    if(response == "success"){
        return true;
    }else{
        return false;
    }
}

void Chrome::SetSize(int width, int height){
    QString resposne = api->SetSize(indexChrome ,width, height);
}

QString Chrome::method_72(QString B686CD07, QString DF35EF25)
{
    QString text = "";
    B686CD07 = B686CD07.toLower(); // Assuming D71F7139() is toLower()

    if (B686CD07.isEmpty())
    {
        // Simulating LINQ queries with Qt
        QStringList hoVN = SetupFolder::GetListHoVN();
        QStringList tenDemVN = SetupFolder::GetListTenDemVN();
        QStringList tenVN = SetupFolder::GetListTenVN();

        QString text2 = hoVN[QRandomGenerator::global()->bounded(hoVN.size())];
        QString text3 = tenDemVN[QRandomGenerator::global()->bounded(tenDemVN.size())].trimmed();
        QString text4 = tenVN[QRandomGenerator::global()->bounded(tenVN.size())];

        B686CD07 = text2+ (text3.isEmpty() ? " " : " " + text3 + " ")+text4;
    }

    if (DF35EF25 == "")
    {
        DF35EF25 = Common::RandomString(1, "a_A");
    }

    if (!Base::isLam || !Utils::isNumber(DF35EF25))
    {
        QString text5 = "[aria-label^=\"Category\"] input";
        QString text6 = "[role=\"listbox\"] [role=\"option\"]";
        QString text7 = "[aria-label=\"Create Page\"]";
        QString string_ = text7 + " [role=\"progressbar\"]";
        QString tex10 = "[aria-label=\"Next\"]";
        QString tex11 = "[aria-label=\"Skip\"]";
        QString tex12 = "[aria-label=\"Close\"]";
        QString tex13 = "[aria-label=\"Done\"]";

        SetFbLanguage();
        SetSize();
        GotoURL("https://www.facebook.com/pages/?category=your_pages&ref=bookmarks");
        DelayTime(2.0);

        QStringList second = method_76();
        qint64 startTime = QDateTime::currentMSecsSinceEpoch();
        int num = 60;
        QStringList newPages = method_76();
        while (true)
        {
            QString text8 = checkExistElements(0.0, {"[aria-label^=\"Page name\"] input", "[href^=\"/pages/creation/\"]"});
            QString text88 = checkExistElements(0.0, {tex10, tex11, tex13});
            QString text9 = text8;
            QString text10 = text9;
            if (!(text10 == "[href^=\"/pages/creation/\"]"))
            {
                //ClickWithAction(text8);
                //}
                if (!(text10 == "[aria-label^=\"Page name\"] input"))
                {
                    method_75();
                }
                else
                {
                    ClickWithAction(text8);
                    sendEnter(text8);
                    SendKeys(text8, B686CD07);
                    DelayTime(2.0);
                    ClickWithAction(text5);
                    SendKeys(text5, DF35EF25);
                    DelayTime(2.0);
                    if (CheckExistElement(text6, 10.0) == 0)
                    {
                        ClearText();
                    }
                    else
                    {
                        ClickWithAction(text6);
                        DelayTime(2.0);
                        ClickWithAction(text7);
                        DelayTime(10.0);
                        SetSize(1700,800);
                        DelayTime(5.0);
                        ClickWithAction(tex10);
                        DelayTime(2.0);
                        ClickWithAction(tex10);
                        DelayTime(2.0);
                        ClickWithAction(tex11);
                        DelayTime(2.0);
                        ClickWithAction(tex10);
                        DelayTime(2.0);
                        ClickWithAction(tex13);
                        DelayTime(10.0);
                        if (WaitForSearchElement(string_, 1, 30.0) != 0)
                        {
                            //text = method_76().Except(second).FirstOrDefault();
                            //if (!string.IsNullOrEmpty(text))
                            //{
                            //     Refresh();
                            //	try
                            //	{
                            //    chrome.SwitchTo().Alert().Accept();
                            //	}
                            //	catch
                            //	{
                            //	}
                            //}
                            break;
                        }
                    }
                }
            }else{
                ClickWithAction(text8);
            }

            if (QDateTime::currentMSecsSinceEpoch() - startTime > num * 1000)
            {
                goto IL_313;
            }

            DelayTime(2.0);
        }
        text = Utils::findFirstDifference(method_76(),second);
        if (!(text.isEmpty() || text.isNull()))
        {
            Refresh();
            try
            {
                switch_to_alert_accept();
            }
            catch(...)
            {
            }
        }

    IL_313:
        SetSize(width,height);
    }

    return text;
}

bool Chrome::GotoBackPage(){
    auto res = api->GotoBackPage(indexChrome);
    if(res == "success"){
        return true;
    }else{
        return false;
    }
}

int Chrome::WaitForSearchElement(QString querySelector, int typeSearch, double timeWait_Second)
{
    bool flag = true;
    if (!CheckChromeClose())
    {
        return -2;
    }
    try
    {
        int tickCount = QDateTime::currentSecsSinceEpoch();
        if (typeSearch == 0)
        {
            while (ExecuteScript("return document.querySelectorAll('" + querySelector.replace("'", "\\'") + "').length+''") == "0")
            {
                if ((double)(QDateTime::currentSecsSinceEpoch() - tickCount) > timeWait_Second)
                {
                    flag = false;
                    break;
                }
                QThread::sleep(1);
            }
        }
        else
        {
            while (ExecuteScript("return document.querySelectorAll('" + querySelector.replace("'", "\\'") + "').length+''") != "0")
            {
                if ((double)(QDateTime::currentSecsSinceEpoch() - tickCount) > timeWait_Second)
                {
                    flag = false;
                    break;
                }
                QThread::sleep(1);
            }
        }
    }
    catch (QException ex)
    {
        flag = false;
        ExportError(nullptr, ex, "chrome.WaitForSearchElement("+querySelector+","+QString::number(typeSearch)+","+QString::number(timeWait_Second)+")");
    }
    if (!flag)
    {
        return 0;
    }
    return 1;
}

int Chrome::ScrollSmoothIfNotExistOnScreen(QString JSpath)
{
    if (!CheckChromeClose())
    {
        return -2;
    }
    try
    {
        if (CheckExistElementOnScreen(JSpath) != 0)
        {
            ExecuteScript(JSpath + ".scrollIntoView({ behavior: 'smooth', block: 'center'});");
            return 1;
        }
    }
    catch (QException ex)
    {
        ExportError(nullptr, ex, "chrome.ScrollSmoothIfNotExistOnScreen(" + JSpath + ")");
    }
    return 0;
}

QString Chrome::GetFbdtsg()
{
    QString text = "";
    try
    {
        QString input = RequestGet("https://m.facebook.com/help");
        text = QRegularExpression("fb_dtsg\" value=\"(.*?)\"").match(input).captured(1);
        if (text == "")
        {
            text = QRegularExpression(Common::Base64Decode("ZHRzZyI6eyJ0b2tlbiI6IiguKj8pIg==")).match(input).captured(1);
            return text;
        }
        return text;
    }
    catch(QException)
    {
        return text;
    }
}

QString Chrome::ConvertFbUrl(QString url, QString currentUrl)
{
    if(CheckChromeClose()){
        return "";
    }
    if (currentUrl == "")
    {
        currentUrl = GetUrl();
    }
    QString domainFb = GetDomainFb(currentUrl);
    QString domainFb2 = GetDomainFb(url);
    return url.replace(domainFb2, domainFb);
}

int Chrome::CheckExistElementv2(QString JSPath, double timeWait_Second)
{
    bool flag = true;
    if (CheckChromeClose())
    {
        return -2;
    }
    try
    {
        QElapsedTimer timer;
        timer.start();
        while (ExecuteScript("return " + JSPath + ".length+''") == "0")
        {
            if (timer.elapsed() > timeWait_Second * 1000)
            {
                flag = false;
                break;
            }
            QThread::sleep(1);
        }
    }
    catch (QException ex)
    {
        flag = false;
        ExportError(nullptr, ex, QString("chrome.CheckExistElement(%1,%2)")
                                     .arg(JSPath)
                                     .arg(timeWait_Second));
    }
    if(ExecuteScript("return " + JSPath + ".length+''") == ""){
        flag = false;
    }
    if (!flag)
    {
        return 0;
    }
    return 1;
}


void Chrome::method_75()
{
    int text = CheckExistElements(0.0, QStringList { "[role=\"dialog\"] [aria-label=\"Not Now\"]", "[role=\"dialog\"] [aria-label=\"Use Page\"]", "[role=\"dialog\"] [aria-label=\"Close\"]" });
    switch (text) {
    case 1:
        ClickJs("[role=\"dialog\"] [aria-label=\"Not Now\"]");
        break;
    case 2:
        ClickJs("[role=\"dialog\"] [aria-label=\"Use Page\"]");
    case 3:
        ClickJs("[role=\"dialog\"] [aria-label=\"Close\"]");
    default:
        break;
    }
}

QString Chrome::checkExistElements(double timeOut, const QStringList& lstCssSelectors)
{
    if (CheckChromeClose())
    {
        return "-2";
    }

    try
    {
        int num = 0;
        QElapsedTimer timer;
        timer.start();
        while (true)
        {
            QString script = "var arr='" + lstCssSelectors.join("|") + "'.split('|');"
                                                                       "var output=0;"
                                                                       "for(i=0;i<arr.length;i++){"
                                                                       "  if (document.querySelectorAll(arr[i]).length > 0) {"
                                                                       "    output = i + 1;"
                                                                       "    break;"
                                                                       "  }"
                                                                       "}"
                                                                       "return (output + '');";

            num = ExecuteScript(script).toInt();

            if (num != 0)
            {
                return lstCssSelectors[num - 1];
            }

            if (timer.elapsed() > timeOut * 1000)
            {
                break;
            }

            QThread::sleep(1);
        }
    }
    catch (const std::exception&)
    {
        // Empty catch block, as in the original C# code
    }

    return "";
}

QString Chrome::method_113()
{
    if (!GetUrl().startsWith("https://www.facebook.com"))
    {
        GotoURL("https://www.facebook.com/api/graphql/");
    }
    QString text = "\n\tasync function RequestGet(url) {\n\t\tvar output = '';\n\t\ttry {\n\t\t\tvar response = await fetch(url);\n\t\t\tif (response.ok) {\n\t\t\t\tvar body = await response.text();\n\t\t\t\treturn body;\n\t\t\t}\n\t\t} catch { }\n\t\treturn output;\n\t};\n\n\tvar html = await RequestGet('https://www.facebook.com/dating/get-started/');\n\tlet check = '';\n\tif (html.includes('download__section-heading')) check = 'Yes';\n\telse if (html.includes('unavailable__section-container')) check = 'No';\n\treturn check";
    return ExecuteScript(text);
}

int Chrome::SetFbLanguage(const QString& language)
{
    QString domainFb = GetDomainFb(GetUrl());
    QString input = RequestGet(domainFb + "/language");

    QRegularExpression langRegex("<html.*?lang=\"(.*?)\".*?>");
    QRegularExpressionMatch match = langRegex.match(input);
    QString value = match.captured(1).split('_')[0].split('-')[0];

    if (language.startsWith(value))
    {
        return 2;
    }

    QString url = GetUrl();
    int num = CommonChrome::CheckTypeWebFacebookFromUrl(url);
    bool flag = false;
    QString uid = GetUid();

    QRegularExpression dtsgRegex("\\[\"DTSGInitData\",\\[\\],{\"token\":\"(.*?)\"");
    match = dtsgRegex.match(input);
    QString value2 = match.captured(1);

    if (value2.isEmpty())
    {
        QRegularExpression dtsgRegex2("fb_dtsg\" value=\"(.*?)\"");
        match = dtsgRegex2.match(input);
        value2 = match.captured(1);
    }

    if (value2.isEmpty())
    {
        QRegularExpression dtsgRegex3("\"dtsg\":{\"token\":\"(.*?)\"");
        match = dtsgRegex3.match(input);
        value2 = match.captured(1);
    }

    switch (num)
    {
    case 3:
    {
        QString data3 = "fb_dtsg=" + value2 + "&jazoest=";
        input = RequestPost("https://mbasic.facebook.com/intl/save_locale/?loc=" + language + "&href=" + url + "ls_ref=mobile_suggested_locale_selector", data3);
        flag = true;
        break;
    }
    case 1:
    {
        QString data2 = "av=" + uid + "&__user=" + uid + "&__a=1&__dyn=7AzHxqU5a5Q1ryUqxenFw9uu2i5U4e0ykdwSwAyUco2qwJxS1NwJwpUe8hw6vwb-q7oc81xoswaq221FwgolzUO0n2US2G5Usw9m1YwBgK7o884y0Mo5W3S1lwlE-U2exi4UaEW2G1NxGm2SUbElxm3y11xfxm16wUws9ovUaU3VBwJCwLyES0Io5d08O321bwzwTwNwLwFg667EW26&__csr=gbJgx9FrmKhGhebly4FeiuGLgBtvgV5Qp3W8fyQmWGWCyqQqmWByVWBCDgN4QKm4oCbzWBKFqUGmbgC2qczo-eDy8OeGm48S2yjwIiAUbFU4-688WDwnEeE-mm2q6U5q489U2qAyocpA1awCwsU6um784a2y1iBwfe0Xo3ewcS3C4UcEeUkwd21xwb-0TU0bhE03kqw1ra00D3U1cE0qwy80nBw&__req=s&__hs=19341.HYP%3Acomet_plat_default_pkg.2.1.0.2.1&dpr=1&__ccg=EXCELLENT&__rev=1006744097&__s=6wdrff%3Av1ddfc%3Aivypow&__hsi=7177392587978281303&__comet_req=1&fb_dtsg=" + value2 + "&jazoest=25561&lsd=28LQ-iX8-krHlH1-04tYFF&__spin_r=1006744097&__spin_b=trunk&__spin_t=1671116936&fb_api_caller_class=RelayModern&fb_api_req_friendly_name=useCometLocaleSelectorLanguageChangeMutation&variables=%7B%22locale%22%3A%22" + language + "%22%2C%22referrer%22%3A%22WWW_ACCOUNT_SETTINGS%22%2C%22fallback_locale%22%3Anull%7D&server_timestamps=true&doc_id=5299223003435639&fb_api_analytics_tags=%5B%22qpl_active_flow_ids%3D30605361%22%5D";
        input = RequestPost("https://www.facebook.com/api/graphql/", data2);
        QRegularExpression successRegex("{\"success\":(.*?)}");
        match = successRegex.match(input);
        flag = match.captured(1) == "true";
        break;
    }
    default:
    {
        QString data = "loc=" + language + "&ref=m_touch_locale_selector&should_redirect=false&fb_dtsg=" + value2 + "&jazoest=22683&lsd=&__dyn=&__csr=&__req=m&__a=&__user=" + uid;
        input = RequestPost("https://m.facebook.com/intl/ajax/save_locale", data);
        QRegularExpression successRegex("{\"success\":(.*?)}");
        match = successRegex.match(input);
        flag = match.captured(1) == "true";
        break;
    }
    }

    input = RequestGet(domainFb + "/help");
    match = langRegex.match(input);
    value = match.captured(1).split('_')[0].split('-')[0];

    if (!language.startsWith(value))
    {
        GotoURL("https://mbasic.facebook.com/language");
        ClickJs("form[action*=\"loc=" + language + "\"] [type=\"submit\"]");
        flag = true;
    }

    if (!flag)
    {
        return 0;
    }
    return 1;
}

QString Chrome::GetDomainFb(const QString& url)
{
    QRegularExpression regex("https://(.*?)facebook\\.com");
    QRegularExpressionMatch match = regex.match(url);
    return match.captured(0);
}

QString Chrome::RequestGet(QString url, QString currentUrl)
{
    try
    {
        if (currentUrl == "")
        {
            currentUrl = GetUrl();
        }
        if (GetDomainFb(currentUrl) != GetDomainFb(url))
        {
            GotoURL(GetDomainFb(url));
            ExecuteScript("document.querySelector('body').innerHTML='AUTOWORKER'; document.querySelector('body').style = 'text-align: center; background-color:#fff'");
        }
        return ExecuteScript("async function RequestGet() { var output = ''; try { var response = await fetch('" + url + "'); if (response.ok) { var body = await response.text(); return body; } } catch {} return output; }; var c = await RequestGet(); return c;");
    }
    catch(...)
    {
    }
    return "";
}

QString Chrome::RequestPost(QString url, QString data, QString contentType, QString currentUrl)
{
    try
    {
        if (currentUrl == "")
        {
            currentUrl = GetUrl();
        }
        if (GetDomainFb(currentUrl) != GetDomainFb(url))
        {
            GotoURL(GetDomainFb(url));
            ExecuteScript("document.querySelector('body').innerHTML='AUTOWORKER'; document.querySelector('body').style = 'text-align: center; background-color:#fff'");
        }
        data = data.replace("\n", "\\n").replace("\"", "\\\"");
        return ExecuteScript("async function RequestPost() { var output = ''; try { var response = await fetch('" + url + "', { method: 'POST', body: '" + data + "', headers: { 'Content-Type': '" + contentType + "' } }); if (response.ok) { var body = await response.text(); return body; } } catch {} return output; }; var c = await RequestPost(); return c;");
    }
    catch(...)
    {
    }
    return "";
}


int Chrome::sendKeys(int typeAttribute, QString attributeValue, QString content, bool isClick, double timeDelayAfterClick){
    QString sendkey = api->sendKeys(indexChrome,typeAttribute,attributeValue,content,isClick,timeDelayAfterClick);
    if(sendkey.contains("errorHandler") || sendkey == "Unexpected response format"){
        if(sendkey.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(sendkey == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::ClickJs(int timeOut, const QStringList &cssSelectors){
    QString click = api->clickJs(indexChrome, timeOut, cssSelectors);
    if(click.contains("errorHandler") || click == "Unexpected response format"){
        if(click.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(click == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

bool Chrome::ClickJs(QString cssSelectorsOrXpath){
    QString click = api->clickJs(indexChrome,cssSelectorsOrXpath);
    if(click.contains("errorHandler") || click == "Unexpected response format"){
        return false;
    }else{
        return true;
    }
}

int Chrome::CountElement(QString querySelector){
    QString count = api->CountElement(indexChrome, querySelector);
    if(count.contains("errorHandler") || count == "Unexpected response format"){
        return -2;
    }else{
        return count.toInt();
    }
}

bool Chrome::SendKeysWithSpeedNew(QString elementSelector, QString text, double speed, bool click_before, double click_delay){
    bool send = api->sendKeysWithSpeed(indexChrome,elementSelector,text,speed,click_before,click_delay);
    return send;
}


int Chrome::ClickWithAction(int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QString clickwa = api->ClickWithAction(indexChrome,typeAttribute,attributeValue,index,subTypeAttribute,subAttributeValue,subIndex);
    if(clickwa.contains("errorHandler") || clickwa == "Unexpected response format"){
        if(clickwa.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(clickwa == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::sendEnter(QString cssSelectorsOrXpath){
    QString sendEnter = api->sendEnter(indexChrome,cssSelectorsOrXpath);
    if(sendEnter.contains("errorHandler") || sendEnter == "Unexpected response format"){
        if(sendEnter.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(sendEnter == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::GetFbWeb(QString url)
{
    if (url.isEmpty())
    {
        url = GetUrl();
    }
    int result = 0;
    if (url.startsWith("https://www.facebook") || url.startsWith("https://facebook") || url.startsWith("https://web.facebook"))
    {
        result = 1;
    }
    else if (url.startsWith("https://m.facebook") || url.startsWith("https://d.facebook") || url.startsWith("https://mobile.facebook"))
    {
        result = 2;
    }
    else if (url.startsWith("https://mbasic.facebook"))
    {
        result = 3;
    }
    return result;
}

int Chrome::ScreenCapture(QString imagePath, QString fileName){
    QString screencap = api->ScreenCapture(indexChrome,imagePath,fileName);
    if(screencap.contains("errorHandler") || screencap == "Unexpected response format"){
        if(screencap.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(screencap == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

QString Chrome::GetUid(){
    QString uid = api->GetUid(indexChrome);
    if(uid.contains("errorHandler") || uid == "Unexpected response format"){
        return "";
    }else{
        return uid;
    }
}

QString Chrome::GetCookie(QString domain){
    QString cookie = api->GetCookie(indexChrome,domain);
    if(cookie.contains("errorHandler") || cookie == "Unexpected response format"){
        return "";
    }else{
        return cookie;
    }
}

int Chrome::ClickWithAction(QString cssSelectorsOrXpath){
    QString click = api->ClickWithAction(indexChrome,cssSelectorsOrXpath);
    if(click.contains("errorHandler") || click == "Unexpected response format"){
        if(click.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(click == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

bool Chrome::click(QString cssSelectorsOrXpath){
    QString click = api->click(indexChrome,cssSelectorsOrXpath);
    if(click.contains("errorHandler") || click == "Unexpected response format"){
        return false;
    }else{
        if(click == "success"){
            return true;
        }else{
            return false;
        }
    }
}

int Chrome::GotoURLIfNotExist(QString url){
    QString click = api->GotoURLIfNotExist(indexChrome,url);
    if(click.contains("errorHandler") || click == "Unexpected response format"){
        if(click.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(click == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::AddCookieIntoChrome(QString cookie, QString domain){
    QString add = api->AddCookieIntoChrome(indexChrome,cookie,domain);
    if(add.contains("errorHandler") || add == "Unexpected response format"){
        if(add.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(add == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::Refresh(){
    QString ref = api->Refresh(indexChrome);
    if(ref.contains("errorHandler") || ref == "Unexpected response format"){
        if(ref.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(ref == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

int Chrome::gotoLogin(int typeWeb)
{
    bool flag = false;
    try
    {
        switch (typeWeb)
        {
        case 1:
            GotoURL("https://www.facebook.com/login");
            break;
        case 2:
            GotoURL("https://m.facebook.com/login");
            break;
        case 3:
            GotoURL("https://mbasic.facebook.com/login");
            break;
        }
        flag = true;
        DelayTime(1.0);
    }
    catch (...)
    {
    }
    if (!flag)
    {
        return 0;
    }
    return 1;
}

void Chrome::AcceptCookie()
{
    for (int i = 0; i < 4; ++i)
    {
        if (GetFbWeb() == 1)
        {
            if (ClickJs("[role=\"dialog\"] [aria-label=\"Close\"],[role=\"dialog\"] [aria-label][role=\"button\"]:has(svg)"))
            {
                DelayTime(2.0);
            }
            break;
        }
        if (CheckExistElement("[data-cookiebanner=\"accept_button\"]") == 1)
        {
            ExecuteScript("document.querySelector('[data-cookiebanner=\"accept_button\"]').click()");
            continue;
        }
        QString url = GetUrl();
        if (url.startsWith("https://m.facebook.com/si/actor_experience/actor_gateway") &&
            CheckExistElement("[data-nt=\"NT:IMAGE\"]", 15000) == 1)
        {
            ExecuteScript("document.querySelector('[data-nt=\"NT:IMAGE\"]').click()");
            DelayTime(2.0);
            continue;
        }
        if (url.contains("facebook.com/legal_consent"))
        {
            ClickJs("button[type=\"submit\"]");
            DelayTime(1.0);
            ClickJs("button[type=\"submit\"]:last-child");
            DelayTime(1.0);
            ClickJs("button[type=\"submit\"]");
            DelayTime(1.0);
            ClickJs("#consent-page-container button[type=\"submit\"]:last-child");
            DelayTime(1.0);
            continue;
        }
        if (url.contains("facebook.com/privacy/consent_framework/prompt/"))
        {
            if (CheckExistElement("[type=\"checkbox\"][name=\"personal_data_toggle\"]") == 1)
            {
                ExecuteScript("document.querySelector('[type=\"checkbox\"][name=\"personal_data_toggle\"]').checked=true;");
            }
            if (CheckExistElement("[type=\"checkbox\"][name=\"data_shared_3pd_toggle\"]") == 1)
            {
                ExecuteScript("document.querySelector('[type=\"checkbox\"][name=\"data_shared_3pd_toggle\"]').checked=true;");
            }
            if (CheckExistElement("[type=\"checkbox\"][name=\"cross_border_data_transfer_toggle\"]") == 1)
            {
                ExecuteScript("document.querySelector('[type=\"checkbox\"][name=\"cross_border_data_transfer_toggle\"]').checked=true;");
            }
            if (CheckExistElement("[type=\"checkbox\"][name=\"location_info_toggle\"]") == 1)
            {
                ExecuteScript("document.querySelector('[type=\"checkbox\"][name=\"location_info_toggle\"]').checked=true;");
            }
            ClickJs("button[name=\"primary_consent_button\"]");
            DelayTime(2);
            continue;
        }
        break;
    }
}

bool Chrome::Clear(QString elementSelector){
    bool clear = api->Clear(indexChrome,elementSelector);
    return clear;
}

QString Chrome::GetCssSelector(QString querySelector, QString attributeName, QString attributeValue)
{
    QString result = "";
    if (!CheckChromeClose())
    {
        return "-2";
    }
    try
    {
        result = ExecuteScript("function GetSelector(el){let path=[],parent;while(parent=el.parentNode){path.unshift(`${el.tagName}:nth-child(${[].indexOf.call(parent.children, el)+1})`);el=parent}return `${path.join('>')}`.toLowerCase()}; function GetCssSelector(selector, attribute, value){var c = document.querySelectorAll(selector); for (i = 0; i < c.length; i++) { if (c[i].getAttribute(attribute)!=null && c[i].getAttribute(attribute).includes(value)) { return GetSelector(c[i])} }; return '';}; return GetCssSelector('" + querySelector + "','" + attributeName + "','" + attributeValue + "')");
        return result;
    }
    catch (QException ex)
    {
        ExportError(nullptr, ex, "chrome.GetCssSelector("+querySelector+","+attributeName+","+attributeValue+")");
        return result;
    }
}



int Chrome::CheckExistElementOnScreen(QString JSpath, int timeOut)
{
    int num = 0;
    QElapsedTimer timer;
    timer.start();
    do
    {
        if (CheckChromeClose())
        {
            return -2;
        }
        try
        {
            num = ExecuteScript("var check='';x=" + JSpath + ";if(x.getBoundingClientRect().top<=0) check='-1'; else if(x.getBoundingClientRect().top+x.getBoundingClientRect().height>window.innerHeight) check='1'; else check='0'; return check;").toInt();
            if (num == 0)
            {
                return num;
            }
        }
        catch (QException)
        {
        }
        if (timeOut == 0)
        {
            break;
        }
        DelayTime(1.0);
    }
    while (timer.elapsed() < timeOut * 1000);
    return num;
}

QString Chrome::CheckExistElementsString(double timeOut,const QStringList &lstCssSelectors){
    QString check = api->checkExistElements(indexChrome,timeOut,lstCssSelectors);
    if(check.contains("errorHandler") || check == "Unexpected response format"){
        if(check.contains("Chrome is closed")){
            return "";
        }else{
            return "";
        }
    }else{
        return lstCssSelectors[check.toInt()];
    }
}

bool Chrome::switch_to_alert_accept(){
    bool sw = api->switch_to_alert_accept(indexChrome);
    return sw;
}

QPoint Chrome::GetSize(){
    QVariant res = api->GetSize(indexChrome);
    if(res.canConvert<QPoint>()){
        return res.toPoint();
    }else{
        qDebug() << res.toString();
        return QPoint(0,0);
    }
}

int Chrome::scrollSmooth(int distance)
{
    if (CheckChromeClose())
    {
        return -2;
    }

    try
    {
        int initialPosition = ExecuteScript("return document.querySelector('html').getBoundingClientRect().y+''").toInt();

        ExecuteScript(QString("window.scrollBy({ top: %1, behavior: 'smooth'});").arg(distance));

        DelayTime(0.1);

        int newPosition = ExecuteScript("return document.querySelector('html').getBoundingClientRect().y+''").toInt();

        if (initialPosition == newPosition)
        {
            return 2;
        }
    }
    catch (const QException& ex)
    {
        ExportError(nullptr, ex, QString("chrome.scrollSmooth(%1)").arg(distance));
    }

    return 1;
}

int Chrome::SendKeysv2(int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex, QString content, bool isClick, double timeDelayAfterClick){
    auto res = api->SendKeysv2(indexChrome,typeAttribute,attributeValue,index,subTypeAttribute,subAttributeValue,subIndex,content,isClick,timeDelayAfterClick);
    if(res.contains("errorHandler") || res == "Unexpected response format"){
        if(res.contains("Chrome is closed")){
            return -2;
        }else{
            return 0;
        }
    }else{
        if(res == "success"){
            return 1;
        }else{
            return 0;
        }
    }
}

void Chrome::ClosePopup()
{
    try
    {
        for (int i = 0; i < 3; i++)
        {
            switch (CheckExistElements(5.0, QStringList{"[aria-label=\"Done\"]", "[aria-label=\"Xong\"]", "body > div > div > div > div > div > div > div > div > div > div > div > div:nth-child(5) > div", "[data-visualcompletion=\"ignore\"] [role=\"dialog\"] [role=\"button\"]", "[style=\"transform: translateX(0%) translateZ(1px);\"]>div>div:nth-child(2)>div:nth-child(3)>div", "[style=\"transform: translate(16px, 0px);\"] [role=\"button\"]", "[style=\"padding-top: 40px;\"]>div>div>[role=\"button\"]", "[style=\"transform: translateX(0%) translateZ(1px);\"] [role=\"button\"]", "[role=\"dialog\"]>div>div>div:nth-child(3)>div", "[role=\"dialog\"] [style*=\"transform: translate\"]>div>div>div [role=\"button\"]"}))
            {
            default:
                return;
            case 1:
                ScrollSmoothv2("document.querySelector('[aria-label=\"Done\"]')");
                DelayTime(1.0);
                ExecuteScript("document.querySelector('[aria-label=\"Done\"]').click()");
                break;
            case 2:
                ScrollSmoothv2("document.querySelector('[aria-label=\"Xong\"]')");
                DelayTime(1.0);
                click(4, "[aria-label=\"Xong\"]");
                break;
            case 4:
                ExecuteScript("document.querySelector('[data-visualcompletion=\"ignore\"] [role=\"dialog\"] [role=\"button\"]').click()");
                DelayTime(1.0);
                break;
            case 5:
                ScrollSmoothv2("document.querySelector('[method=\"POST\"]>div>div:nth-child(2)>div>div>div:nth-child(2)>div:nth-child(3) [role=\"button\"]')");
                DelayTime(1.0);
                click(4, "[method=\"POST\"]>div>div:nth-child(2)>div>div>div:nth-child(2)>div:nth-child(3) [role=\"button\"]");
                DelayTime(1.0);
                break;
            case 6:
                ScrollSmoothv2("document.querySelector('[style=\"transform: translate(16px, 0px);\"] [role=\"button\"]')");
                DelayTime(1.0);
                click(4, "[style=\"transform: translate(16px, 0px);\"] [role=\"button\"]");
                DelayTime(1.0);
                break;
            case 7:
                click(4, "[style=\"padding-top: 40px;\"]>div>div>[role=\"button\"]");
                DelayTime(1.0);
                break;
            case 8:
                ExecuteScript("document.querySelector('[style=\"transform: translateX(0%) translateZ(1px);\"] [role=\"button\"]').click()");
                DelayTime(1.0);
                break;
            case 9:
                ExecuteScript("document.querySelector('[role=\"dialog\"]>div>div>div:nth-child(3)>div').click()");
                DelayRandom(2, 4);
                break;
            case 10:
                ExecuteScript("document.querySelector('[role=\"dialog\"] [style*=\"transform: translate\"]>div>div>div [role=\"button\"]').click()");
                DelayTime(1.0);
                break;
            case 3:
                break;
            }
            DelayTime(1.0);
        }
    }
    catch(...)
    {
    }
}

void Chrome::DelayRandom(int timeFrom, int timeTo)
{
    if (timeFrom > timeTo)
    {
        DelayTime(QRandomGenerator::global()->bounded(timeTo, timeFrom + 1));
    }
    else
    {
        DelayTime(QRandomGenerator::global()->bounded(timeFrom, timeTo + 1));
    }
}

void Chrome::DelayThaoTacNho(int timeAdd)
{
    DelayTime(QRandomGenerator::global()->bounded(timeAdd + 1, timeAdd + 4));
}
