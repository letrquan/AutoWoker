#include "baseworker.h"

BaseWorker::BaseWorker(int row, QTableWidget *tableWidget, QObject *parent)
    : QObject(parent), row(row), tableWidget(tableWidget) {}
