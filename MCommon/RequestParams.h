#ifndef REQUESTPARAMS_H
#define REQUESTPARAMS_H
#include <QVariant>
#include <QList>
#include <QString>
#include <QPair>

class RequestParams : public QList<QPair<QString, QString>>
{
public:
    void set(const QString& paramName, const QVariant& value)
    {
        if (paramName.isNull())
            throw std::invalid_argument("Parameter name cannot be null.");

        if (paramName.isEmpty())
            throw std::invalid_argument("Parameter name cannot be empty.");

        QString valueString = value.toString().isEmpty() ? QString() : value.toString();
        append(QPair<QString, QString>(paramName, valueString));
    }
};

#endif // REQUESTPARAMS_H
