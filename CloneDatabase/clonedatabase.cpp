#include "clonedatabase.h"
#include <QFileInfo>
#include "../MCommon/Common.h"
#include "connectsqlite.h"
#include <QSqlQuery>
#include <QSqlRecord>
CloneDatabase::CloneDatabase() {}

void CloneDatabase::Excute(const QString& pathDb) {
    QString localAppData = QString::fromLocal8Bit(std::getenv("LocalAppData"));
    Common::CreateFolder(localAppData + "\\database");
    QString fileName = QFileInfo(pathDb).fileName();
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    QString filePath = localAppData + "\\database\\" + timestamp + "_" + fileName;

    std::unique_ptr<ConnectSqlite> sourceDb = std::make_unique<ConnectSqlite>(pathDb);
    sourceDb->CheckConnectServer();

    std::unique_ptr<ConnectSqlite> targetDb = std::make_unique<ConnectSqlite>(filePath);
    targetDb->CheckConnectServer();

    QSqlQuery schemaQuery = sourceDb->ExecuteQuery("SELECT name, sql FROM sqlite_master WHERE type='table';");
    QList<QString> tableNames;

    while (schemaQuery.next()) {
        QString tableName = schemaQuery.value(0).toString();
        if (tableName == "sqlite_sequence") {
            continue; // Skip the internal SQLite sequence table
        }
        QString createTableSql = schemaQuery.value(1).toString();
        targetDb->ExecuteNonQuery(createTableSql);
        tableNames.append(tableName);
    }

    for (const QString& tableName : tableNames) {
        if (tableName == "interacts") {
            continue; // Skip copying data for the 'interacts' table
        }
        // Constructing column names list
        QSqlQuery columnQuery = sourceDb->ExecuteQuery("PRAGMA table_info(" + tableName + ")");
        QStringList columnNames;
        while (columnQuery.next()) {
            columnNames << columnQuery.value(1).toString(); // Column name is in the second position
        }

        // Prepare to copy data
        QString insertSql = "INSERT INTO " + tableName + "(" + columnNames.join(",") + ") VALUES ";
        QSqlQuery dataQuery = sourceDb->ExecuteQuery("SELECT * FROM " + tableName);
        while (dataQuery.next()) {
            QStringList values;
            for (int i = 0; i < dataQuery.record().count(); ++i) {
                values << "'" + dataQuery.value(i).toString() + "'";
            }
            targetDb->ExecuteNonQuery(insertSql + "(" + values.join(",") + ");");
        }
    }
}
