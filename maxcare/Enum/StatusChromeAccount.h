#ifndef STATUSCHROMEACCOUNT_H
#define STATUSCHROMEACCOUNT_H
#include <QObject>

class StatusChromeAccount : public QObject {
    Q_OBJECT
    Q_ENUMS(Status) // Use Q_ENUM for new code, Q_ENUMS for compatibility

public:
    enum Status {
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
};
#endif // STATUSCHROMEACCOUNT_H
