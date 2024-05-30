#ifndef CHECKCOOKIEWORKER_H
#define CHECKCOOKIEWORKER_H

#include "baseworker.h"
class CheckCookieWorker : public BaseWorker
{
public:
    CheckCookieWorker(int row, QTableView *tableView);
    void run() override;
private:
    void CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282);
};

#endif // CHECKCOOKIEWORKER_H
