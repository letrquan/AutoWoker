#include "json_settings.h"
#include "qmutex.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDir>

JSON_Settings::JSON_Settings(QString jsonStringOrPathFile, bool isJsonString) {
    if(isJsonString){
        if(jsonStringOrPathFile.trimmed() == ""){
            jsonStringOrPathFile = "{}";
        }
        QJsonDocument Document = QJsonDocument::fromJson(jsonStringOrPathFile.toUtf8());
        JSON = Document.object();
        return;
    }
    try {
        PathFileSetting = "settings\\"+jsonStringOrPathFile+".json";
        QDir dir("settings");
        if (!dir.exists()) {
            if (!dir.mkpath(".")) {
                qDebug() << "Failed to create the directory: settings";
                return;
            }
        }
        if(!QFile::exists(PathFileSetting)){
            QFile file(PathFileSetting);
            if(file.open(QIODevice::WriteOnly)){
                file.write("{}");
                file.close();
            }else{
                qDebug() << "Failed to create the file: " << PathFileSetting;
            }

        }
        QFile file(PathFileSetting);
        if(file.open(QIODevice::ReadOnly)){
            QByteArray Bytes = file.readAll();
            file.close();
            QJsonParseError fError;
            QJsonDocument Document = QJsonDocument::fromJson(Bytes, &fError);
            if(fError.error != QJsonParseError::NoError){
                qDebug() << "Error in Json Data: " << fError.errorString();
                return;
            }
            if(Document.isObject()){
                JSON = Document.object();
            }
        }
    } catch (...) {
    }
}

JSON_Settings::JSON_Settings(){}

void JSON_Settings::Save(QString pathFileSetting){
    try
    {
        if (pathFileSetting == "")
        {
            pathFileSetting = PathFileSetting;
        }
        QFile file(pathFileSetting);
        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
            QJsonDocument doc(JSON);
            file.write(doc.toJson());
            file.close();
        }
    } catch (...) {

    }
}

void JSON_Settings::Update(QString key, QVariant value){
    try
    {
        if(JSON.contains(key)){
            JSON[key] = value.toString();
        }else{
            JSON.insert(key,value.toString());
        }
    } catch (...) {

    }
}

QString JSON_Settings::GetValue(QString key, QString valueDefault){
    QString result = valueDefault;
    try {
        if(JSON[key] != NULL){
            result = JSON[key].toString();

        }
    } catch (...) {
    }
    return result;
}

bool JSON_Settings::ContainsKey(QString key){
    return JSON.contains(key);
}

QStringList JSON_Settings::GetValueList(QString key, int typeSplitString){
    QStringList list;
    try {
        QString value = GetValue(key);
        if (typeSplitString != 0) {
            // Split using custom delimiter
            list = value.split("\n|\n", Qt::SkipEmptyParts);
        } else {
            // Split using newline as the delimiter
            list = value.split('\n', Qt::SkipEmptyParts);
        }
    } catch (...) {
    }
    return list;
}

bool JSON_Settings::GetValueBool(QString key, bool valueDefault){
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    bool result =valueDefault;
    try {
        if(JSON.contains(key)){
            result = stringToBool(JSON[key].toString());
        }
    } catch (...) {
    }
    return result;
}
QString JSON_Settings::GetFullString(){
    QString result = "";
    try {
        QJsonDocument doc(JSON);
        result = QString(doc.toJson(QJsonDocument::Compact));
    } catch (...) {
    }
    return result;
}
bool JSON_Settings::stringToBool(const QString& str) {
    // Normalize the string
    QString normalizedStr = str.trimmed().toLower();

    // Check for "true" and "false" (case-insensitive)
    if (normalizedStr == "true" || normalizedStr == "1") {
        return true;
    } else if (normalizedStr == "false" || normalizedStr == "0") {
        return false;
    }

    // Default to false or throw an exception if the value is invalid
    qWarning() << "Invalid boolean string:" << str;
    return false;
}

int JSON_Settings::GetValueInt(QString key, int valueDefault){
    int result = valueDefault;
    try {
        auto check = JSON[key];
        int i = JSON[key].toString().toInt();
        if(i!=0){
            result =i;
        }
    } catch (...) {
    }
    return result;
}
