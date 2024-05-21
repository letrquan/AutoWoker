#ifndef GETCONTENTSTATUSCHROME_H
#define GETCONTENTSTATUSCHROME_H
#include <QString>
#include "StatusChromeAccount.h"
class GetContentStatusChrome {
public:
    static QString GetContent(StatusChromeAccount::Status status){
        QString result;
        switch (status) {
        case StatusChromeAccount::ChromeClosed:
            result = QObject::tr("Không tìm thấy chrome!");
            break;
        case StatusChromeAccount::Checkpoint:
            result = QObject::tr("Checkpoint!");
            break;
        case StatusChromeAccount::NoInternet:
            result = QObject::tr("Không có kết nối Internet!");
            break;
        case StatusChromeAccount::Blocked:
            result = QObject::tr("Facebook Blocked!");
            break;
        default:
            result = QObject::tr("Unknown status.");
            break;
        }
        return result;
    };
};

#endif // GETCONTENTSTATUSCHROME_H
