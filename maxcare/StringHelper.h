#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <QString>
#include <QVariant>
#include "../MCommon/Common.h"
class StringHelper{
public:
    static bool isInteger(const QVariant& var) {
        return var.type() == QVariant::Int || var.type() == QVariant::LongLong || var.type() == QVariant::UInt || var.type() == QVariant::ULongLong;
    }

    static QString randomChar(const QString& content, int type = 0, QChar c = '*')
    {
        try
        {
            QString text;
            for (const QChar& ch : content)
            {
                if (ch != c)
                {
                    text += ch;
                    continue;
                }
                switch (type)
                {
                case 0:
                    text += Common::createRandomNumber(1);
                    break;
                case 1:
                    text += Common::createRandomString(1);
                    break;
                case 2:
                    text += createRandomStringNumber(1);
                    break;
                }
            }
            return text;
        }
        catch (...)
        {
            // Handle or log the exception as needed
        }
        return QString();
    }
};

#endif // STRINGHELPER_H
