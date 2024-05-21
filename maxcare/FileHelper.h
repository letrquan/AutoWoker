#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QCoreApplication>
class FileHelper{
public:
    static QString GetPathToCurrentFolder(){
        return  QCoreApplication::applicationDirPath();
    }
};

#endif // FILEHELPER_H
