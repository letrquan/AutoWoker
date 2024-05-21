#ifndef LANGUAGE_H
#define LANGUAGE_H
#include "Base.h"
#include <QString>
#include <QWidget>
#include <QTableWidget>

class Language{
public:
    static QString GetValue(QString key);
    static void SetLanguage(QWidget* control);
    static QList<QWidget*> GetAllControl(QWidget* parent);
};

#endif // LANGUAGE_H
