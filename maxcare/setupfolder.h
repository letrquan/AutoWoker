#ifndef SETUPFOLDER_H
#define SETUPFOLDER_H
#include <QString>
class SetupFolder
{
public:
    SetupFolder();
    static QString GetUseragentIPhone();
    static void StartApplication();
    static void CreateBaseFolder();
private:
    static QStringList userAgents;
    static void* getUseragentIphone; // Function pointer
    static void CheckDataBase();
};

#endif // SETUPFOLDER_H
