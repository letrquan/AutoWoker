#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <QString>
#include <QVariant>
class StringHelper{
public:
    static bool isInteger(const QVariant& var) {
        return var.type() == QVariant::Int || var.type() == QVariant::LongLong || var.type() == QVariant::UInt || var.type() == QVariant::ULongLong;
    }
};

#endif // STRINGHELPER_H
