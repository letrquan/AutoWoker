#include "checkcookieworker.h"
#include "../Utils/Utils.h"
#include "../maxcare/Language.h"
#include "../maxcare/SettingsTool.h"
#include "../MCommon/requesthandle.h"
CheckCookieWorker::CheckCookieWorker(int row, QTableWidget *tableWidget)
    : BaseWorker(row, tableWidget){}

void CheckCookieWorker::run(){
    QString cellAccount = tableWidget->item(row, Utils::GetIndexByColumnHeader(tableWidget,"Cookies"))->text();
    if (cellAccount.trimmed() == "")
    {
        emit setStatusAccount(row, Language::GetValue("Cookie trô\u0301ng!"));
    }
    // GetCellAccount(row, "cUseragent").trimmed();
    QString text = "";
    int typeProxy = 0;
    if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 9)
    {
        text = tableWidget->item(row, Utils::GetIndexByColumnHeader(tableWidget,"Proxy"))->text();
        typeProxy = (text.endsWith("*1") ? 1 : 0);
        if (text.endsWith("*0") || text.endsWith("*1"))
        {
            text = text.left(text.length() - 2);
        }
    }
    emit setStatusAccount(row, Language::GetValue("Checking..."));
    bool isCheckpoint = false;
    CheckDangCheckPoint(row, "", cellAccount, text, typeProxy,  isCheckpoint);
}

void CheckCookieWorker::CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282){
    try {
        RequestHandle requestXNet(cookie, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);
        isCheckpoint282 = false;
        QString text = requestXNet.RequestGet("https://mbasic.facebook.com/");
        QString url = requestXNet.GetUrl();
        if(url.contains("checkpoint/disabled")){
            emit setStatusAccount(indexRow, statusProxy + "Vô hiệu hóa!");
            emit setInfoAccount(indexRow, "Checkpoint: vhh");
            emit setRowColor(indexRow, 1);
        }else if (url.contains("828281030927956"))
        {
            QString text2 = "956";
            text2 = ((!text.contains("/stepper/")) ? (text2 + "-Tìm hiểu thêm") : (text2 + "-Bắt đầu"));
           emit setStatusAccount(indexRow, statusProxy + "Checkpoint " + text2 + "!");
            emit setInfoAccount(indexRow, "Checkpoint: " + text2);
            emit setRowColor(indexRow, 1);
        }else if (url.contains("1501092823525282"))
        {
            emit setInfoAccount(indexRow, "Checkpoint: 282");
            emit setStatusAccount(indexRow, statusProxy + "Checkpoint 282!");
            isCheckpoint282 = true;
        }
        else if (url.contains("facebook.com/gettingstarted") || (text.contains("href=\"/menu/bookmarks/") && text.contains("id=\"mbasic_logout_button\"")))
        {
            emit setInfoAccount(indexRow, "Live");
            emit setStatusAccount(indexRow, "Tài khoản live!");
            emit setRowColor(indexRow, 2);
        }
        else if (text.contains("https://mbasic.facebook.com/login.php") || text.contains("name=\"login\""))
        {
            emit setStatusAccount(indexRow, statusProxy + "No login!");
        }
        else if (text.contains("confirmation"))
        {
            emit setStatusAccount(indexRow, statusProxy + "Novery Live!");
            emit setRowColor(indexRow, 2);
        }
        else if (text.contains("/login/device-based/validate-pin/"))
        {
            emit setStatusAccount(indexRow, statusProxy + "Cookie bị đăng xuất!");
            emit setRowColor(indexRow, 2);
        }
        else
        {
            emit setStatusAccount(indexRow, statusProxy + "Dạng Checkpoint khác!");
            emit setRowColor(indexRow, 1);
        }
    } catch (...) {
        emit setStatusAccount(indexRow, statusProxy + "Không check được!");
    }
}
