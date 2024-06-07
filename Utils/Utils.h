#ifndef UTILS_H
#define UTILS_H
#include "qjsondocument.h"
#include "qjsonobject.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTableWidget>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <windows.h>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "../Table/customtablemodel.h"
class Utils {
public:
    static bool ValidateTcpPort(int port)
    {
        if (port < 1 || port > 65535)
        {
            return false;
        }

        return true;
    }
    static bool isNumber(const QString &str) {
        bool isNumeric;
        str.toDouble(&isNumeric);
        return isNumeric;
    }
    static bool isConnectedToInternet() {
        QNetworkAccessManager nam;
        QNetworkRequest req(QUrl("http://www.google.com"));
        QNetworkReply* reply = nam.get(req);

        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        bool isConnected = (reply->error() == QNetworkReply::NoError);
        reply->deleteLater();
        return isConnected;
    }
    static int GetIndexByColumnHeader(QTableView* dgv, QString colHeader) {
        if (!dgv) {
            return -1;  // Return -1 if the QTableView pointer is null
        }

        ;
        if (!dgv->model()) {
            return -1;  // Return -1 if the model is null
        }

        QHeaderView* header = dgv->horizontalHeader();
        if (!header) {
            return -1;  // Return -1 if the header is null
        }

        for (int i = 0; i < dgv->model()->columnCount(); ++i) {
            QString headerData = dgv->model()->headerData(i, Qt::Horizontal).toString();
            if (headerData == colHeader) {
                return i;  // Return the index if the header matches
            }
        }

        return -1;  // Return -1 if no matching header is found
    }
    static int GetIndexByColumnHeader(QTableWidget dgv, QString colHeader){
        int col=-1;
        for (int i = 0; i < dgv.columnCount(); ++i) {
            QTableWidgetItem *headerItem = dgv.horizontalHeaderItem(i);
            if (headerItem != nullptr && headerItem->text() == colHeader) {
                col = i;
            }
        }
        return col;
    }
    static bool isRunningAsAdmin() {
        BOOL fIsRunAsAdmin = FALSE;
        PSID pAdministratorsGroup = NULL;

        SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
        if (AllocateAndInitializeSid(
                &NtAuthority, 2,
                SECURITY_BUILTIN_DOMAIN_RID,
                DOMAIN_ALIAS_RID_ADMINS,
                0, 0, 0, 0, 0, 0,
                &pAdministratorsGroup)) {
            CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin);
            FreeSid(pAdministratorsGroup);
        }

        return fIsRunAsAdmin;
    }

    static QVariant getDataAt(QTableView *tableView, int row, int col) {
        // Get the model associated with the QTableView
        QAbstractItemModel *model = tableView->model();

        // Check if the model is not null
        if (model) {
            // Create an index for the specified row and column
            QModelIndex index = model->index(row, col);

            // Access and return the data at the specified index
            return model->data(index);
        } else {
            qDebug() << "No model is set on the QTableView.";
            return QVariant();
        }
    }
    static bool writeTextToFile(const QString &fileName, const QString &text)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Could not open file" << fileName << "for writing";
            return false;
        }

        QTextStream out(&file);
        out << text;

        file.close();
        return true;
    }
    static QString getMachineName() {
        return QSysInfo::machineHostName();
    }
    static QString getPathToCurrentFolder()
    {
        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        QString executablePath = QString::fromLocal8Bit(path);
        QFileInfo fileInfo(executablePath);
        return fileInfo.absolutePath();
    }

    static bool writeAllLines(const QString &filePath, QList<QString> lines)
    {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Could not open file" << filePath << "for writing";
            return false;
        }

        QTextStream out(&file);
        for (const QString &line : lines)
        {
            out << line << "\n";
        }

        file.close();
        return true;
    }
    static QString readAllText(const QString &filePath)
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Cannot open file for reading:" << filePath;
            return {};
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Split the content by "\r\n" and "\n", and remove empty entries
        return content;
    }
    static QString trimEnd(const QString &str, QChar ch)
    {
        int end = str.length();
        while (end > 0 && str[end - 1] == ch)
        {
            --end;
        }
        return str.left(end);
    }
    static QString runCommand(const QString& command) {
        QProcess process;
        process.start(command);
        process.waitForFinished();
        return QString::fromLocal8Bit(process.readAllStandardOutput()).trimmed();
    }

    static QString getProcessorId() {
        return runCommand("wmic cpu get ProcessorId /value").split("=")[1].trimmed();
    }

    static QString getMotherboardSerialNumber() {
        return runCommand("wmic baseboard get SerialNumber /value").split("=")[1].trimmed();
    }

    static QString getSystemDriveSerialNumber() {
        return runCommand("wmic diskdrive where index=0 get SerialNumber /value").split("=")[1].trimmed();
    }

    static QString buildDeviceId() {
        QString deviceId = getMachineName() + "-" +
                           getProcessorId() + "-" +
                           getMotherboardSerialNumber() + "-" +
                           getSystemDriveSerialNumber();
        return deviceId;
    }
    static bool isCellCheckBox(QTableView* tableView, int row, int column) {
        QModelIndex index = tableView->model()->index(row, column);
        QVariant data = tableView->model()->data(index, Qt::CheckStateRole);
        return data.isValid();
    }
    static void changeRowColor(QTableView* tableView, int row, QColor color) {
        CustomTableModel* model = qobject_cast<CustomTableModel*>(tableView->model());
        if (model) {
            model->setRowColor(row, color);  // Example usage
        }
    }
    static QJsonObject parseJsonString(const QString& jsonString) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            return jsonResponse.object();
        } else {
            qDebug() << "Failed to parse JSON string.";
            return QJsonObject();
        }
    }
};

#endif // UTILS_H
