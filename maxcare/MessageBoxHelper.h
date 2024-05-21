#ifndef MESSAGEBOXHELPER_H
#define MESSAGEBOXHELPER_H
#include <QObject>
#include <QMessageBox>
#include "../maxcare/Language.h"
class MessageBoxHelper{
public:
    static void Show(const QVariant& object, int type =1){
        QMessageBox::Icon icon = QMessageBox::NoIcon;
        switch (type) {
        case 1:
            icon = QMessageBox::Information;
            break;
        case 2:
            icon = QMessageBox::Critical;
            break;
        case 3:
            icon = QMessageBox::Warning;
            break;
        case 4:
            icon = QMessageBox::Warning;
            break;
        }

        QString message = Language::GetValue(object.toString());
        QMessageBox msgBox;
        msgBox.setIcon(icon);
        msgBox.setText(message);
        msgBox.setWindowTitle("Autoworker PC");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    static QMessageBox::StandardButton ShowYesNo(const QString& content)
    {
        // Display the message box and return the user's response
        return QMessageBox::question(nullptr, "Autoworker PC", content, QMessageBox::Yes | QMessageBox::No);
    }
};

#endif // MESSAGEBOXHELPER_H
