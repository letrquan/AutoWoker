#include "chrome.h"
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
}
bool Chrome::Open(){
    api->startApiProcess();
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
