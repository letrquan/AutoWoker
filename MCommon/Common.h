#ifndef COMMON_H
#define COMMON_H
#include "RequestHandle.h"
#include <QString>
#include <QException>
#include <QFile>
#include <QProcess>
#include <QSqlTableModel>
#include <QDialog>
#include <QFileInfo>
#include <QTableWidget>
#include "../Utils/Utils.h"
#include "qfuture.h"
#include "qlibrary.h"
#include "qscreen.h"
#include "qtconcurrentrun.h"
#include "../maxcare/SettingsTool.h"
#include <Windows.h>
class Common{
public:
    typedef void* (*RandomStringFunc)(const char*, const char*);
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
    static QString CheckIPP(QString string_0)
    {
        QString text;
        try
        {
            text = (new RequestHandle("", "", "", 0))->RequestGet(string_0);
        }
        catch(...)
        {
            text = nullptr;
        }
        return text;
    }
    static bool smethod_28(const QString& string_0) {
        if (string_0.isEmpty()) {
            return false;
        } else {
            for (const QChar& c : string_0) {
                if (!c.isDigit()) {
                    return false;
                }
            }
            return true;
        }
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
    static QString CheckProxy(QString proxy, int typeProxy, int timeOut = 0){
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
                        QString text = CheckProxyOneThread(link, proxy, typeProxy);
                        if (text != "" && !text.contains("html"))
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
    static QString CreateRandomString(int length, QString typeRandom){
        QLibrary library("main");

        // Check if the library is loaded
        if (library.load()) {
            RandomStringFunc randomString = (RandomStringFunc)library.resolve("RandomString");
            if (randomString) {
                return Go2C(randomString(C2Go(QString::number(length)), C2Go(typeRandom)));
            }
        }
        return "";
    }
    static QString Go2C(void* data) {
        try {
            // Convert char* to QString assuming the data is ANSI encoded
            return QString::fromLocal8Bit(static_cast<char*>(data));
        } catch (...) {
            // Catch all exceptions (although not typically done in C++)
            return QString("");
        }
    }
    static QByteArray C2Go(const QString &input) {
        return input.toUtf8();
    }
    static QString GetTotp(QString string_0, int type = 0){
        QString text = "";
        try {
            string_0 = string_0.replace(" ", "").trimmed();
            QString text2 = "http://app.minsoftware.xyz/api/2fa1?secret=" + string_0;
            QString text3 = "http://2fa.live/tok/" + string_0;
            int i = 0;
            while (i < 5){
                text = "";
                try
                {
                    QString text4 = Common::CheckIPP(text3);
                    if (text4.contains("token"))
                    {
                        auto jobject = Utils::parseJsonString(text4);
                        text = jobject["token"].toString().trimmed();
                    }
                }
                catch (QException ex)
                {
                    Common::ExportError(&ex, text3);
                }
                try
                {
                IL_8F:
                    if (text.trimmed() == "")
                    {
                        text = Common::CheckIPP(text2);
                    }
                }catch (QException ex2)
                {
                    Common::ExportError(&ex2, text2);
                }
                if (!(text != "") || !Common::smethod_28(text))
                {
                    Common::DelayTime(1.0);
                    i++;
                    continue;
                }
                for (int j = text.length(); j < 6; j++)
                {
                    text = "0" + text;
                }
                break;
            }
        } catch (...) {
        }
        return text;
    }
    static QPoint GetPointFromIndexPosition(int indexPos, int column, int row){
        if (SettingsTool::GetSettings("configChrome").GetValueInt("width") == 0) {
            SettingsTool::GetSettings("configChrome").Update("width", getWidthScreen);
            SettingsTool::GetSettings("configChrome").Update("heigh", getHeightScreen);
            SettingsTool::SaveSettings("configChrome");
        }
        getWidthScreen = SettingsTool::GetSettings("configChrome").GetValueInt("width");
        getHeightScreen = SettingsTool::GetSettings("configChrome").GetValueInt("heigh");

        QPoint result;
        while (indexPos >= column * row) {
            indexPos -= column * row;
        }

        switch (row) {
        case 1:
            result.setY(0);
            break;
        case 2:
            if (indexPos < column) {
                result.setY(0);
            } else if (indexPos < column * 2) {
                result.setY(getHeightScreen / 2);
                indexPos -= column;
            }
            break;
        case 3:
            if (indexPos < column) {
                result.setY(0);
            } else if (indexPos < column * 2) {
                result.setY(getHeightScreen / 3);
                indexPos -= column;
            } else if (indexPos < column * 3) {
                result.setY((getHeightScreen / 3) * 2);
                indexPos -= column * 2;
            }
            break;
        case 4:
            if (indexPos < column) {
                result.setY(0);
            } else if (indexPos < column * 2) {
                result.setY(getHeightScreen / 4);
                indexPos -= column;
            } else if (indexPos < column * 3) {
                result.setY((getHeightScreen / 4) * 2);
                indexPos -= column * 2;
            } else if (indexPos < column * 4) {
                result.setY((getHeightScreen / 4) * 3);
                indexPos -= column * 3;
            }
            break;
        case 5:
            if (indexPos < column) {
                result.setY(0);
            } else if (indexPos < column * 2) {
                result.setY(getHeightScreen / 5);
                indexPos -= column;
            } else if (indexPos < column * 3) {
                result.setY((getHeightScreen / 5) * 2);
                indexPos -= column * 2;
            } else if (indexPos < column * 4) {
                result.setY((getHeightScreen / 5) * 3);
                indexPos -= column * 3;
            } else {
                result.setY((getHeightScreen / 5) * 4);
                indexPos -= column * 4;
            }
            break;
        }

        int num = getWidthScreen / column;
        result.setX(indexPos * num - 10);
        return result;
    }
    static void initializeScreenDimensions() {
        // Initialize the application (if not already done in the main function)
        if (!QGuiApplication::instance()) {
            int argc = 0;
            char *argv[] = {nullptr};
            new QGuiApplication(argc, argv);
        }

        // Get the primary screen
        QScreen *screen = QGuiApplication::primaryScreen();

        // Check if the screen is available
        if (screen) {
            // Get the working area size
            QRect workingArea = screen->availableGeometry();

            // Initialize the width and height of the working area
            getWidthScreen = workingArea.width();
            getHeightScreen = workingArea.height();
        } else {
            getWidthScreen = 0;
            getHeightScreen = 0;
        }
    }
    static QPoint GetSizeChrome(int column, int row) {
        if (SettingsTool::GetSettings("configChrome").GetValueInt("width") == 0) {
            SettingsTool::GetSettings("configChrome").Update("width", getWidthScreen);
            SettingsTool::GetSettings("configChrome").Update("heigh", getHeightScreen);
            SettingsTool::SaveSettings("configChrome");
        }
        getWidthScreen = SettingsTool::GetSettings("configChrome").GetValueInt("width");
        getHeightScreen = SettingsTool::GetSettings("configChrome").GetValueInt("heigh");
        int x = getWidthScreen / column + 15;
        int y = getHeightScreen / row + 10;
        return QPoint(x, y);
    }
private:
    static int getWidthScreen;
    static int getHeightScreen;
};

#endif // COMMON_H
