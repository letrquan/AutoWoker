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
    if(create != "success"){
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
