#ifndef COMMONCHROME_H
#define COMMONCHROME_H
#include "qregularexpression.h"
#include <QString>

class CommonChrome{
public:
    static bool CheckStringContainKeyword(const QString &content, const QStringList &lstKeyword) {
        for (const QString &keyword : lstKeyword) {
            QRegularExpression re(keyword);
            if (re.match(content).hasMatch() || content.contains(keyword)) {
                return true;
            }
        }
        return false;
    }
};

#endif // COMMONCHROME_H
