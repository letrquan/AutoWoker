#ifndef JSON_SETTINGS_H
#define JSON_SETTINGS_H
#include <QJsonObject>
#include <QString>

class JSON_Settings
{
public:
    JSON_Settings(QString jsonStringOrPathFile, bool isJsonString = false);
    JSON_Settings();
    void Save(QString pathFileSetting = "");
    void Update(QString key, QVariant value);
    QString GetValue(QString key, QString valueDefault ="");
    bool ContainsKey(QString key);
    QStringList GetValueList(QString key, int typeSplitString = 0);
    bool GetValueBool(QString key, bool valueDefault = false);
    QString GetFullString();
    bool stringToBool(const QString& str);
    int GetValueInt(QString key, int valueDefault = 0);
private:
    QString PathFileSetting;
    QJsonObject JSON;
};

#endif // JSON_SETTINGS_H
