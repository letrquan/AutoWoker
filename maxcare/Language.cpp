#include "Language.h"
#include "../MCommon/json_settings.h"
#include "../MCommon/Common.h"
QString Language::GetValue(QString key){
    QString text = "";
    if(Base::GetLanguage() == "VN"){
        return key;
    }
    if(key ==""){
        return key;
    }
    if(false){
        text = JSON_Settings("configLanguage").GetValue(key);
        {
            text = key;
            if (key.trimmed() != "" && !Common::IsNumber(key.trimmed()) && key.trimmed() != Common::convertToUnSign(key.trimmed()))
            {
                try
                {
                    QFile file("settings\\\\configLanguage.txt");
                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << key << "\r\n";
                        file.close();
                    }

                }
                catch(...)
                {
                }
            }
        }
    }else{
        if(text == ""){
            text = key;
        }
    }
    return text;
}

void Language::SetLanguage(QWidget* control){
    QList<QWidget*> list = GetAllControl(control);
    for(QWidget* var:list){
        QTableWidget* tableWidget = qobject_cast<QTableWidget*>(var);
        if(tableWidget){
            // for(QTableWidget widget:tableWidget.){

            // }
        }
    }
}

QList<QWidget*> Language::GetAllControl(QWidget* parent) {
        QList<QWidget*> widgets;
        if (parent) {
            // Add the parent widget to the list
            widgets.append(parent);

            // Recursively add all child widgets to the list
            foreach(QWidget* child, parent->findChildren<QWidget*>()) {
                widgets.append(GetAllControl(child));
            }
        }
        return widgets;
}
