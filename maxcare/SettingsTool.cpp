#include "SettingsTool.h"

QMap<QString, JSON_Settings> SettingsTool::settings;

JSON_Settings& SettingsTool::GetSettings(QString key) {
    if(!settings.contains(key)){
        settings.insert(key,JSON_Settings(key));
    }
    return settings[key];
}


void SettingsTool::SaveSettings(QString key)
{
    if (settings.contains(key))
    {
        settings[key].Save() ;
    }
    LoadSettings(key);
}

void SettingsTool::LoadSettings(QString key) {
    if(settings.contains(key)){
        settings[key] = JSON_Settings(key) ;
    }else{
        settings.insert(key, JSON_Settings(key));
    }
}
