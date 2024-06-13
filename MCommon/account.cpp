#include "account.h"
#include "qthread.h"
#include "qtimer.h"
Account::Account(QThread* thread, int limitTimeRun, QObject* parent)
    : QObject(parent), thread(thread), limitTimeRun(limitTimeRun), timer(new QTimer(this)) {
    timeBegin.start();

    if (limitTimeRun > 0) {
        connect(timer, &QTimer::timeout, this, &Account::checkTimeLimit);
        timer->start(1000);  // Check every second
    }
}

QString Account::getTimeRun() const {
    int elapsedSeconds = timeBegin.elapsed() / 1000;
    int hours = elapsedSeconds / 3600;
    int minutes = (elapsedSeconds % 3600) / 60;
    int seconds = elapsedSeconds % 60;
    return QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

void Account::checkTimeLimit() {
    if (timeBegin.elapsed() >= limitTimeRun * 1000 && thread->isRunning()) {
        thread->terminate();
        thread->wait();
        timer->stop();
    }
}
