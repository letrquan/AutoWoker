#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H
#include <QNetworkAccessManager>
#include <QDialog>
#include <QNetworkReply>
#include <QFile>
namespace Ui {
class DownloadDialog;
}

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QString fileLink ,QWidget *parent = nullptr);
    ~DownloadDialog();
    void startDownload(const QUrl &url, const QString &pathFile);
    bool copyDir(const QString &sourcePath, const QString &destinationPath);
    void unzipFile(const QString &zipFilePath, const QString &outputDir);
private:
    Ui::DownloadDialog *ui;
    void progress_Load();
    QString fileLink = "";
    QString fileName = "";
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile* outputFile;
private slots:
    void updateProgress(qint64 bytesRead, qint64 totalBytes);
    void downloadFinished();
    void onReadyRead();
};

#endif // DOWNLOADDIALOG_H
