#include "mainwindow.h"
#include "fimportaccount.h"
#include "qnetworkreply.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include "../MCommon/requesthandle.h"
#include <QNetworkAccessManager>
#include <zlib.h>
#include <QEventLoop>
#include "../maxcare/Language.h"
#include "../MCommon/commonsql.h"
#include "../maxcare/emailhelper.h"
#include "../MCommon/Common.h"
#include "../maxcare/setupfolder.h"
#include "../maxcare/SettingsTool.h"
#include <QSqlRecord>
#include "../CloneDatabase/clonedatabase.h"
#include "../maxcare/collectionhelper.h"
#include "../Form/fchonthumuc.h"//"
#include "fcauhinhhienthi.h"
#include <QTableWidget>
#include "../maxcare/datagridviewhelper.h"
#include "../Utils/Utils.h"
MainWindow::MainWindow(QString tokemem, QString namemem, QString phoneMem, QString maxDeviceMem,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    name = namemem;
    phone = phoneMem;
    this->setWindowTitle("AutoWorker");
    this->setWindowIcon(QIcon(":/img/img/eagle.png"));
    maxdevice = maxDeviceMem;
    ui->label_3->setText(ui->label_3->text()+name);
    ui->label_7->setText(ui->label_7->text()+phone);
    // ui->label_6->setText(ui->label_7->text()+Utils::buildDeviceId());
    this->setAttribute(Qt::WA_TranslucentBackground);
    setColumnVisibility("Id",false);
    OnLoaded();

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getIPServer(const QString& address) {
    QString ip = "";
    QHostInfo hostInfo = QHostInfo::fromName(address);
    if (!hostInfo.addresses().isEmpty()) {
        return hostInfo.addresses()[0].toString();  // Return the first address
    }
    return ip;  // Return an error message if no addresses were found
}

QString MainWindow::md5Encode(const QString &input) {
    // Convert the input QString to a QByteArray in UTF-8 encoding
    QByteArray byteArray = input.toUtf8();

    // Create an MD5 hash object and compute the hash
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);

    // Convert the hash to a hex string
    QString hexString = hash.toHex().toUpper();

    // Return the first 12 characters of the hex string
    return hexString.left(12);
}

void MainWindow::xoaProxy(){
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", QSettings::NativeFormat);

    // Set the ProxyServer and ProxyEnable values
    settings.setValue("ProxyServer", 1);  // It seems like a mistake in the original C# to set ProxyServer to 1 while disabling it.
    settings.setValue("ProxyEnable", 0);
}


//This function need to test ?
QString MainWindow::Getdocs(QString uri){
    QNetworkRequest request(uri);
    request.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, "Mozilla/5.0");
    // Enable automatic handling of decompression
    request.setRawHeader("Accept-Encoding", "gzip, deflate");
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;

    // Use an event loop to wait for the reply to finish
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QString responseText;
    if (reply->error() == QNetworkReply::NoError) {
        // Check for content encoding
        QByteArray responseData = reply->readAll();
        responseText = QString::fromUtf8(responseData);

    } else {
        qDebug() << "Network error:" << reply->errorString();
    }
    return responseText;
}

QString MainWindow::checkUpdate(QString namesoft){
    QString contentc;
    RequestHandle *requestHttp = new RequestHandle("datr=WZJvYiyKfkXCQUnre2uko636; fr=0oqi8uvi6J1Ke1hP4.AWWnEdQcAIbqvuADKlxidQffUOA.BiXNNR._x.AAA.0.0.Bi14Bb.AWWzPrNJL6o; sb=UNNcYqIKRmV0qebQb9n77CHo","","",0);
    try {
        return contentc = requestHttp->RequestGet("https://giau.cc/update/" + namesoft);
    } catch (...) {
    }
    return "";
}

void MainWindow::ChangeLanguage(){
    Language::SetLanguage(this);
    // Language::SetLanguage(menu)
}

void MainWindow::LoadcbbSearch(){
    ui->cbbSearch->addItem("UID", "cUid");
    ui->cbbSearch->addItem(Language::GetValue("Mật khẩu"), "cPassword");
    ui->cbbSearch->addItem(Language::GetValue("Tên"), "cName");
    ui->cbbSearch->addItem(Language::GetValue("Ngày sinh"), "cBirthday");
    ui->cbbSearch->addItem(Language::GetValue("Giới tính"), "cGender");
    ui->cbbSearch->addItem("Token", "cToken");
    ui->cbbSearch->addItem("Cookie", "cCookies");
    ui->cbbSearch->addItem("Email", "cEmail");
    ui->cbbSearch->addItem("Pass email", "cPassMail");
    ui->cbbSearch->addItem("2FA", "cFa2");
    ui->cbbSearch->addItem(Language::GetValue("Ghi chu\u0301"), "cGhiChu");
    ui->cbbSearch->addItem(Language::GetValue("Tương ta\u0301c cuô\u0301i"), "cInteractEnd");
}
void MainWindow::LoadCbbThuMuc(int selectedIndex){
    isExcute_CbbThuMuc_SelectedIndexChanged = false;
    QVariantList allFilesFromDatabase = CommonSQL::GetAllFilesFromDatabase(true);
    ui->cbbThuMuc->clear();
    for (int i = 0; i < allFilesFromDatabase.size(); ++i) {
        const QVariant &item = allFilesFromDatabase[i];
        QVariantMap rowMap = item.toMap();
        ui->cbbThuMuc->addItem(rowMap["name"].toString(), rowMap["id"].toString());
        ui->cbbThuMuc->setCurrentIndex(i);
    }
    if(selectedIndex != -1 && ui->cbbThuMuc->count() >= selectedIndex){
        ui->cbbThuMuc->setCurrentIndex(selectedIndex);
    }
    isExcute_CbbThuMuc_SelectedIndexChanged = true;
}

void MainWindow::LoadCbbTinhTrang(const QList<QString>& lstIdFile){
    try {
        QVariantList allInfoFromAccount = CommonSQL::GetAllInfoFromAccount(lstIdFile);
        ui->cbbTinhTrang->clear();
        for (int i = 0; i < allInfoFromAccount.size(); ++i) {
            const QVariant &item = allInfoFromAccount[i];
            QVariantMap rowMap = item.toMap();
            ui->cbbTinhTrang->addItem(rowMap["name"].toString(), rowMap["id"].toString());

            // Set the current index to trigger the signal
            ui->cbbTinhTrang->setCurrentIndex(i);
            on_cbbTinhTrang_currentIndexChanged(i);
        }
    } catch (...) {
    }
}

void MainWindow::OnLoaded(){
    lstMailDomainAw = *EmailHelper::getListMailDomain();
    QFile file("update.ini");
    try {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString textUpdate = in.readAll();
            file.close();
            QString namesoft = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[0].replace("[", "").replace("]", "");
            QString currentVersion = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[1].replace("Version=", "");
            if(!QFile::exists("AutoUpdate.exe") || QFileInfo("AutoUpdate.exe").size() != 165376 ){
                Common::DownloadFile("https://storage.giau.cc/"+namesoft+"/autoupdate.zip");
            }
        }
        SetupFolder::StartApplication();
        LoadcbbSearch();
        LoadCbbThuMuc(1);
        LoadCbbTinhTrang();
        LoadConfigManHinh();
        AddUI();
    } catch (...) {
    }
}
void MainWindow::AddUI(){
    bool ignore = Base::isLam;
    Q_UNUSED(ignore);
}
void MainWindow::changeEvent(QEvent *event){
    if (event->type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            try {
                try {
                    QFile file("settings\\language.txt");
                    file.remove();

                } catch (...) {
                }
                if(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBackupDB",true)){
                    CloneDatabase::Excute();
                }
                QApplication::exit();
            } catch (...) {
                this->close();
            }

        }else{
            if(isMaximized()){

            }
        }
    }
    QMainWindow::changeEvent(event);
}



void MainWindow::on_btnLoadAcc_clicked()
{
    QString text ="";
    if(!ui->cbbThuMuc->currentData().isNull()){
        text = ui->cbbThuMuc->currentData().toString();
    }
    LoadCbbThuMuc();
    if(text != "999999" && text !="-1"){
        indexCbbThuMucOld =-1;
        ui->cbbThuMuc->currentData()=text;
        return;
    }
    isExcute_CbbThuMuc_SelectedIndexChanged =false;
    ui->cbbThuMuc->currentData()=text;
    LoadCbbTinhTrang();
}

QList<QString> MainWindow::GetIdFile(){
    QList<QString>  result;
    try {
        QString text = ui->cbbThuMuc->currentData().toString();
        if(text !="-1"){
            if(text == "999999"){
                result = CollectionHelper::CloneList(fChonThuMuc::lstChooseIdFiles);
            }
            result = {ui->cbbThuMuc->currentData().toString()};
        }
    } catch (...) {
    }
    return result;
}

void MainWindow::LoadAccountFromFile(QList<QString> lstIdFile, QString info){
    try {
        if (info == "[Tất cả tình trạng]" || info == Language::GetValue("[Tất cả tình trạng]"))
        {
            info = "";
        }
        QVariantList accFromFile = CommonSQL::GetAccFromFile(&lstIdFile, info);
        LoadDtgvAccFromDatatable(&accFromFile);
    } catch (...) {
    }
}
void MainWindow::LoadDtgvAccFromDatatable(QVariantList* tableAccount){
    DatagridviewHelper::LoadDtgvAccFromDatatable(this->ui->tableWidget,tableAccount);
    CountCheckedAccount(0);
    SetRowColor();
    CountTotalAccount();
}


void MainWindow::on_pushButton_4_clicked()
{
    QString fullString = SettingsTool::GetSettings("configDatagridview").GetFullString();
    auto cauhinh = new fCauHinhHienThi(this);
    cauhinh->exec();
    if(SettingsTool::GetSettings("configDatagridview").GetFullString() != fullString){
        LoadConfigManHinh();
    }
}

void MainWindow::LoadConfigManHinh(){
    setColumnVisibility("Token",SettingsTool::GetSettings("configDatagridview").GetValueBool("cToken"));
    setColumnVisibility("Cookies",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbCookie"));
    setColumnVisibility("Email",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbEmail"));
    setColumnVisibility("Tên",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbTen"));
    setColumnVisibility("Bạn Bè",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBanBe"));
    setColumnVisibility("Page",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPage"));
    setColumnVisibility("PagePro5",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPagePro5",false));
    setColumnVisibility("Ngày sinh",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNgaySinh"));
    setColumnVisibility("Giới tính",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbGioiTinh"));
    setColumnVisibility("Mật khẩu",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMatKhau"));
    setColumnVisibility("Mail Khôi Phục",SettingsTool::GetSettings("configDatagridview").GetValueBool("cMailRecovery"));
    setColumnVisibility("Mật khẩu Mail",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMatKhauMail"));
    setColumnVisibility("Backup",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBackup"));
    setColumnVisibility("Mã 2FA",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMa2FA"));
    setColumnVisibility("Useragent",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbUseragent"));
    setColumnVisibility("Proxy",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbProxy"));
    setColumnVisibility("Ngày tạo tài khoản",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNgayTao"));
    setColumnVisibility("Avatar",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbAvatar"));
    setColumnVisibility("Profile",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbProfile"));
    setColumnVisibility("Tình Trạng",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbTinhTrang"));
    setColumnVisibility("Thư Mục",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbThuMuc"));
    setColumnVisibility("Ghi Chú",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbGhiChu"));
    setColumnVisibility("Lần Tương Tác Cuối",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbInteractEnd"));
    setColumnVisibility("Mail Khôi Phục",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbMailRecovery"));
    setColumnVisibility("Phone",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbPhone"));
    setColumnVisibility("Home Town",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbHometown"));
    setColumnVisibility("Current City",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbCurrentCity"));
    setColumnVisibility("Job",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbJob",false));
    setColumnVisibility("Location",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbLocation"));
    setColumnVisibility("Dating",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbDating"));
    setColumnVisibility("Ads",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbAds"));
    setColumnVisibility("BM",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbBM"));
    setColumnVisibility("FbBlock",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbFbBlock"));
    setColumnVisibility("Status282",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbStatus282"));
    setColumnVisibility("Nhóm",SettingsTool::GetSettings("configDatagridview").GetValueBool("ckbNhom"));
}
void MainWindow::setColumnVisibility(const QString& headerLabel, bool isVisible){
    int columnIndex = -1;
    for(int i=0;i<ui->tableWidget->columnCount();++i){
        if (ui->tableWidget->horizontalHeaderItem(i)->text() == headerLabel) {
            columnIndex = i;
            break;
        }
    }
    if (columnIndex != -1) {
        ui->tableWidget->setColumnHidden(columnIndex, !isVisible);
    }
}
void MainWindow::SetRowColor(int indexRow){
    if(SettingsTool::GetSettings("configGeneral").GetValueInt("typePhanBietMau") == 0){
        if(indexRow == -1){
            for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
                QString infoAccount = GetInfoAccount(var);
                if(infoAccount =="Live"){
                    Utils::changeRowColor(ui->tableWidget,var,QColor(184, 233, 148));
                }else if(infoAccount.contains("Die") || infoAccount.contains("Checkpoint") || infoAccount.contains("Changed pass")){
                    Utils::changeRowColor(ui->tableWidget,var,QColor(255, 118, 117));
                }
            }
        }else{
            QString infoAccount2 = GetInfoAccount(indexRow);
            if (infoAccount2 == "Live")
            {
                Utils::changeRowColor(ui->tableWidget,indexRow,QColor(184, 233, 148));
            }
            else if (infoAccount2.contains("Die") || infoAccount2.contains("Checkpoint") || infoAccount2.contains("Changed pass"))
            {
                Utils::changeRowColor(ui->tableWidget,indexRow,QColor(255, 118, 117));
            }
        }
    }else if(indexRow == -1){
        for (int j = 0; j < ui->tableWidget->rowCount(); j++)
        {
            QString infoAccount3 = GetInfoAccount(j);
            if (infoAccount3 == "Live")
            {
                Utils::changeRowColor(ui->tableWidget,j,QColor("green"));
            }
            else if (infoAccount3.contains("Die") || infoAccount3.contains("Checkpoint") || infoAccount3.contains("Changed pass"))
            {
                Utils::changeRowColor(ui->tableWidget,j,QColor("red"));
            }
        }
    }else{
        QString infoAccount4 = GetInfoAccount(indexRow);
        if (infoAccount4 == "Live")
        {
            Utils::changeRowColor(ui->tableWidget,indexRow,QColor("green"));
        }
        else if (infoAccount4.contains("Die") || infoAccount4.contains("Checkpoint") || infoAccount4.contains("Changed pass"))
        {
            Utils::changeRowColor(ui->tableWidget,indexRow,QColor("red"));
        }
    }
}

QString MainWindow::GetInfoAccount(int indexRow)
{
    return DatagridviewHelper::GetStatusDataGridView(ui->tableWidget, indexRow, "Info");
}

void MainWindow::CountCheckedAccount(int count){
    if(count ==-1){
        count = 0;
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            if (ui->tableWidget->item(i,Utils::GetIndexByColumnHeader(ui->tableWidget,"Chọn"))->text().toInt() == 1)
            {
                count++;
            }
        }
    }
    ui->lblCountSelect->setText(QString::number(count));
}

void MainWindow::CountTotalAccount(){
    try {
        ui->lblCountTotal->setText(QString::number(ui->tableWidget->rowCount()));
    } catch (...) {
    }
}

void MainWindow::on_button9_clicked()
{
    try {
        QString text = "";
        if(ui->cbbThuMuc->currentData() != NULL){
            text = ui->cbbThuMuc->currentData().toString();
        }
        fImportAccount* fImportAccount2 = new fImportAccount(text);
        Common::ShowForm(fImportAccount2);
        if(fImportAccount2->isAddAccount || fImportAccount2->isAddFile){
            LoadCbbThuMuc();
            indexCbbThuMucOld=-1;
            if(fImportAccount2->isAddAccount){
                ui->cbbThuMuc->setItemData(ui->cbbThuMuc->currentIndex(),fImportAccount2->idFileAdded);
            }else{
                ui->cbbThuMuc->setItemData(ui->cbbThuMuc->currentIndex(),text);
            }
        }
    } catch (...) {
    }
}



void MainWindow::on_cbbThuMuc_currentIndexChanged(int index)
{
    auto data = ui->cbbThuMuc->currentData();
    auto check= data.toInt();
    if (!isExcute_CbbThuMuc_SelectedIndexChanged || data.isNull() || !(check != 0) || (data.toString()) != "999999" && indexCbbThuMucOld == ui->cbbThuMuc->currentIndex())
    {
        return;
    }
    QString text = ui->cbbThuMuc->currentData().toString();
    if(!(text == "-1")){
        if(text == "999999"){
            Common::ShowDialog(new fChonThuMuc());
            if(!fChonThuMuc::isAdd || fChonThuMuc::lstChooseIdFiles.isEmpty() || fChonThuMuc::lstChooseIdFiles.size() ==0){
                isExcute_CbbThuMuc_SelectedIndexChanged =false;
                ui->cbbThuMuc->setCurrentIndex( ((indexCbbThuMucOld != -1) ? indexCbbThuMucOld : 0));
                isExcute_CbbThuMuc_SelectedIndexChanged = true;
            }else{
                LoadCbbTinhTrang(fChonThuMuc::lstChooseIdFiles);
            }
        }else{
            LoadCbbTinhTrang(GetIdFile());
        }
    }else{
        LoadCbbTinhTrang();
    }
    indexCbbThuMucOld = ui->cbbThuMuc->currentIndex();
    if(!ui->cbbThuMuc->currentData().isNull()){
        QString text2 = ui->cbbThuMuc->currentData().toString();
        if(text2 == "-1" || text2 == "999999"){
            // ui->btnDeleteFile->setStyleSheet("background-color: gray;");
            ui->btnDeleteFile->setVisible(false);
            ui->btnDeleteFile->setEnabled(false);
            // ui->btnEditFile->setStyleSheet("background-color: gray;");
            ui->btnEditFile->setEnabled(false);
            ui->btnEditFile->setVisible(false);
        }else{
            // ui->btnDeleteFile->setStyleSheet("background-color: white;");
            ui->btnDeleteFile->setEnabled(true);
            // ui->btnEditFile->setStyleSheet("background-color: white;");
            ui->btnEditFile->setEnabled(true);
        }
    }
}


void MainWindow::on_cbbTinhTrang_currentIndexChanged(int index)
{
    auto data = ui->cbbTinhTrang->currentData();
    auto check= data.toInt();
    if (!isExcute_CbbTinhTrang_SelectedIndexChanged || data.isNull() || !!(check != 0) || (data.toString() != "-1" && indexCbbTinhTrangOld == ui->cbbThuMuc->currentIndex()))
    {
        return;
    }
    QString text = ui->cbbTinhTrang->currentData().toString();
    if(!(text == "-1")){
        if (text == "999999")
        {
            LoadAccountFromFile(fChonThuMuc::lstChooseIdFiles, ui->cbbTinhTrang->currentText());
        }
        else
        {
            LoadAccountFromFile(GetIdFile(), ui->cbbTinhTrang->currentText());
        }
    }else{
        LoadAccountFromFile(QList<QString>(), ui->cbbTinhTrang->currentText());
    }
    indexCbbTinhTrangOld = ui->cbbTinhTrang->currentIndex();
}

