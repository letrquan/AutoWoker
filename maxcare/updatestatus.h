#ifndef UPDATESTATUS_H
#define UPDATESTATUS_H
#include <QString>
class UpdateStatus
{
public:
    UpdateStatus();
    static bool isSaveSettings;
    static QString GetStatusById(QString id);
    static void GetValueFromDatabase();
    static void SetStatusById(QString id, QString status);
private:
    static QMap<QString, QString> dicIdStatus;
};

#endif // UPDATESTATUS_H
