#include "baseworker.h"

BaseWorker::BaseWorker(int row, QTableView *tableView, QObject *parent)
    : QObject(parent), row(row), tableView(tableView) {}
