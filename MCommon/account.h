#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "qelapsedtimer.h"
#include "qobject.h"
#include "qtimer.h"
class Account : public QObject {
    Q_OBJECT

public:
    explicit Account(QThread* thread, int limitTimeRun = 0, QObject* parent = nullptr);

    QString getTimeRun() const;

private slots:
    void checkTimeLimit();

private:
    QThread* thread;
    QElapsedTimer timeBegin;
    QTimer* timer;
    int limitTimeRun;
};

#endif // ACCOUNT_H
