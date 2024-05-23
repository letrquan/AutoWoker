#include "Common.h"
#include <QTextStream>
#include <QDateTime>
#include "../Form/downloaddialog.h"
#include "qtablewidget.h"
#include <QDir>
#include <QEventLoop>
#include <QTimer>
#include <unistd.h>
#include <windows.h>
#include "../MCommon/connector.h"
void Common::ExportError(const QException* ex, QString error){
    try {
        QFile file("log/log.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << "-----------------------------------------------------------------------------\n";
        out << "Date: " << QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss") << "\n";
        if (!error.isEmpty()) {
            out << "Error: " << error << "\n";
        }
        out << "\n";
        if (ex != nullptr) {
            out << "Type: " << typeid(*ex).name() << "\n";
            out << "Message: " << ex->what() << "\n";
            // Stack trace is not readily available in C++
        }
        file.close();
    } catch (...) {
    }
}
bool Common::IsNumber(QString pValue)
{
    if (pValue == "")
    {
        return false;
    }
    for (int i = 0; i < pValue.length(); i++)
    {
        if (!QChar(pValue[i]).isDigit())
        {
            return false;
        }
    }
    return true;
}

QString Common::convertToUnSign(QString s)
{
    s = s.normalized(QString::NormalizationForm_D);
    const QString diacriticLetters = "đĐ";
    const QString nonDiacriticLetters = "dD";
    for (int i=0; i<diacriticLetters.size(); i++)
    {
        s.replace(diacriticLetters[i], nonDiacriticLetters[i]);
    }
    return s;
}
void Common::DownloadFile(QString link){
    DownloadDialog down(link);
    down.show();
}

QString Common::RunCMD(const QString& cmd)
{
    try
    {
        QProcess process;
        process.setProgram("cmd.exe");
        process.setArguments({"/c", cmd});
        process.setReadChannel(QProcess::StandardOutput);
        process.start();
        process.waitForFinished();

        QByteArray outputData = process.readAllStandardOutput();
        QString text = QString::fromUtf8(outputData).trimmed(); // Convert to QString

        if (text.isEmpty())
        {
            return ""; // Return an empty string
        }

        return text;
    }
    catch (const std::exception& ex)
    {
        qWarning() << "Exception: " << ex.what(); // Print exception message (optional)
        return "";
    }
}
QString Common::Base64Decode(const QString& base64Encoded)
{
    // Convert the base64-encoded string to a QByteArray
    QByteArray base64Data = base64Encoded.toUtf8();
    QByteArray decodedData = QByteArray::fromBase64(base64Data);

    // Convert the decoded QByteArray back to a QString
    QString decodedString = QString::fromUtf8(decodedData);

    return decodedString;
}

bool Common::deleteDirectory(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) {
        return false; // No directory at path
    }

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs | QDir::Hidden);
    QFileInfoList fileList = dir.entryInfoList();

    foreach (const QFileInfo &fileInfo, fileList) {
        if (fileInfo.isDir()) {
            // Recursively delete directories
            if (!deleteDirectory(fileInfo.absoluteFilePath())) {
                return false;
            }
        } else {
            // Delete files
            if (!QFile::remove(fileInfo.absoluteFilePath())) {
                qDebug() << "Could not delete file:" << fileInfo.absoluteFilePath();
                return false;
            }
        }
    }

    // Now delete the now-empty directory
    return dir.rmdir(path);
}
bool Common::deleteFile(QString pathFile){
    try {
        QFile file(pathFile);
        return file.remove();
    } catch (...) {
    }
    return false;
}

void Common::DelayTime(double second){
    sleep(second);
}
void Common::CreateFolder(QString pathFolder){
    try {
        QDir dir(pathFolder);
        if(dir.exists()){
            dir.mkpath(".");
        }
    } catch (...) {
    }
}
void Common::ShowDialog(QDialog* dialog){
    try
    {
        dialog->setWindowFlags(dialog->windowFlags() | Qt::Tool);
        dialog->exec();
    }
    catch (...)
    {
        // Handle any exceptions that may occur
    }
}
void Common::ShowForm(QWidget* widget){
    try
    {
        widget->setWindowFlags(widget->windowFlags() | Qt::Tool);
        widget->show();
    }
    catch (...)
    {
        // Handle any exceptions that may occur
    }
}
QStringList Common::RemoveEmptyItems(const QStringList& lst) {
    QStringList list;
    for (const QString& item : lst) {
        QString text = item.trimmed();
        if (!text.isEmpty()) {
            list.append(text);
        }
    }
    return list;
}

void Common::SwapTableWidgetRows(QTableWidget* tableWidget, int oldRow, int newRow, int indexStart) {
    QString text;
    for (int i = indexStart; i < tableWidget->columnCount(); ++i) {
        text = tableWidget->item(oldRow, i)->text();
        tableWidget->item(oldRow, i)->setText(tableWidget->item(newRow, i)->text());
        tableWidget->item(newRow, i)->setText(text);
    }
}
bool Common::UpdateFieldToAccount(QString id, QString fieldName, QString fieldValue){
    bool result = false;
    try {
        QString text = "";
        if (fieldName == "pass")
        {
            text = ", pass_old=pass";
        }
        if (fieldName == "uid" && fieldValue.trimmed() == "")
        {
            return false;
        }
        if (fieldName == "cookie1" && fieldValue.trimmed() == "")
        {
            return false;
        }
        QString query = "update accounts set "+fieldName+" = '"+fieldValue.replace("'", "''")+"'" + text + " where id=" + id;
        if (Connector::getInstance().ExecuteNonQuery(query) > 0)
        {
            result = true;
        }
        result = false;
    } catch (...) {
    }
    return result;
}
