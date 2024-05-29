#include "commonsql.h"
#include "../maxcare/Language.h"
#include "connector.h"
#include <QSqlRecord>
#include "../Utils/Utils.h"
CommonSQL::CommonSQL() {}

AutoTable* CommonSQL::GetAllFilesFromDatabase(bool isShowAll, bool notAW){
    AutoTable* model;
    try
    {
        QString aw = "";
        if (notAW)
        {
            aw = "and aw=0";
        }
        QString text;
        if (isShowAll)
        {
            text = "select id, name, STT from files where active=1 "+aw+" UNION SELECT -1 AS id, '" + Language::GetValue("[Tất cả thư mục]") + "' AS name, -1 AS STT UNION SELECT 999999 AS id, '" + Language::GetValue("[Chọn nhiều thư mục]") + "' AS name, 999999 AS STT ORDER BY STT";
        }
        else
        {
            text = "select id, name from files where active=1  "+aw+" ORDER BY STT";
        }

        model = Connector::getInstance().ExecuteQuery(text);
    }
    catch (...)
    {
        qDebug() << "Error occurred while executing the database query.";
    }
    return model;
}

AutoTable* CommonSQL::GetAllInfoFromAccount(QList<QString> lstIdFile, bool isGetActive,bool foraw){
    AutoTable* result;
    try {
        QString text = "";
        if(lstIdFile.count()!= 0 && !lstIdFile.isEmpty()){
            text = "where idfile IN (" + lstIdFile.join(",") + ") AND active=" + QString::number(isGetActive ? 1 : 0);
        }else{
            text = "where active=" + QString::number(isGetActive ? 1 : 0);
        }
        if(foraw){
            text += " AND foraw=1";
        }
        QString query = "SELECT '-1' as id, '" + Language::GetValue("[Tất cả tình trạng]") + "' AS name UNION select DISTINCT '0' as id,info from accounts " + text + " ORDER BY id ASC";
        result = Connector::getInstance().ExecuteQuery(query);
    } catch (...) {
    }
    return result;
}

bool CommonSQL::CheckColumnIsExistInTable(QString table, QString column){
    bool result =Connector::getInstance().ExecuteScalar("SELECT COUNT(*) AS count FROM pragma_table_info('"+table+"') WHERE name='"+column+"'") > 0;
    return result;
}
bool CommonSQL::CheckExistTable(QString table){
    return Connector::getInstance().ExecuteScalar("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='" + table + "';")>0;
}

bool CommonSQL::AddColumnsIntoTable(QString table, QString columnName, int typeColumnData){
    bool result = false;
    try {
        QString type = (typeColumnData == 0) ? "INT" : "TEXT";
        if(Connector::getInstance().ExecuteNonQuery("ALTER TABLE {table} ADD COLUMN '"+columnName+ "'" + type +";")>0){
            result =true;
            return result;
        }
    } catch (...) {
        return result;
    }
    return result;
}

AutoTable* CommonSQL::GetIdStatus(){
    AutoTable* result;
    try {
        QString query = "SELECT id, status FROM accounts";
        result = Connector::getInstance().ExecuteQuery(query);
        return result;
    } catch (...) {
    }
    return result;
}
AutoTable* CommonSQL::GetAllFilesFromDatabaseForBin(bool isShowAll){
    AutoTable* result;
    try {
        QString text = "";
        text = (isShowAll ? ("select id, name from files WHERE id IN (SELECT DISTINCT idfile FROM accounts WHERE active=0) UNION SELECT -1 AS id, '" + Language::GetValue("[Tất cả thư mục]") + "' AS name UNION SELECT 999999 AS id, '" + Language::GetValue("[Chọn nhiều thư mục]") + "' AS name ORDER BY id ASC") : "select id, name from files WHERE id IN (SELECT DISTINCT idfile FROM accounts WHERE active=0)");
        result = Connector::getInstance().ExecuteQuery(text);
        return result;
    } catch (...) {
        return result;
    }
}
AutoTable* CommonSQL::GetAccFromFile(QList<QString>* lstIdFile, QString info, bool isGetActive){
    AutoTable* result = nullptr;
    try {
        QString text = "WHERE ";
        QString text2 =  ((!lstIdFile->isEmpty() && lstIdFile->count() > 0) ? ("t1.idFile IN (" + lstIdFile->join(",") + ")") : "");
        if(text2 != ""){
            text = text+text2+" AND ";
        }
        QString text3 = ((info != "") ? ("t1.info = '" + info + "'") : "");
        if(text3 != ""){
            text = text + text3 + " AND ";
        }
        QString text4 = "t1.active = '"+QString::number((isGetActive ? 1 : 0))+"'";
        text+=text4;
        QString query = "SELECT t1.*, t2.name AS nameFile FROM accounts t1 JOIN files t2 ON t1.idfile=t2.id " + text + " ORDER BY t1.idfile";
        result = Connector::getInstance().ExecuteQuery(query);
    } catch (...) {
    }
    return result;
}

QString CommonSQL::ConvertToSqlInsertAccount(QString& uid, QString& pass, const QString& token, const QString& cookie, const QString& email, QString& name, const QString& friends, const QString& groups, const QString& birthday, const QString& gender, const QString& info, const QString& fa2, const QString& idFile, const QString& passMail, const QString& useragent, const QString& proxy, const QString& create, const QString& mailKp)
{
    QString text;
    try
    {
        text = "('"+uid.replace("'", "''")+"','"+pass.replace("'", "''")+"','"+token+"','"+cookie+"','"+email+"','"+name.replace("'", "''")+"','"+friends+"','"+groups+"','"+birthday+"','"+gender+"','"+info+"','"+fa2+"','"+idFile+"','"+passMail+"','"+useragent+"','"+proxy+"','"+create+"','"+QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss")+"','"+mailKp+"',1)";
        return text;
    }
    catch (...)
    {
        return QString();
    }
}
QList<QString> CommonSQL::ConvertToSqlInsertAccount(const QList<QString>& lstSqlStatement)
{
    QList<QString> list;
    try
    {
        int num = 100;
        int num2 = static_cast<int>(std::ceil(static_cast<double>(lstSqlStatement.size()) / num));
        QString text;
        for (int i = 0; i < num2; ++i)
        {
            QStringList range = lstSqlStatement.mid(num * i, (num * i + num <= lstSqlStatement.size()) ? num : (lstSqlStatement.size() % num));
            text = "INSERT INTO accounts(uid,pass,token,cookie1,email,name,friends,groups,birthday,gender,info,fa2,idfile,passmail,useragent,proxy,dateCreateAcc,dateImport,mailrecovery,active) VALUES " + range.join(",");
            list.append(text);
        }
        return list;
    }
    catch (...)
    {
        return list;
    }
}

bool CommonSQL::CheckExitsFile(QString name)
{
    return Connector::getInstance().ExecuteScalar("SELECT COUNT(*) FROM files WHERE name='" + name + "' AND active=1;") > 0;
}
bool CommonSQL::InsertFileToDatabase(QString namefile,bool aw)
{
    bool result = true;
    try
    {
        int num = Connector::getInstance().ExecuteScalar("SELECT MAX(STT) FROM files");
        QString query = "INSERT INTO files (name, createddate, active, STT,aw) values('" + namefile + "','" + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss") + "',1," + QString::number(num + 1) + ",0)";

        if (aw)
        {
            query = "INSERT INTO files (name, createddate, active, STT,aw) values('" + namefile + "','" + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss") + "',1," + QString::number(num + 1) + ",1)";
        }
        Connector::getInstance().ExecuteQuery(query);
        return result;
    }
    catch(...)
    {
        return false;
    }
}

bool CommonSQL::UpdateThuTuThuMuc(const QString& id1, const QString& id2) {
    bool result = false;
    try {
        AutoTable* queryResult1 = Connector::getInstance().ExecuteQuery("SELECT STT FROM files WHERE id = " + id1);
        AutoTable* queryResult2 = Connector::getInstance().ExecuteQuery("SELECT STT FROM files WHERE id = " + id2);

        if (!queryResult1 || !queryResult2 || queryResult1->rowCount() == 0 || queryResult2->rowCount() == 0) {
            return result;
        }

        QString text = queryResult1->record(0).value("STT").toString();
        QString text2 = queryResult2->record(0).value("STT").toString();

        QString query1 = "UPDATE files SET STT = " + text2 + " WHERE id = " + id1;
        QString query2 = "UPDATE files SET STT = " + text + " WHERE id = " + id2;

        if (Connector::getInstance().ExecuteNonQuery(query1) > 0) {
            if (Connector::getInstance().ExecuteNonQuery(query2) > 0) {
                result = true;
                return result;
            }
            return result;
        }
        return result;
    } catch (...) {
        return result;
    }
}


bool CommonSQL::UpdateMultiFieldToAccount(QString id, QString lstFieldName, QString lstFieldValue, bool isAllowEmptyValue){
    bool result = false;
    try
    {
        if (lstFieldName.split('|').length() == lstFieldValue.split('|').length())
        {
            int num = lstFieldName.split('|').length();
            QString text = "";
            for (int i = 0; i < num; i++)
            {
                if (isAllowEmptyValue || !(lstFieldValue.split('|')[i].trimmed() == ""))
                {
                    text = text + lstFieldName.split('|')[i] + "='" + lstFieldValue.split('|')[i].replace("'", "''") + "',";
                }
            }
            text = Utils::trimEnd(text,',');
            QString query = "update accounts set " + text + " where id=" + id;
            result = Connector::getInstance().ExecuteNonQuery(query) > 0;
            return result;
        }
        return result;
    }
    catch(...)
    {
        return result;
    }
}
