#ifndef STATUSCHROMEACCOUNT_H
#define STATUSCHROMEACCOUNT_H
#include <QObject>


enum class StatusChromeAccount {
    Empty,
    ChromeClosed,
    LoginWithUserPass,
    LoginWithSelectAccount,
    Checkpoint,
    Logined,
    NoInternet,
    Blocked,
    Noveri
};

#endif // STATUSCHROMEACCOUNT_H
