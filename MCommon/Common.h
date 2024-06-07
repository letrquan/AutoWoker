#ifndef COMMON_H
#define COMMON_H
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
    static void SwapTableWidgetRows(QTableWidget *tableWidget, int oldRow, int newRow, int indexStart = 1);
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
private:
    // static int getWidthScreen = Screen.PrimaryScreen.WorkingArea.Width;
};

#endif // COMMON_H
