#ifndef SETTINGSTOOL_H
#define SETTINGSTOOL_H
#include <QMap>
#include "../MCommon/json_settings.h"
#include "../Utils/Utils.h"
#include <QDir>
class SettingsTool {
private:
    static QMap<QString, JSON_Settings> settings;
    static void LoadSettings(QString key);

public:
    // Retrieves the JSON_Settings object for the given key, creating it if it doesn't exist
    static JSON_Settings& GetSettings(QString key);
    static void SaveSettings(QString key);
    static QString GetPathProfile(){
        QString text = settings["configGeneral"].GetValue("txbPathProfile");
        if (!text.contains('\\'))
        {
            text = Utils::GetPathToCurrentFolder() + "\\" + ((text == "") ? "profiles" : text);
        }
        QDir dir(text);
        if (!dir.exists())
        {
            return Utils::GetPathToCurrentFolder() + "\\profiles";
        }
        return text;
    }
    // static QString GetPathProfile(){
    //     QString text = settings["configGeneral"].
    // }

    // Loads settings for a specific key (reloads if already exists)

};



#endif // SETTINGSTOOL_H
