#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include <QSslConfiguration>
#include "../Utils/Utils.h"
#include <QDir>
#include <QMessageBox>
#include <QException>
#include <QMovie>
#include "../maxcare/Language.h"
#include <QProcess>
#include "../MCommon/Common.h"
#include <QTimer>
DownloadDialog::DownloadDialog(QString fileLink,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DownloadDialog)
{
    ui->setupUi(this);
    this->fileLink = fileLink;
    QFileInfo file(fileLink);
    fileName = file.fileName();
    manager = new QNetworkAccessManager(this);
    QMovie *movie = new QMovie(":/img/C:/Users/quan2/Downloads/handy-loading-paper-into-the-printer.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
    if(fileLink !=""){
        progress_Load();
    }
    this->setWindowTitle("Download");
}

DownloadDialog::~DownloadDialog()
{
    delete ui;
}

void DownloadDialog::progress_Load(){
    try {
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyPeer);
        config.setProtocol(QSsl::TlsV1_2);
        QSslConfiguration::setDefaultConfiguration(config);

        if (Utils::isConnectedToInternet()) {
            QUrl uri(fileLink);
            QDir dir;
            dir.remove("download");
            dir.mkdir("download");
            startDownload(uri, "download/" + fileName);
        } else {
            QMessageBox::warning(this, tr("Connection Error"), tr("No internet connection, please check again!"));
            close();
        }
    } catch (const QException &ex) {
        QMessageBox::critical(this, tr("Error"), tr("Error: %1").arg(ex.what()));
        close();
    }
}

void DownloadDialog::startDownload(const QUrl &url, const QString &pathFile) {
    QNetworkRequest request(url);
    reply = manager->get(request);
    outputFile = new QFile(pathFile);
    if (!outputFile->open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file:" << pathFile;
        delete outputFile;
        return;
    }
    ui->progressBar->setValue(0);
    connect(reply, &QNetworkReply::downloadProgress, this, &DownloadDialog::updateProgress);
    connect(reply, &QIODevice::readyRead, this, &DownloadDialog::onReadyRead);
    connect(reply, &QNetworkReply::finished, this, &DownloadDialog::downloadFinished);
}

void DownloadDialog::updateProgress(qint64 bytesRead, qint64 totalBytes) {
    ui->progressBar->setValue(static_cast<int>(100 * bytesRead / totalBytes));
    ui->label->setText(QString("Downloading (%1%)...").arg(100 * bytesRead / totalBytes));
}
void DownloadDialog::downloadFinished(){
    if (reply->error() == QNetworkReply::NoError) {
        ui->label->setText("Download completed!");
        ui->label->setText(Language::GetValue("Unzip file..."));
        try {
            unzipFile("./download/" + fileName, "./download/");
            Common::deleteFile("./download/" + fileName);

            if(copyDir("download", "./")){
                Common::deleteDirectory("download");
                outputFile->flush();
                outputFile->close();
                qDebug() << "Download finished";
                QTimer::singleShot(3000, this, &QDialog::close);
            }
        } catch (...) {
        }

    } else {
        ui->label->setText("Download failed!");
        QMovie* fail = new QMovie(":/img/C:/Users/quan2/Downloads/bouncy-multiple-errors-on-the-computer.gif");
        ui->gifLabel->setMovie(fail);
        fail->start();
        QTimer::singleShot(3000, this, &QDialog::close);
    }
    reply->deleteLater();
    outputFile->deleteLater();
}
bool DownloadDialog::copyDir(const QString &sourcePath, const QString &destinationPath) {
    QDir sourceDirectory(sourcePath);
    if (!sourceDirectory.exists())
        return false;

    QDir targetDirectory(destinationPath);
    if (!targetDirectory.exists()) {
        targetDirectory.mkpath(".");
    }

    foreach (const QString &fileName, sourceDirectory.entryList(QDir::Files)) {
        const QString srcName = sourcePath + QDir::separator() + fileName;
        const QString destName = destinationPath + QDir::separator() + fileName;
        QFile::copy(srcName, destName);
    }

    foreach (const QString &directoryName, sourceDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        const QString srcName = sourcePath + QDir::separator() + directoryName;
        const QString destName = destinationPath + QDir::separator() + directoryName;
        copyDir(srcName, destName);  // Recursive call
    }

    return true;
}
void DownloadDialog::unzipFile(const QString &zipFilePath, const QString &outputDir){
    QString program = "7z.exe";

    // Prepare arguments
    QStringList arguments;
    arguments << "x"                    // 'x' means extract with full paths
              << "-y"                   // Assume Yes on all queries (e.g., overwrite files without asking)
              << zipFilePath            // The path of the zip file to extract
              << QString("-o%1").arg(outputDir); // Output directory
    QProcess *process = new QProcess();
    process->start(program, arguments);

    // Optional: Wait for the process to finish if synchronous execution is needed
    if (!process->waitForFinished()) {
        qDebug() << "Failed to execute 7z:" << process->errorString();
    } else {
        qDebug() << "Extraction complete. Output:" << process->readAllStandardOutput();
    }

    delete process;  // Clean up the QProcess instance
}
void DownloadDialog::onReadyRead() {
    if (outputFile) {
        outputFile->write(reply->readAll());
    }
}
