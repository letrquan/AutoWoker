#ifndef GETICONFACEBOOK_H
#define GETICONFACEBOOK_H
#include <QString>
#include "../MCommon/Common.h"
#include <QRandomGenerator>
class GetIconFacebook{
private:
    static QString icon1;
    static QString icon2;
    static QString icon3;
    static QString icon4;
    static QString icon5;
    static QString icon6;
    static QString icon7;
    static QString icon8;
    static QString number;
    static QStringList lstKey;

    static QString GetNumber(const QString& input) {
        QString text;
        try {
            QString text2;
            QStringList list = QString("0|1|2|3|4|5|6|7|8|9").split('|');
            for (int i = 0; i < input.length(); ++i) {
                text2 = input[i];
                if (Common::IsNumber(text2)) {
                    text2 = list[QString(text2).toInt()];
                }
                text += text2;
            }
        } catch (...) {
            // Handle exceptions if necessary
        }
        return text;
    }


    static uint E63B250D(const QString& string_0) {
        uint num = 0U;
        if (!string_0.isEmpty()) {
            num = 2166136261U;
            for (int i = 0; i < string_0.length(); ++i) {
                num = (static_cast<uint>(string_0[i].unicode()) ^ num) * 16777619U;
            }
        }
        return num;
    }


    static QString GetIcon(const QString& type, QRandomGenerator& rd)
    {
        QString result;
        QStringList list;

        try {
            uint num = E63B250D(type.toStdString().c_str());

            if (num <= 2059200309) {
                if (num <= 312791236) {
                    switch (num) {
                    case 312791236:
                        if (type == "[r3]") {
                            list = icon3.split('|');
                            result = list[rd.bounded(list.size())];
                            return result;
                        }
                        return result;
                    case 311070023:
                        if (type == "[r8]") {
                            list = icon8.split('|');
                            result = list[rd.bounded(list.size())];
                            return result;
                        }
                        return result;
                    default:
                        return result;
                    }
                }
                switch (num) {
                case 380446165:
                    if (type == "[r6]") {
                        list = icon6.split('|');
                        result = list[rd.bounded(list.size())];
                        return result;
                    }
                    return result;
                case 313482784:
                    if (type == "[r7]") {
                        list = icon7.split('|');
                        result = list[rd.bounded(list.size())];
                        return result;
                    }
                    return result;
                case 2059200309:
                    if (type == "[t]") {
                        result = QDateTime::currentDateTime().toString("HH:mm:ss");
                        return result;
                    }
                    return result;
                default:
                    return result;
                }
            }
            if (num <= 3534241179) {
                switch (num) {
                case 3534241179:
                    if (type == "[r4]") {
                        list = icon4.split('|');
                        result = list[rd.bounded(list.size())];
                        return result;
                    }
                    return result;
                case 3135527781:
                    if (type == "[d]") {
                        result = QDateTime::currentDateTime().toString("dd/MM/yyyy");
                        return result;
                    }
                    return result;
                default:
                    return result;
                }
            }
            switch (num) {
            case 3600807202:
                if (type == "[r1]") {
                    list = icon1.split('|');
                    result = list[rd.bounded(list.size())];
                    return result;
                }
                return result;
            case 3600954297:
                if (type == "[r2]") {
                    list = icon2.split('|');
                    result = list[rd.bounded(list.size())];
                    return result;
                }
                return result;
            case 3601498750:
                if (type == "[r5]") {
                    list = icon5.split('|');
                    result = list[rd.bounded(list.size())];
                    return result;
                }
                return result;
            default:
                return result;
            }
        }
        catch (...) {
            return result;
        }
    }
public:
    static QString ProcessString(QString input) {
        QString text;
        try {
            QString text2;
            for (const QString& key : lstKey) {
                if (input.contains(key)) {
                    QStringList list = input.split(key);
                    for (int j = 0; j < list.size() - 1; ++j) {
                        text += list[j] + GetIcon(key, *QRandomGenerator::global());
                    }
                    text += list.last();
                    input = text;
                    text.clear();
                }
            }

            QRegularExpression regex("\\[n(.*?)\\]");
            QRegularExpressionMatchIterator matchIterator = regex.globalMatch(input);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                QStringList list2 = input.split(match.captured(0));
                for (int l = 0; l < list2.size() - 1; ++l) {
                    text += list2[l] + Common::createRandomNumber(match.captured(1).toInt());
                }
                text += list2.last();
                input = text;
                text.clear();
            }

            regex.setPattern("\\[s(.*?)\\]");
            matchIterator = regex.globalMatch(input);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                QStringList list3 = input.split(match.captured(0));
                for (int n = 0; n < list3.size() - 1; ++n) {
                    text += list3[n] + Common::createRandomString(match.captured(1).toInt());
                }
                text += list3.last();
                input = text;
                text.clear();
            }

            regex.setPattern("\\[q(.*?)\\]");
            matchIterator = regex.globalMatch(input);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                QStringList list4 = input.split(match.captured(0));
                for (int num2 = 0; num2 < list4.size() - 1; ++num2) {
                    text += list4[num2] + GetNumber(match.captured(1));
                }
                text += list4.last();
                input = text;
                text.clear();
            }
        } catch (...) {
            // Handle exceptions if necessary
        }
        return input;
    }
};

#endif // GETICONFACEBOOK_H
