#include "checkwallworker.h"
#include "../maxcare/Language.h"
#include "../MCommon/CommonRequest.h"
#include "../MCommon/Common.h"
CheckWallWorker::CheckWallWorker(int row, const QString &token, QTableView *tableView)
    : BaseWorker(row, tableView), token(token) {}

void CheckWallWorker::run() {
    try {
        QString cellAccount = tableView->model()->index(row,Utils::GetIndexByColumnHeader(tableView,"Uid")).data().toString();
        if (!checkIsUidFacebook(cellAccount))
        {
            emit setStatusAccount(row, Language::GetValue("Uid không hợp lệ!"));
        }
        QString text = "";
        QString text2 = "";
        QString text3 = CommonRequest::CheckLiveWall(cellAccount);
        if (text3.startsWith("0|"))
        {
            text = "Die";
            text2 = "Wall die";
        }
        else if (text3.startsWith("1|"))
        {
            text = "Live";
            text2 = "Wall live";
        }
        else
        {
            text2 = Language::GetValue("Không check được!");
        }

        emit setStatusAccount(row, text2);
        if (text != "")
        {
            emit setInfoAccount(row, text);
        }
    } catch (...) {
        emit setStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
    }
}
bool CheckWallWorker::checkIsUidFacebook(const QString &uid){
    if (Common::IsNumber(uid))
    {
        if (uid.startsWith("1")|| uid.startsWith("6"))
        {
            return true;
        }
    }
    return false;
}
