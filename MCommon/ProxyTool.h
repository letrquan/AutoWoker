#ifndef PROXYTOOL_H
#define PROXYTOOL_H
#include "qobject.h"
class ProxyTool: public QObject{
    Q_OBJECT

public:
    explicit ProxyTool(QObject *parent = nullptr) : QObject(parent) {}

    // Disable copy constructor and assignment operator
    ProxyTool(const ProxyTool&) = delete;
    ProxyTool& operator=(const ProxyTool&) = delete;
};

#endif // PROXYTOOL_H
