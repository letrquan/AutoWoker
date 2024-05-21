#include "Base.h"
#include "SettingsTool.h"
#include "FileHelper.h"
QString Base::pathDataBase = GetPathDatabase();
QString Base::domain = NULL;
QString Base::softIndex = NULL;
QString Base::base64_anhmau = "/9j/4AAQSkZJRgABAgAAAQABAAD/7QCcUGhvdG9zaG9wIDMuMAA4QklNBAQAAAAAAIAcAmcAFGFaalJHblh2SmllZ1pTYWZTalhhHAIoAGJGQk1EMDEwMDBhOTkwMTAwMDBmMTAxMDAwMDM5MDIwMDAwNWEwMjAwMDA4NDAyMDAwMGJmMDIwMDAwMDIwMzAwMDAzMjAzMDAwMDU2MDMwMDAwODgwMzAwMDBmZjAzMDAwMP/bAEMABgQFBgUEBgYFBgcHBggKEAoKCQkKFA4PDBAXFBgYFxQWFhodJR8aGyMcFhYgLCAjJicpKikZHy0wLSgwJSgpKP/bAEMBBwcHCggKEwoKEygaFhooKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKP/CABEIADIAMgMAIgABEQECEQH/xAAaAAEAAwEBAQAAAAAAAAAAAAAAAQMFAgQG/8QAFQEBAQAAAAAAAAAAAAAAAAAAAQD/xAAVAQEBAAAAAAAAAAAAAAAAAAABAP/aAAwDAAABEQIRAAAB+5JS7vRDiPT5kCndc1tq7BzPP1wkoVK/Rrm0HG52vCnjFat1VohQVhxPKf/EAB0QAAICAgMBAAAAAAAAAAAAAAECAxAAEhEgMzH/2gAIAQAAAQUCpYmbDCeo+1P6Wg5ap/Toh2XGOzdIhqmMCpqOPfFULZHOSQ8VF59T9//EABQRAQAAAAAAAAAAAAAAAAAAAED/2gAIAQIRAT8BB//EABQRAQAAAAAAAAAAAAAAAAAAAED/2gAIAQERAT8BB//EAB0QAAIBBAMAAAAAAAAAAAAAAAEQIQARIDACUWH/2gAIAQAABj8CXVROwaAUTiFYvyoc1fihn//EAB8QAAEEAgMBAQAAAAAAAAAAAAEAESExECBRcaFBYf/aAAgBAAABPyHEwzOShxIIQxY3pIO8tpxOjDMOci3YaVS90RgL9w0ElhJRQjf1GQmQNk8jCj45ALA4TA08Y8+1/a//2gAMAwAAARECEQAAEA3owy+Lz2TJQ9PPLf/EABQRAQAAAAAAAAAAAAAAAAAAAED/2gAIAQIRAT8QB//EABcRAAMBAAAAAAAAAAAAAAAAAAARIBD/2gAIAQERAT8QHbx1/8QAIxABAAEDBAICAwAAAAAAAAAAAREAITEQIEFRcYFhkcHw8f/aAAgBAAABPxDQixlOXwVLvhsNIgIGEeNgguED96k9qPb+RsB1ACTU0RlBTrj8bBUKhGR6o5y6R5c0hFsBLTKsytPBxsCQqYAlaMOL0dTQkHCRSpSGBcPjW5UTE8vioQJ25X3q9O3CVeEi68+tP2vndZD2r//Z";
bool Base::isLam = false;
bool Base::isTuan = false;

QString Base::GetPathDatabase(){
    QDir dir;
    if(SettingsTool::GetSettings("configGeneral").GetValueBool("ckbDongBoMaxCare")&& dir.exists(SettingsTool::GetSettings("configGeneral").GetValue("txtPathMaxCare"))){
        return SettingsTool::GetSettings("configGeneral").GetValue("txtPathMaxCare");
    }
    return FileHelper::GetPathToCurrentFolder();
}

QString Base::GetLanguage(){
    QString text = SettingsTool::GetSettings("configGeneral").GetValue("Language");
    if (text == "")
    {
        text = ((!(GetServer() == "1")) ? "EN" : "VN");
    }
    return text;
}

QString Base::GetServer(){
    return SettingsTool::GetSettings("settingLogin").GetValue("Server", "1");
}

void Base::SetLanguage(QString language)
{
    SettingsTool::GetSettings("configGeneral").Update("Language", language);
    SettingsTool::SaveSettings("configGeneral");
}

bool Base::CheckPassword()
{
    return true;
}

QMap<QString, QString> Base::GetServers()
{
    QMap<QString, QString> servers;
    servers.insert("1", "MaxCare VietNam");
    servers.insert("2", "MaxCare English");
    servers.insert("3", "MaxCare Cambodia");
    servers.insert("4", "MaxCare Thailand");
    return servers;
}

QString Base::GetDomain()
{
    domain = "https://farm-api.giau.xyz/api/v1/";
    return domain;
}
QString Base::GetSoftIndex()
{
    QString server = GetServer();
    if(server == "2"){
        softIndex ="61";
    }else{
        if(server == "3" || server == "4"){
            softIndex = "1";
        }else{
            softIndex ="11";
        }
    }
    return softIndex;
}
