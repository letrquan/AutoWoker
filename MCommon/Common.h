#ifndef COMMON_H
#define COMMON_H
#include "RequestHandle.h"
#include "qcombobox.h"
#include <QString>
#include <QException>
#include <QFile>
#include <QProcess>
#include <QSqlTableModel>
#include <QDialog>
#include <QFileInfo>
#include "../maxcare/Language.h"
#include <QTableWidget>
#include "../Utils/Utils.h"
#include "qfuture.h"
#include "qtconcurrentrun.h"
#include "qtimer.h"
class Common{
public:
    static void ExportError(const QException* ex = nullptr, QString error ="");
    static bool IsNumber(QString pValue);
    static QString convertToUnSign(QString s);
    static QString RunCMD(const QString& cmd);
    static QString Base64Decode(const QString& base64Encoded);
    static void DownloadFile(QString link);
    static bool deleteDirectory(const QString &path);
    static void DelayTime(double second);
    static bool deleteFile(QString pathFile);
    static void CreateFolder(QString pathFolder);
    static bool UpdateFieldToAccount(QString id, QString fieldName, QString fieldValue);
    static void ShowDialog(QDialog *dialog);
    static QStringList RemoveEmptyItems(const QStringList& lst);
    static void ShowForm(QWidget* widget);
    static QStringList ShuffleList(QStringList lst);
    static void SwapTableWidgetRows(QTableWidget *tableWidget, int oldRow, int newRow, int indexStart = 1);
    static int GetIndexOfPositionApp(QList<int> &lstPosition);
    static void FillIndexPossition(QList<int> lstPossition, int indexPos);
    static bool ChangeIP(int typeChangeIP, int typeDcom, QString profileDcom, QString urlHilink, int iTypeHotspot, QString sLinkNord){
        bool result = false;
        QString text = "";
        try {
            switch (typeChangeIP) {
            case 0:{
                return true;
            }
            case 1:{
                QString text2 = CheckIP();

            }
            default:
                break;
            }
        } catch (...) {
        }
    }
    static QString ConvertSecondsToTime(int seconds) {
        if (seconds < 0) {
            return QStringLiteral("Invalid time (negative)");
        }

        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int secondsLeft = seconds % 60;

        QString timeString;
        if (hours > 0) {
            timeString = QString("%1:").arg(hours, 2, QChar('0'));
        }
        timeString += QString("%1:").arg(minutes, 2, QChar('0'));
        timeString += QString("%1").arg(secondsLeft, 2, QChar('0'));

        return timeString;
    }
    static QString CheckIP(){
        QString result = "";
        try
        {
            result = Utils::parseJsonString((new RequestHandle("", "", "", 0))->RequestGet("http://lumtest.com/myip.json"))["ip"].toString();
            return result;
        }
        catch(...)
        {
            return result;
        }
    }
    static bool IsVNName(QString ten)
    {
        ten = ten.trimmed();
        if (ten == "")
        {
            return false;
        }
        if (ten != ConvertToUnSign(ten))
        {
            return IsContainsVNChar(ten);
        }
        return false;
    }
    static QString ConvertToUnSign(const QString& s) {
        // Normalize the string to Form D (decomposed)
        QString input = s.normalized(QString::NormalizationForm_D);

        // Regular expression to match combining diacritical marks
        QRegularExpression regex("[\\p{Mn}]");

        // Remove diacritical marks
        QString result = input.remove(regex);

        // Replace specific characters
        result.replace(QStringLiteral("đ"), QStringLiteral("d"));
        result.replace(QStringLiteral("Đ"), QStringLiteral("D"));

        return result;
    }
    static bool IsContainsVNChar(const QString& text) {
        QString vnChars = " abcdeghiklmnopqrstuvxyABCDEGHIKLMNOPQRSTUVXYaAeEoOuUiIdDyY"
                          "áàạảãâấầậẩẫăắằặẳẵÁÀẠẢÃÂẤẦẬẨẪĂẮẰẶẲẴ"
                          "éèẹẻẽêếềệểễÉÈẸẺẼÊẾỀỆỂỄ"
                          "óòọỏõôốồộổỗơớờợởỡÓÒỌỎÕÔỐỒỘỔỖƠỚỜỢỞỠ"
                          "úùụủũưứừựửữÚÙỤỦŨƯỨỪỰỬỮ"
                          "íìịỉĩÍÌỊỈĨ"
                          "đĐ"
                          "ýỳỵỷỹÝỲỴỶỸ";

        QSet<QChar> vnCharSet = QSet<QChar>(vnChars.begin(), vnChars.end());

        for (const QChar& c : text) {
            if (!vnCharSet.contains(c)) {
                return false;
            }
        }
        return true;
    }

    static void CreateFile(QString pathFile){
        try
        {
            // Check if the file exists
            QFileInfo checkFile(pathFile);
            if (!checkFile.exists())
            {
                // Create the file
                QFile file(pathFile);
                if (!file.open(QIODevice::WriteOnly))
                {
                    qWarning() << "Failed to create file:" << pathFile;
                }
                file.close(); // Close the file after creating it
            }
        }
        catch (const std::exception &e)
        {
            qWarning() << "Exception caught:" << e.what();
        }
        catch (...)
        {
            qWarning() << "Unknown exception caught.";
        }
    }
    static QString CheckProxyNew(QString proxy, int typeProxy, int timeOut = 0){
        QString ip="";
        QStringList* list = new QStringList { "https://icanhazip.com", "https://api.myip.com/", "https://api64.ipify.org/", "http://v4v6.ipv6-test.com/api/myip.php/" };
        try {
            std::atomic<int> check(0);
            int count = list->count();
            QList<QFuture<void>> list2;
            QMutex mutex;
            for(int i = 0; i < count; i++){
                QString link = list->at(i);
                QFuture<void> thread = QtConcurrent::run([link, proxy, typeProxy, &ip, &check, &mutex]{
                    int tickCount = GetTickCount();
                    while(GetTickCount() - tickCount < 20000){
                        QString text = CheckProxyOneThread(link, proxy, typeProxy).toLower();
                        if (text.contains("html") || text.contains("cannot_connect") || text.contains("authenticated") || text.contains("maximum"))
                        {
                            ip = "";
                            break;
                        }
                        if (text != "")
                        {
                            ip = text;
                            break;
                        }
                    }
                    {
                        QMutexLocker lock(&mutex);
                        check++;
                    }
                });
                list2.append(thread);
            }
            while (check < count && ip == "")
            {
                QThread::sleep(1);
            }
            for(auto thread: list2){
                try {
                    thread.waitForFinished();
                } catch (...) {
                }
            }
        } catch (...) {
        }
        return ip.trimmed();
    }
    static QString CheckProxyOneThread(QString link, QString proxy, int typeProxy){
        QString text="";
        try {
            RequestHandle* requestHandle = new RequestHandle("", "", proxy, typeProxy);
            requestHandle->addHeader("Cache-Control", "no-cache");
            if(proxy != ""){
                requestHandle->setConnectionTimeout(5000);
            }
            text = requestHandle->RequestGet(link);
            if (link == "https://api.myip.com/") {
                QRegularExpression re("\"ip\":\"(.*?)\"");
                QRegularExpressionMatch match = re.match(text);
                if (match.hasMatch()) {
                    text = match.captured(1);
                    return text;
                }
            }
            return text;
        } catch (std::exception ex) {
            return text;
        }
    }
private:
    // static int getWidthScreen = Screen.PrimaryScreen.WorkingArea.Width;
};

#endif // COMMON_H
