#ifndef COMMONCHROME_H
#define COMMONCHROME_H
#include "qregularexpression.h"
#include <QString>
#include "../MCommon/chrome.h"
#include <QQueue>
#include "../maxcare/SettingsTool.h"
#include "../MCommon/Common.h"
class CommonChrome{
public:
    static bool CheckStringContainKeyword(const QString &content, const QStringList &lstKeyword) {
        for (const QString &keyword : lstKeyword) {
            QRegularExpression re(keyword);
            if (re.match(content).hasMatch() || content.contains(keyword)) {
                return true;
            }
        }
        return false;
    }
    static QString LoginFacebookUsingUidPassNew(Chrome* chrome, const QString uid, QString pass, QString fa2 = "", const QString url = "https://mobile.facebook.com", int tocDoGoVanBan = 0, bool isDontSaveBrowser = false, int type2Fa = 0, int timeOut = 120, bool isLoginVia = false, bool isCheckPass = false) {
        QQueue<QString> queue;
        if (isCheckPass) {
            QStringList passList = SettingsTool::GetSettings("configGeneral").GetValueList("txtCheckPass");
            queue.clear();
            for (const QString& pass : passList)
            {
                queue.enqueue(pass);
            }
        }
        int num = 0;
        QString uRL = chrome->GetUrl();
        if (uRL.contains("1501092823525282") || uRL.contains("828281030927956") || (uRL.contains("facebook.com/nt/screen/?params=") && uRL.contains("checkpoint")))
        {
            return "2";
        } else {
            int num2 = 0;
            int startTick = QTime::currentTime().msecsSinceStartOfDay();
            try {
                int typeWeb = checkFacebookWebsite(chrome, url);
                while (true) {
                    IL_007c:
                    if (chrome->CheckExistElement("[name='email']") != 1 || chrome->CheckExistElement("[name='pass']") != 1 || chrome->CheckExistElement("[name='login'],#loginbutton") != 1 || chrome->CheckExistElement("[data-cookiebanner=\"accept_button\"]") == 1) {
                        if (chrome->GetUrl().contains("facebook.com/user_cookie_prompt"))
                        {
                            chrome->GotoURL("https://mobile.facebook.com/");
                        }
                        if (chrome->CheckExistElement("[name=\"accept_only_essential\"][value=\"0\"]"))
                        {
                            chrome->ClickWithAction("[name=\"accept_only_essential\"][value=\"0\"]");
                        }
                        chrome->ExecuteScript("document.querySelector('[name=\"primary_consent_button\"]').click()");
                        chrome->ExecuteScript("document.querySelector('[data-cookiebanner=\"accept_button\"]').click()");
                        chrome->ExecuteScript("document.querySelectorAll('[data-testid=\"cookie-policy-manage-dialog-accept-button\"]')[1].click()");
                        if (!chrome->CheckExistElement("[name=\"pass\"]"))
                        {
                            chrome->GotoURL(url + "/login");
                            chrome->ExecuteScript("document.querySelector('[data-cookiebanner=\"accept_button\"]').click()");
                            chrome->ExecuteScript("document.querySelectorAll('[data-testid=\"cookie-policy-manage-dialog-accept-button\"]')[1].click()");
                        }
                    }
                    if(chrome->GetFbWeb() == 1){
                        if (chrome->ClickJs(0, QStringList { "[data-userid] [name=\"login\"]", "[data-userid]" }) && chrome->CheckExistElement("[role=\"dialog\"] [name=\"pass\"]", 5.0))
                        {
                            chrome->DelayTime(1.0);
                            chrome->SendKeysWithSpeedNew("[role=\"dialog\"] [name=\"pass\"]", pass, 0.1);
                            chrome->DelayTime(1.0);
                            chrome->ClickJs("[role=\"dialog\"] [name=\"login\"]");
                        }
                    }else if (!chrome->CheckExistElement("[name='email']") || !chrome->CheckExistElement("[name='pass']") || !chrome->CheckExistElement("[name='login']"))
                    {
                        if (chrome->ClickJs(0, QStringList { "[data-sigil=\"login_profile_form\"] div[role=\"button\"]", "[action*=\"/login/device-based/\"] [type=\"submit\"]" }))
                        {
                            if(chrome->CheckExistElements(5.0, QStringList { "[name=\"pass\"]", "#approvals_code" }) == 1)
                            {
                                chrome->DelayTime(1.0);
                                chrome->SendKeysWithSpeedNew("[name=\"pass\"]", pass, 0.1);
                                chrome->DelayTime(1.0);
                                chrome->sendEnter("[name=\"pass\"]");
                            }
                        }
                        else if (chrome->GetFbWeb() > 1 && chrome->CheckExistElement("#nux-nav-button,[href^=\"/a/nux/wizard/nav.php\"]", 4.0) == 1)
                        {
                            chrome->ClickWithAction("#nux-nav-button,[href^=\"/a/nux/wizard/nav.php\"]");
                        }
                    }
                    if (chrome->CheckExistElement("[name='email']") == 1 && chrome->CheckExistElement("[name='pass']") == 1 && chrome->CheckExistElement("[name='login'],#loginbutton") == 1) {
                        if(chrome->CheckExistElement("[role=\"button\"][tabindex=\"0\"][aria-label=\"Allow all cookies\"]")){
                            chrome->click(4, "[role=\"button\"][tabindex=\"0\"][aria-label=\"Allow all cookies\"]");
                            chrome->DelayTime(1.0);
                        }
                        QString text2 = chrome->GetUrl();
                        chrome->Clear("[name='email']");
                        chrome->SendKeysWithSpeedNew("[name='email']", uid, 0.1);
                        chrome->DelayTime(1.0);
                        chrome->Clear("[name='pass']");
                        chrome->SendKeysWithSpeedNew("[name='pass']", pass, 0.1);
                        chrome->DelayTime(1.0);
                        chrome->ClickWithAction("[name='login'],#loginbutton");
                        chrome->DelayTime(2.0);
                        for (int i = 0; i < 10; i++)
                        {
                            if (chrome->GetUrl() != text2)
                            {
                                break;
                            }
                            if (chrome->ExecuteScript("return document.querySelector('[name = \'pass\']').value") == "")
                            {
                                break;
                            }
                            chrome->DelayTime(2.0);
                        }
                    }
                    int num3 = 0;
                    int num4 = 5;
                    int num5 = 0;
                    int num6 = 2;
                    int num7 = 0;
                    while (QTime::currentTime().msecsSinceStartOfDay() - startTick < timeOut * 1000) {
                        switch (chrome->CheckExistElements(0.0, QStringList{"[name=\"login\"]","[name=\"approvals_code\"]", "[name=\"verification_method\"]", "#checkpointSubmitButton", "#qf_skip_dialog_skip_link", "#nux-nav-button", "[name=\"n\"]", "[name=\"reset_action\"]", "#checkpointBottomBar", "[name=\"primary_consent_button\"]", "#identify_search_text_input", "[name=\"submit[Get Started]\"]","[role=\"button\"][tabindex=\"0\"][aria-label=\"Allow all cookies\"]"})) {
                        case 1:
                        case 8:
                            if (num5 == 0 && num7 == 0) {
                                QString text;
                                switch (checkTypeWebFacebookFromUrl(chrome->GetUrl())) {
                                case 1:
                                    text = chrome->ExecuteScript("var out='';var x=document.querySelector('#error_box');if(x!=null) out=x.innerText;return out;");
                                    text = ((text.split("\r\n", Qt::SkipEmptyParts).size() > 1) ? text.split("\r\n", Qt::SkipEmptyParts)[1] : text);
                                    break;
                                case 2:
                                    text = chrome->ExecuteScript("var out='';var x=document.querySelector('#login_error');if(x!=null) out=x.innerText;return out;");
                                    break;
                                }
                                if (!text.isEmpty()) {
                                    return text;
                                }
                                if (chrome->CheckExistElement("[href=\"/login/identify/\"]") == 1) {
                                    num = 4;
                                } else if (chrome->CheckExistElement("#account_recovery_initiate_view_label") == 1) {
                                    num = 5;
                                } else if (!QVariant(chrome->ExecuteScript("return (document.querySelector('[name=\"email\"]').value!='' && document.querySelector('[name=\"pass\"]').value!='')+''")).toBool()) {
                                    if (chrome->ExecuteScript("return document.querySelector('[name=\"email\"]').value").trimmed().isEmpty()) {
                                        num = 4;
                                    } else if (chrome->ExecuteScript("return document.querySelector('[name=\"pass\"]').value").trimmed().isEmpty()) {
                                        num = 5;
                                    }
                                }
                            } else if (chrome->ExecuteScript("return document.querySelector('[name=\"email\"]').value").trimmed().isEmpty()) {
                                num = 0;
                                goto end_IL_03b5;
                            }
                            break;
                        case 2:
                            if (fa2 == "")
                            {
                                num = 3;
                                break;
                            }
                            if (num5 >= num6)
                            {
                                num = 6;
                                break;
                            }
                            if (isLoginVia)
                            {
                                chrome->GotoURL(chrome->GetUrl().replace("www.face", "m.face"));
                                for (int m = 0; m < 10; m++)
                                {
                                    if (chrome->CheckExistElement("[name=\"approvals_code\"]") == 1)
                                    {
                                        break;
                                    }
                                    chrome->DelayTime(1.0);
                                }
                            }
                            if (Common::GetTotp(fa2.replace(" ", "").replace("\n", "").trimmed(), type2Fa) == "")
                            {
                                num = 6;
                                break;
                            }
                            num5++;
                            chrome->sendKeys(2, "approvals_code", Common::GetTotp(fa2.replace(" ", "").replace("\n", "").trimmed(), type2Fa));
                            chrome->DelayTime(1.0);
                            chrome->sendEnter("[name='approvals_code']");
                            chrome->DelayTime(1.0);
                            break;
                        case 3:
                            num = 2;
                            break;
                        case 4:
                            num3++;
                            if (num3 >= num4) {
                                num = 2;
                                break;
                            }
                            if (chrome->CheckExistElement("#checkpointSubmitButton>input") == 1) {
                                chrome->ClickJs("#checkpointSubmitButton>input");
                            } else if (chrome->CheckExistElement("#checkpointSubmitButton>button") == 1) {
                                chrome->ClickJs("#checkpointSubmitButton>button");
                            } else {
                                chrome->ClickJs("#checkpointSubmitButton");
                            }
                            chrome->DelayTime(2.0);
                            break;
                        case 5:
                            if (chrome->ClickWithAction(1, "qf_skip_dialog_skip_link") == 0)
                            {
                                chrome->ExecuteScript("document.getElementById('qf_skip_dialog_skip_link').click()");
                            }
                            chrome->DelayTime(2.0);
                            break;
                        case 6:
                            chrome->click(1, "nux-nav-button");
                            chrome->DelayTime(2.0);
                            break;
                        case 7:
                            num = 5;
                            break;
                        case 9:
                            if (num5 > 1)
                            {
                                num = 6;
                                break;
                            }
                            if (chrome->CheckExistElements(0.0,
                                                          QStringList{"[name=\"verification_method\"]",
                                                          "[name=\"submit[Yes]\"]",
                                                          "[name=\"send_code\"]",
                                                          "#captcha_response",
                                                                       "[href=\"https://www.facebook.com/communitystandards/\"]"}) != 0 || CheckStringContainKeyword(chrome->GetPageSource(),
                                                             QStringList{ "/checkpoint/dyi", "https://www.facebook.com/communitystandards/", "help/121104481304395", "checkpoint/828281030927956" })
                                )
                            {
                                num = 2;
                                break;
                            }
                            num2 = chrome->CheckExistElements(0.0, QStringList{"button#checkpointSubmitButton","#checkpointSubmitButton [type=\"submit\"]", "#checkpointButtonGetStarted"});
                            if (num7 < 10)
                            {
                                if (chrome->CheckExistElement("[value=\"dont_save\"]") == 1 && isDontSaveBrowser)
                                {
                                    chrome->click(4, "[value=\"dont_save\"]");
                                }
                                num7++;
                                if (num2 == 1)
                                {
                                    chrome->click(4, "button#checkpointSubmitButton");
                                }else if (num2 == 3)
                                {
                                    chrome->click(4, "#checkpointButtonGetStarted");
                                    chrome->DelayTime(10.0);
                                    int numchecksubmit = 0;
                                    while (numchecksubmit<5)
                                    {
                                        if (chrome->CheckExistElement("button#checkpointSubmitButton") == 1)
                                        {
                                            chrome->click(4, "button#checkpointSubmitButton"); //password_confirm
                                            break;
                                        }
                                        numchecksubmit++;
                                        chrome->DelayTime(5);
                                    }
                                }
                                else
                                {
                                    chrome->click(4, "#checkpointSubmitButton [type=\"submit\"]");
                                }
                                chrome->DelayTime(1.0);
                            }
                            else
                            {
                                num = 0;
                            }
                            break;
                        case 10:
                            chrome->click(4, "[name=\"primary_consent_button\"]", chrome->CountElement("[name=\"primary_consent_button\"]") - 1);
                            break;
                        case 11:
                            goto IL_094e;
                            break;
                        case 12:
                            chrome->click(4, "[name=\"submit[Get Started]\"]");
                            chrome->DelayTime(10.0);
                            break;
                        case 13:

                            break;
                        default:
                            if ((chrome->ExecuteScript("async function checkCookie(){try{let a=await fetch(\"https://www.facebook.com/me\"),b=\"0|0\";if(a.ok){if(a.url.includes(\"checkpoint\"))b=\"0|1\";else if(a.url.includes(\"com/?refsrc\")||\"https://www.facebook.com/\"==a.url)b=\"0|2\";else{let d=await a.text();if(d.includes(\"/photos/change/profile_picture\"))b=\"1|1\";else{let e=d.match(/\"USER_ID\"\\:\"([0-9]{0,})\"/)[1],f=document.cookie.match(/c_user\\=([0-9]{0,})/)[1];e==f&&(b=\"1|1\")}}}return b}catch{}}var c=await checkCookie(); return c")).startsWith("0|"))
                            {
                                num = 2;
                                break;
                            }
                            if (CheckNoveri(chrome))
                            {
                                num = 8;
                                break;
                            }
                            if (chrome->GetUrl().contains("facebook.com/checkpoint/1501092823525282/") || chrome->GetUrl().contains("checkpoint/828281030927956"))
                            {
                                num = 2;
                                break;
                            }
                            if(chrome->GetUrl().contains("facebook.com/two_step_verification/two_factor")){
                                chrome->click(4, "div[role=\"button\"][tabindex=\"0\"]");
                                chrome->DelayTime(1.0);
                                chrome->ExecuteScript("document.querySelector('input[type=\"radio\"][name=\"unused\"][value=\"1\"]').click()");
                                chrome->DelayTime(1.0);
                                chrome->ExecuteScript("document.querySelectorAll('div[role=\"button\"][tabindex=\"0\"]')[3].click()");
                                chrome->DelayTime(1.0);
                                chrome->Clear("input[type=\"text\"]");
                                chrome->SendKeysWithSpeedNew("input[type=\"text\"]", Common::GetTotp(fa2.replace(" ", "").replace("\n", "").trimmed(), type2Fa),0.1);
                                chrome->DelayTime(1.0);
                                chrome->sendEnter("input[type=\"text\"]");
                                chrome->DelayTime(1.0);
                            }
                            // if(chrome->GetUrl().contains())
                            if(chrome->GetUrl().contains("facebook.com/two_factor/remember_browser")){
                                chrome->ExecuteScript("document.querySelectorAll('[role=\"button\"][tabindex=\"0\"]')[1].click()");
                                chrome->DelayTime(1.0);
                            }
                            if (chrome->GetUrl().contains("facebook.com/user_cookie_prompt"))
                            {
                                chrome->GotoURL("https://mobile.facebook.com/");
                                break;
                            }
                            if (chrome->GetUrl().contains("facebook.com/nt/screen/?params=%7B%22token") || chrome->CheckExistElements(0.0, QStringList{"[name=\"verification_method\"]", "[name=\"submit[Yes]\"]", "[name=\"send_code\"]", "#captcha_response", "[href=\"https://www.facebook.com/communitystandards/\"]"}) != 0 || CheckStringContainKeyword(chrome->GetPageSource(), QStringList { "/checkpoint/dyi", "https://www.facebook.com/communitystandards/", "help/121104481304395" }))
                            {
                                num = 2;
                            }
                            else if (CheckLoginSuccess(chrome))
                            {
                                num = 1;
                            }
                            if (CheckTypeWebFacebookFromUrl(chrome->GetUrl()) == 2)
                            {
                                if (chrome->GetUrl().startsWith("https://mobile.facebook.com/zero/policy/optin"))
                                {
                                    chrome->DelayTime(1.0);
                                    chrome->ExecuteScript("document.querySelector('a[data-sigil=\"touchable\"]').click()");
                                    chrome->DelayTime(3.0);
                                    if (chrome->CheckExistElement("button[data-sigil=\"touchable\"]", 10.0) == 1)
                                    {
                                        chrome->DelayTime(1.0);
                                        chrome->ExecuteScript("document.querySelector('button[data-sigil=\"touchable\"]').click()");
                                        chrome->DelayTime(3.0);
                                    }
                                }
                                if (QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('legal_consent/basic/?consent_step=1')){x[i].click();break;check='true'}} return check")).toBool())
                                {
                                    for (int j = 0; j < 5; j++)
                                    {
                                        Common::DelayTime(2.0);
                                        if (!QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('legal_consent/basic/?consent_step=1')){x[i].click();break;check='true'}} return check")).toBool())
                                        {
                                            break;
                                        }
                                    }
                                    for (int k = 0; k < 5; k++)
                                    {
                                        Common::DelayTime(2.0);
                                        if (!QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('consent/basic/log')){x[i].click();break;check='true'}} return check")).toBool())
                                        {
                                            break;
                                        }
                                    }
                                    if (chrome->CheckExistElement("[href=\"/home.php\"]") == 1)
                                    {
                                        chrome->click(4, "[href=\"/home.php\"]");
                                    }
                                }
                                if (chrome->GetUrl().startsWith("https://mobile.facebook.com/legal_consent"))
                                {
                                    chrome->ExecuteScript("document.querySelector('button').click()");
                                    chrome->DelayTime(1.0);
                                    chrome->ExecuteScript("document.querySelectorAll('button')[1].click()");
                                    chrome->DelayTime(1.0);
                                    chrome->ExecuteScript("document.querySelector('button').click()");
                                    chrome->DelayTime(1.0);
                                    chrome->ExecuteScript("document.querySelectorAll('button')[1].click()");
                                    chrome->DelayTime(1.0);
                                }
                                if (chrome->GetUrl().startsWith("https://mobile.facebook.com/si/actor_experience/actor_gateway"))
                                {
                                    chrome->click(4, "[data-sigil=\"touchable\"]");
                                    chrome->DelayTime(1.0);
                                }
                                if (chrome->CheckExistElement("button[value=\"OK\"]") == 1)
                                {
                                    chrome->click(4, "button[value=\"OK\"]");
                                    chrome->DelayTime(1.0);
                                }
                                if (chrome->CheckExistElement("[data-store-id=\"2\"]>span") == 1)
                                {
                                    chrome->click(4, "[data-store-id=\"2\"]>span");
                                    chrome->DelayTime(1.0);
                                }
                                if (chrome->CheckExistElement("[data-nt=\"FB:HEADER_FOOTER_VIEW\"]>div>div>div>span>span") == 1)
                                {
                                    chrome->click(4, "[data-nt=\"FB:HEADER_FOOTER_VIEW\"]>div>div>div>span>span");
                                    chrome->DelayTime(3.0);
                                }
                            }
                            else
                            {
                                if (!chrome->GetUrl().startsWith("https://www.facebook.com/legal_consent"))
                                {
                                    break;
                                }
                                for (int l = 0; l < 5; l++)
                                {
                                    if (chrome->CheckExistElement("button") != 1)
                                    {
                                        break;
                                    }
                                    chrome->ExecuteScript("document.querySelector('button').click()");
                                    chrome->DelayTime(1.0);
                                }
                            }
                            break;
                        }
                        if (num != 0) {
                            break;
                        }
                        continue;
                    IL_094e:
                        chrome->GotoURL("https://www.facebook.com/login");
                        chrome->DelayTime(1.0);
                        typeWeb = 0;
                        goto IL_007c;
                        continue;
                    end_IL_03b5:
                        break;
                    }
                    break;
                }
            } catch (const QException& e) {
                Common::ExportError(&e,"Error Login Uid Pass");
            }
        }
        return QString::number(num);
    }
    static int checkFacebookWebsite(Chrome* chrome, const QString& url) {
        if (chrome->CheckChromeClose()) {
            return -2;
        }
        int num = 0;
        for (int i = 0; i < 2; i++) {
            num = checkTypeWebFacebookFromUrl(chrome->GetUrl());
            if (num != 0) {
                break;
            }
            chrome->GotoURL(url);
            chrome->DelayTime(1.0);
        }
        return num;
    }
    static int checkTypeWebFacebookFromUrl(const QString& url) {
        int result = 0;
        if (url.startsWith("https://www.facebook") || url.startsWith("https://facebook") || url.startsWith("https://web.facebook")) {
            result = 1;
        } else if (url.startsWith("https://m.facebook") || url.startsWith("https://d.facebook") || url.startsWith("https://mobile.facebook")) {
            result = 2;
        } else if (url.startsWith("https://mbasic.facebook")) {
            result = 3;
        }
        return result;
    }

    static bool CheckNoveri(Chrome* chrome, const QString& currentUrl = QString(), const QString& html = QString())
    {
        QString url = currentUrl;
        if (url.isEmpty()) {
            url = chrome->GetUrl();
        }

        QStringList lstKeyword = {"facebook.com/confirmemail", "facebook.com/confirmation", "facebook.com/conf/strongrec/?contact="};
        if (CheckStringContainKeyword(url, lstKeyword)) {
            return true;
        }

        QStringList list = {"[name=\"c\"]"};
        if (chrome->CheckExistElements(0.0, list) > 0) {
            return true;
        }

        return false;
    }

    static bool CheckLoginSuccess(Chrome* chrome, const QString& currentUrl = QString(), const QString& html = QString())
    {
        try {
            if (chrome->GetFbWeb() == 2) {
                chrome->ClickJs(0, QStringList() << "[href^=\"/a/preferences.php?fast_switch_site\"]");
            }

            QString url = currentUrl;
            if (url.isEmpty()) {
                url = chrome->GetUrl();
            }

            QStringList lstKeyword = {"https://mobile.facebook.com/home.php"};
            if (CheckStringContainKeyword(url, lstKeyword)) {
                return true;
            }

            QString pageHtml = html;
            if (pageHtml.isEmpty()) {
                pageHtml = chrome->GetPageSource();
            }

            QStringList lstKeyword2 = {"/friends/", "/logout.php?button_location=settings&amp;button_name=logout"};
            if (CheckStringContainKeyword(pageHtml, lstKeyword2)) {
                return true;
            }

            QStringList list = {"a[href*=\"/friends/\"]", "[action=\"/logout.php?button_location=settings&button_name=logout\"]"};
            if (chrome->CheckExistElements(0.0, list) > 0) {
                return true;
            }

            QString script = "async function checkCookie(){try{let a=await fetch(\"https://www.facebook.com/me\"),b=\"0|0\";if(a.ok){if(a.url.includes(\"checkpoint\"))b=\"0|1\";else if(a.url.includes(\"com/?refsrc\")||\"https://www.facebook.com/\"==a.url)b=\"0|2\";else{let d=await a.text();if(d.includes(\"/photos/change/profile_picture\"))b=\"1|1\";else{let e=d.match(/\"USER_ID\"\\:\"([0-9]{0,})\"/)[1],f=document.cookie.match(/c_user\\=([0-9]{0,})/)[1];e==f&&(b=\"1|1\")}}}return b}catch{}}var c=await checkCookie(); return c";
            QString result = chrome->ExecuteScript(script);
            if (result == "1|1") {
                return true;
            }
        }
        catch (const std::exception&) {
            // Handle exception
        }

        return false;
    }

    static int CheckTypeWebFacebookFromUrl(const QString &url)
    {
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


    static QString LoginFacebookUsingCookie(Chrome* chrome, const QString& cookie, const QString& URL = "https://www.facebook.com")
    {
        try
        {
            if (chrome->GotoURLIfNotExist(URL) == -2)
            {
                return "-2";
            }
            if (chrome->AddCookieIntoChrome(cookie) == -2)
            {
                return "-2";
            }
            if (chrome->Refresh() == -2)
            {
                return "-2";
            }

            bool ok;
            int liveCookieResult = CheckLiveCookie(chrome);
            if (ok)
            {
                return QString::number(liveCookieResult);
            }
            else
            {
                return "";
            }
        }
        catch (...)
        {
            // Catch all exceptions
        }
        return "0";
    }

    static int CheckLiveCookie(Chrome* chrome, QString url = "https://mobile.facebook.com")
    {
        try {
            if (chrome->CheckChromeClose()) {
                return -2;
            }
            if (chrome->GetFbWeb() != chrome->GetFbWeb(url)) {
                chrome->GotoURL(url);
            }
            if (chrome->GetFbWeb() == 2) {
                chrome->ClickJs(0, QStringList{"[href^=\"/a/preferences.php?fast_switch_site\"]"});
            }
            if (CheckNoveri(chrome)) {
                return 8;
            }
            QString text = chrome->ExecuteScript("async function checkCookie(){try{let a=await fetch(\"/me\"),b=\"0|0\";if(a.ok){if(a.url.includes(\"checkpoint\"))b=\"0|1\";else if(a.url.includes(\"com/?refsrc\")||\"https://www.facebook.com/\"==a.url)b=\"0|2\";else{let d=await a.text();if(d.includes(\"/photos/change/profile_picture\"))b=\"1|1\";else{let e=d.match(/\"USER_ID\"\\:\"([0-9]{0,})\"/)[1],f=document.cookie.match(/c_user\\=([0-9]{0,})/)[1];e==f&&(b=\"1|1\")}}}return b}catch{}}var c=await checkCookie(); return c");
            if (text == "0|1") {
                return 2;
            }
            if (text == "1|1") {
                return 1;
            }
            QString uRL = chrome->GetUrl();
            if (uRL.contains("facebook.com/checkpoint/") || uRL.contains("facebook.com/nt/screen/?params=%7B%22token") || uRL.contains("facebook.com/x/checkpoint/")) {
                return 2;
            }
            if (chrome->GetUrl().contains("facebook.com/user_cookie_prompt")) {
                chrome->GotoURL("https://mobile.facebook.com/");
            }
            switch (checkFacebookWebsite(chrome, url)) {
            case 2: {
                for (int num = 0; num < 30; num++) {
                    CheckStatusAccount(chrome, true);
                    switch (chrome->Status) {
                    case StatusChromeAccount::ChromeClosed:
                        return -2;
                    case StatusChromeAccount::LoginWithUserPass:
                    case StatusChromeAccount::LoginWithSelectAccount:
                        return 0;
                    case StatusChromeAccount::Checkpoint:
                        return 2;
                    case StatusChromeAccount::Logined:
                        return 1;
                    case StatusChromeAccount::NoInternet:
                        return -3;
                    case StatusChromeAccount::Noveri:
                        return 3;
                    case StatusChromeAccount::Empty:
                    case StatusChromeAccount::Blocked:
                        break;
                    }
                    // chrome->AcceptCookie();
                    if (chrome->CheckExistElement("a[href*=\"/zero/optin/write/?action=cancel&page=dialtone_optin_page\"]", 5.0) == 1) {
                        chrome->ExecuteScript("document.querySelector('a[href*=\"/zero/optin/write/?action=cancel&page=dialtone_optin_page\"]').click()");
                        chrome->DelayTime(3.0);
                        if (chrome->CheckExistElement("[action=\"/zero/optin/write/?action=confirm&page=reconsider_optin_dialog\"] button", 10.0) == 1) {
                            chrome->ExecuteScript("document.querySelector('[action=\"/zero/optin/write/?action=confirm&page=reconsider_optin_dialog\"] button').click()");
                            chrome->DelayTime(3.0);
                        }
                    }
                    if (chrome->GetUrl().contains("facebook.com/zero/optin/write/")) {
                        chrome->DelayTime(1.0);
                        chrome->ExecuteScript("document.querySelector('[action=\"/zero/optin/write/?action=confirm&page=reconsider_optin_dialog\"] button').click()");
                        chrome->DelayTime(3.0);
                    }
                    if (chrome->GetUrl().contains("facebook.com/zero/policy/optin")) {
                        chrome->DelayTime(1.0);
                        chrome->ExecuteScript("document.querySelector('a[data-sigil=\"touchable\"]').click()");
                        chrome->DelayTime(3.0);
                        if (chrome->CheckExistElement("button[data-sigil=\"touchable\"]", 10.0) == 1) {
                            chrome->DelayTime(1.0);
                            chrome->ExecuteScript("document.querySelector('button[data-sigil=\"touchable\"]').click()");
                            chrome->DelayTime(3.0);
                        }
                    }
                    if (QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('legal_consent/basic/?consent_step=1')){x[i].click();break;check='true'}} return check")).toBool()) {
                        for (int j = 0; j < 5; j++) {
                            Common::DelayTime(2.0);
                            if (!QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('legal_consent/basic/?consent_step=1')){x[i].click();break;check='true'}} return check")).toBool()) {
                                break;
                            }
                        }
                        for (int k = 0; k < 5; k++) {
                            Common::DelayTime(2.0);
                            if (!QVariant(chrome->ExecuteScript("var check='false';var x=document.querySelectorAll('a');for(i=0;i<x.length;i++){if(x[i].href.includes('consent/basic/log')){x[i].click();break;check='true'}} return check")).toBool()) {
                                break;
                            }
                        }
                        if (chrome->CheckExistElement("[href=\"/home.php\"]") == 1) {
                            chrome->click(4, "[href=\"/home.php\"]");
                        }
                    }
                    if (chrome->GetUrl().startsWith("https://mobile.facebook.com/si/actor_experience/actor_gateway")) {
                        chrome->click(4, "[data-sigil=\"touchable\"]");
                        chrome->DelayTime(1.0);
                    }
                    if (chrome->CheckExistElement("button[value=\"OK\"]") == 1) {
                        chrome->click(4, "button[value=\"OK\"]");
                        chrome->DelayTime(1.0);
                    }
                    if (chrome->CheckExistElement("[data-store-id=\"2\"]>span") == 1) {
                        chrome->click(4, "[data-store-id=\"2\"]>span");
                        chrome->DelayTime(1.0);
                    }
                    if (chrome->CheckExistElement("[data-nt=\"FB:HEADER_FOOTER_VIEW\"]>div>div>div>span>span") == 1) {
                        chrome->click(4, "[data-nt=\"FB:HEADER_FOOTER_VIEW\"]>div>div>div>span>span");
                        chrome->DelayTime(3.0);
                    }
                    if (chrome->CheckExistElement("#nux-nav-button") == 1) {
                        bool flag = false;
                        for (int l = 0; l < 5; l++) {
                            if (flag) {
                                break;
                            }
                            switch (chrome->CheckExistElements(3.0, QStringList{"#qf_skip_dialog_skip_link", "#nux-nav-button"})) {
                            case 1:
                                chrome->ExecuteScript("document.querySelector('#qf_skip_dialog_skip_link').click()");
                                chrome->DelayTime(1.0);
                                break;
                            case 2:
                                chrome->click(1, "nux-nav-button");
                                chrome->DelayTime(2.0);
                                break;
                            default:
                                flag = true;
                                break;
                            }
                        }
                    }
                    chrome->findAndClick(0.0, 4, "[name=\"primary_consent_button\"]");
                    chrome->DelayTime(2.0);
                    if (chrome->CheckExistElement("#nux-nav-button") == 1) {
                        chrome->click(1, "nux-nav-button");
                        if (chrome->CheckExistElement("#qf_skip_dialog_skip_link", 10.0) == 1 && chrome->ClickWithAction(1, "qf_skip_dialog_skip_link") == 0) {
                            chrome->ExecuteScript("document.getElementById('qf_skip_dialog_skip_link').click()");
                        }
                    }
                }
                break;
            }
            case 1: {
                if (!chrome->GetUrl().startsWith("https://www.facebook.com/legal_consent")) {
                    break;
                }
                for (int i = 0; i < 5; i++) {
                    if (chrome->CheckExistElement("button") != 1) {
                        break;
                    }
                    chrome->ExecuteScript("document.querySelector('button').click()");
                    chrome->DelayTime(1.0);
                }
                break;
            }
            }
            CheckStatusAccount(chrome, true);
            switch (chrome->Status) {
            case StatusChromeAccount::ChromeClosed:
                return -2;
            case StatusChromeAccount::LoginWithUserPass:
            case StatusChromeAccount::LoginWithSelectAccount:
                return 0;
            case StatusChromeAccount::Checkpoint:
                return 2;
            case StatusChromeAccount::Logined:
                return 1;
            case StatusChromeAccount::NoInternet:
                return -3;
            case StatusChromeAccount::Noveri:
                return 3;
            case StatusChromeAccount::Blocked:
                break;
            case StatusChromeAccount::Empty:
                break;
            // case Empty:
            //     break;
            }
        } catch (...) {
        }
        return 0;
    }

    static void CheckStatusAccount(Chrome* chrome, bool isSendRequest, int& result) {
        try {
            if (chrome->CheckChromeClose()) {
                chrome->Status = StatusChromeAccount::ChromeClosed;
                return;
            }
            if (chrome->GetFbWeb() == 2) {
                chrome->ClickJs(0, QStringList{"[href^=\"/a/preferences.php?fast_switch_site\"]"});
            }
            if (chrome->GetUrl().startsWith("https://free.facebook.com/") || chrome->CheckExistElement("[href^=\"/upsell/advanced_upsell/in_line\"]") == 1) {
                chrome->ClickJs(0, QStringList{"[href^=\"/upsell/advanced_upsell/in_line\"]"});
                chrome->ClickJs(5, QStringList{"#upsell_upgrade_confirm_button"});
                result = 1;
            }
            QString uRL = chrome->GetUrl();
            if (uRL.startsWith("https://mobile.facebook.com/error/index.php")) {
                chrome->GotoURL("https://www.facebook.com/notifications");
                chrome->DelayTime(2.0);
                if (chrome->click("[role=\"complementary\"] [role=\"toolbar\"] [aria-pressed]|1")) {
                    chrome->DelayTime(2.0);
                }
                if (chrome->click("[role=\"complementary\"] [role=\"grid\"] [role=\"row\"] a|0")) {
                    chrome->DelayTime(2.0);
                }
                chrome->GotoURL(uRL);
                chrome->DelayTime(2.0);
            }
            if (chrome->CheckExistElement("[href^=\"/zero/optin/write/?action=cancel&page=dialtone_optin_page\"]") == 1) {
                chrome->ClickJs("[href^=\"/zero/optin/write/?action=cancel&page=dialtone_optin_page\"]");
                chrome->ClickJs(5, QStringList{"[action^=\"/zero/optin/write/?action=confirm&page=reconsider_optin_dialog\"] button"});
                result = 1;
            }
            if (chrome->CheckExistElement("#nux-nav-button") == 1) {
                chrome->ClickWithAction("#nux-nav-button");
                if (chrome->CheckExistElement("#qf_skip_dialog_skip_link", 5.0) == 1) {
                    chrome->ClickWithAction("#qf_skip_dialog_skip_link");
                }
                result = 1;
            }
            if (CheckLoginSuccess(chrome)) {
                chrome->Status = StatusChromeAccount::Logined;
                return;
            }
            QString text = "";
            if (isSendRequest) {
                QString uRL2 = chrome->GetUrl();
                uRL2 = QRegularExpression("https://(.*?)facebook.com").match(uRL2).captured(0) + "/login";
                text = RequestGet(chrome, uRL2, uRL2);
            } else {
                text = chrome->GetPageSource();
            }
            if (text == "-2") {
                chrome->Status = StatusChromeAccount::ChromeClosed;
            } else if (text.contains("login_form") || text.contains("/login/?next")) {
                if (chrome->CheckExistElement("[href*=\"/login/?next\"]") == 1) {
                    chrome->click(4, "[href*=\"/login/?next\"]");
                }
                chrome->Status = StatusChromeAccount::LoginWithUserPass;
            } else if (text.contains("login_profile_form") || text.contains("/login/device-based/validate-p")) {
                chrome->Status = StatusChromeAccount::LoginWithSelectAccount;
            } else if (QVariant(chrome->ExecuteScript("var kq=false;if(document.querySelector('#mErrorView')!=null && !document.querySelector('#mErrorView').getAttribute('style').includes('display:none')) kq=true;return kq+''")).toBool() || text.contains("href=\"https://m.facebook.com/login.php") || text.contains("href=\"https://mobile.facebook.com/login.php")) {
                chrome->Status = StatusChromeAccount::LoginWithSelectAccount;
            } else if (CheckNoveri(chrome)) {
                chrome->Status = StatusChromeAccount::Noveri;
            } else if (CheckCheckpoint(chrome)) {
                chrome->Status = StatusChromeAccount::Checkpoint;
            } else if (text.contains("error-information-popup-content") || text.contains("suggestionsSummaryList")) {
                chrome->Status = StatusChromeAccount::NoInternet;
            }
        } catch (...) {
            // Handle any exceptions
        }
    }

    static void CheckStatusAccount(Chrome* chrome, bool isSendRequest)
    {
        int result = 0;
        CheckStatusAccount(chrome,isSendRequest,result);
    }




    static bool CheckCheckpoint(Chrome* chrome, const QString& currentUrl = QString(), const QString& html = QString())
    {
        QString url = currentUrl.isEmpty() ? chrome->GetUrl() : currentUrl;

        QStringList urlKeywords = {
            "facebook.com/checkpoint/828281030927956",
            "facebook.com/checkpoint/1501092823525282",
            "facebook.com/x/checkpoint/",
            "facebook.com/checkpoint/block"
        };

        if (CheckStringContainKeyword(url, urlKeywords))
            return true;

        if (url.contains("facebook.com/nt/screen/?params=") && url.contains("checkpoint"))
            return true;

        QString pageSource = html.isEmpty() ? chrome->GetPageSource() : html;

        QStringList htmlKeywords = {
            "verification_method", "submit[Yes]", "send_code", "/checkpoint/dyi",
            "https://www.facebook.com/communitystandards/", "help/121104481304395",
            "help/166863010078512", "help/117450615006715", "checkpoint/1501092823525282",
            "checkpoint/828281030927956", "name=\"code_1\""
        };

        if (CheckStringContainKeyword(pageSource, htmlKeywords))
            return true;

        QStringList elements = {
            "[name=\"verification_method\"]",
            "[name=\"submit[Yes]\"]",
            "[name=\"send_code\"]",
            "[href=\"https://www.facebook.com/communitystandards/\"]",
            "[name=\"code_1\"]",
            "[action=\"/login/checkpoint/\"] [name=\"contact_index\"]"
        };

        if (chrome->CheckExistElements(0.0, elements) > 0)
            return true;

        return false;
    }


    static QString RequestGet(Chrome* chrome, const QString& url, const QString& website)
    {
        try
        {
            QString processedWebsite = website;
            if (processedWebsite.split('/').length() > 2)
            {
                processedWebsite.replace("//", "__");
                processedWebsite = processedWebsite.split('/').at(0);
                processedWebsite.replace("__", "//");
            }

            if (!chrome->GetUrl().startsWith(processedWebsite))
            {
                chrome->GotoURL(processedWebsite);
                chrome->DelayTime(1.0);
                chrome->ExecuteScript("document.querySelector('body').innerHTML='AUTOWORKER'; document.querySelector('body').style = 'text-align: center; background-color:#fff'");
            }

            QString script = QString(
                                 "async function RequestGet() { "
                                 "    var output = ''; "
                                 "    try { "
                                 "        var response = await fetch('%1'); "
                                 "        if (response.ok) { "
                                 "            var body = await response.text(); "
                                 "            return body; "
                                 "        } "
                                 "    } catch {} "
                                 "    return output; "
                                 "}; "
                                 "var c = await RequestGet(); "
                                 "return c;"
                                 ).arg(url);

            return chrome->ExecuteScript(script);
        }
        catch (...)
        {
            // Handle any exceptions
        }

        return QString();
    }
};

#endif // COMMONCHROME_H
