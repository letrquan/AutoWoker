#ifndef CHECKWALLWORKER_H
#define CHECKWALLWORKER_H

#include "baseworker.h"
#include <QObject>
#include <QTableWidget>
#include <QRunnable>

class CheckWallWorker : public BaseWorker {
    Q_OBJECT
public:
    CheckWallWorker(int row, const QString &token, QTableWidget *tableWidget);
    void run() override;
private:
    QString token;
    bool checkIsUidFacebook(const QString &uid);
};

#endif // CHECKWALLWORKER_H
