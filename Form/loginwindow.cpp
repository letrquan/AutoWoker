#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "../maxcare/SettingsTool.h"
#include "../MCommon/AwApi.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QFontDatabase>
#include <QMovie>
#include <QRegularExpression>
#include <QFile>
#include "mainwindow.h"
#include <QGraphicsDropShadowEffect>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    // QMovie *movie = new QMovie(":/res/img/C:/Users/quan2/Downloads/droll-coming-soon.gif");
    // ui->gifLabel->setMovie(movie);
    // movie->start();

    this->setWindowIcon(QIcon(":/img/img/eagle.png"));
    this->setWindowTitle("AutoWorker");

    // Set the QLineEdit to handle key press events
    ui->accountEdit->installEventFilter(this);
    loadSettings();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loadSettings(){
    getLogin();
    Loadx();
}


void LoginWindow::saveLogin(){
    QString password = ui->accountEdit->text();
    SettingsTool::GetSettings("settingLogin").Update("Username",ui->accountEdit->text());
    SettingsTool::GetSettings("settingLogin").Update("password",password.toUtf8().toBase64());
    SettingsTool::GetSettings("settingLogin").Update("cb_luu",ui->remeberBox->isChecked());
    SettingsTool::SaveSettings("settingLogin");
}

void LoginWindow::on_LoginButton_clicked()
{

    if(ui->remeberBox->isChecked()) {
        saveLogin();
    }
    try {
        QString account = ui->accountEdit->text();
        QString password = ui->passwordEdit->text();
        QString res = AwApi::LoginTool(account,password);
        QJsonDocument doc =QJsonDocument::fromJson(res.toUtf8());
        if(!doc.isNull()){
            QJsonObject response = doc.object();
            int status = response["status"].toInt();
            QString mess = response["msg"].toString();
            if(status == 200){
                QJsonObject result = response["result"].toObject();
                QString token = result["token"].toString();
                QString name = result["fullname"].toString();
                QString phone = result["phone"].toString();
                QString max_devices = result["status"].toString();
                int status_u = result["status"].toString().toInt();
                QString boxchao = name + " đăng nhập thành công";
                QMessageBox::information(this, "Đăng nhập", boxchao);
                if(status_u==1){
                    auto  mainWindow = new MainWindow(token,name,phone,max_devices,this);
                    this->close();
                    mainWindow->show();
                }else{
                    QMessageBox::critical(this,
                                          "ĐĂNG NHẬP",
                                          "Tài khoản của bạn đã bị khoá",
                                          QMessageBox::Ok);
                    QCoreApplication::exit(0);
                }
            }else{
                QMessageBox::warning(this, "ĐĂNG NHẬP", "Sai tên tài khoản hoặc mật khẩu");
            }
        }
    } catch (...) {
        QMessageBox::warning(this, "ĐĂNG NHẬP", "Lỗi kết nối đến Server !");
    }
}


void LoginWindow::getLogin(){
    ui->accountEdit->setText(SettingsTool::GetSettings("settingLogin").GetValue("Username"));
    ui->passwordEdit->setText(QByteArray::fromBase64((SettingsTool::GetSettings("settingLogin").GetValue("password").toUtf8())));
    ui->remeberBox->setChecked(SettingsTool::GetSettings("settingLogin").GetValueBool("cb_luu"));
}

void LoginWindow::Loadx(){
    QFile file("update.ini");
    try {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            // QTextStream in(&file);
            // QString textUpdate = in.readAll();
            // file.close();
            // QString namesoft = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[0].replace("[", "").replace("]", "");
            // QString currentVersion = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[1].replace("Version=", "");
            // ui->versionLabel->setText(namesoft+" v "+currentVersion);
            // if(!QFile::exists("AutoUpdate.exe") || QFileInfo("AutoUpdate.exe").size() != 165376 ){
            //     Common::DownloadFile("https://storage.giau.cc/"+namesoft+"/autoupdate.zip");
            // }
            // try {
            //     QString contentRes = AwApi::checkUpdate(namesoft);
            //     QJsonDocument doc =QJsonDocument::fromJson(contentRes.toUtf8());
            //     if(!doc.isEmpty()){
            //         QJsonObject obj = doc.object();

            //         QString newversion = obj["version"].toString();
            //         QString content = obj["content"].toString();
            //         QString linkupdate = obj["link"].toString();
            //         if(newversion != currentVersion){
            //             QMessageBox::information(this,"Cập nhật hệ thống","Vui lòng cập nhật phần mềm để tiếp tục sử dụng");
            //             QProcess::startDetached("Autoupdate.exe");
            //             QCoreApplication::exit(0);
            //             return;
            //         }
            //     }
            // } catch (...) {
            //     QMessageBox::information(this,"Error","Không thể kết nối đến server");
            // }
            try {
                QFile file("update.ini");

                if (!file.exists()) {
                    // File does not exist, create it and write the initial content
                    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                        QTextStream out(&file);
                        out << "[awcare]\r\nVersion=1.0\r\nContent=";
                        file.close();
                    }
                } else {
                    // File exists, read its content and modify if necessary
                    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        QTextStream in(&file);
                        QString content = in.readAll();
                        file.close();

                        // Process content
                        QStringList lines = content.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
                        if (lines[0] != "[awcare]") {
                            content.replace(lines[0], "[awcare]");
                        }

                        // Write back the modified content
                        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                            QTextStream out(&file);
                            out << content;
                            file.close();
                        }
                    }
                }
            } catch (...) {
            }
            on_LoginButton_clicked();
        }
    } catch (...) {
    }
}

void LoginWindow::on_closeButton_clicked()
{
    this->close();
}



