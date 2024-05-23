#include "mainwindow.h"
#include "fimportaccount.h"
#include "qnetworkreply.h"
#include "Form/ui_mainwindow.h"
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
#include "../maxcare/collectionhelper.h"
#include "../Form/fchonthumuc.h"
#include "fcauhinhhienthi.h"
#include <QTableWidget>
#include "../maxcare/datagridviewhelper.h"
#include "../Utils/Utils.h"
#include "../MCommon/CommonRequest.h"
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
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
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
    QVariantList allFilesFromDatabase = *CommonSQL::GetAllFilesFromDatabase(true);
    ui->cbbThuMuc->clear();
    for (int i = 0; i < allFilesFromDatabase.size(); ++i) {
        auto rowMap = allFilesFromDatabase[i].toMap();
        ui->cbbThuMuc->addItem(rowMap["name"].toString() , rowMap["id"].toString());
        ui->cbbThuMuc->setCurrentIndex(i);
    }
    if(selectedIndex != -1 && ui->cbbThuMuc->count() >= selectedIndex){
        ui->cbbThuMuc->setCurrentIndex(selectedIndex);
    }
    isExcute_CbbThuMuc_SelectedIndexChanged = true;
}

void MainWindow::LoadCbbTinhTrang(const QList<QString>& lstIdFile){
    try {
        QVariantList allInfoFromAccount = *CommonSQL::GetAllInfoFromAccount(lstIdFile);
        ui->cbbTinhTrang->clear();
        for (int i = 0; i < allInfoFromAccount.size(); ++i) {
            auto rowMap = allInfoFromAccount[i].toMap();
            ui->cbbTinhTrang->addItem(rowMap["name"].toString() , rowMap["id"].toString());
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
            // try {
            //     try {
            //         QFile file("settings\\language.txt");
            //         file.remove();

            //     } catch (...) {
            //     }
            //     if(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbBackupDB",true)){
            //         CloneDatabase::Excute();
            //     }
            //     QApplication::exit();
            // } catch (...) {
            //     this->close();
            // }

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
        QVariantList accFromFile = *CommonSQL::GetAccFromFile(&lstIdFile, info);
        LoadDtgvAccFromDatatable(&accFromFile);
    } catch (...) {
    }
}
void MainWindow::LoadDtgvAccFromDatatable(QSqlQueryModel* tableAccount){
    DatagridviewHelper::LoadDtgvAccFromDatatable(this->ui->ta,tableAccount);
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
    int columnIndex = Utils::findColumnByHeader(ui->tableView,headerLabel);
    if(columnIndex != -1){
        ui->tableView->setColumnHidden(columnIndex, !isVisible);
    }
}
void MainWindow::SetRowColor(int indexRow){
    if(SettingsTool::GetSettings("configGeneral").GetValueInt("typePhanBietMau") == 0){
        if(indexRow == -1){
            for (int var = 0; var < ui->tableView->model()->rowCount(); var++) {
                QString infoAccount = GetInfoAccount(var);
                if(infoAccount =="Live"){
                    Utils::changeRowColor(ui->tableView,var,QColor(184, 233, 148));
                }else if(infoAccount.contains("Die") || infoAccount.contains("Checkpoint") || infoAccount.contains("Changed pass")){
                    Utils::changeRowColor(ui->tableView,var,QColor(255, 118, 117));
                }
            }
        }else{
            QString infoAccount2 = GetInfoAccount(indexRow);
            if (infoAccount2 == "Live")
            {
                Utils::changeRowColor(ui->tableView,indexRow,QColor(184, 233, 148));
            }
            else if (infoAccount2.contains("Die") || infoAccount2.contains("Checkpoint") || infoAccount2.contains("Changed pass"))
            {
                Utils::changeRowColor(ui->tableView,indexRow,QColor(255, 118, 117));
            }
        }
    }else if(indexRow == -1){
        for (int j = 0; j < ui->tableView->model()->rowCount(); j++)
        {
            QString infoAccount3 = GetInfoAccount(j);
            if (infoAccount3 == "Live")
            {
                Utils::changeRowColor(ui->tableView,j,QColor("green"));
            }
            else if (infoAccount3.contains("Die") || infoAccount3.contains("Checkpoint") || infoAccount3.contains("Changed pass"))
            {
                Utils::changeRowColor(ui->tableView,j,QColor("red"));
            }
        }
    }else{
        QString infoAccount4 = GetInfoAccount(indexRow);
        if (infoAccount4 == "Live")
        {
            Utils::changeRowColor(ui->tableView,indexRow,QColor("green"));
        }
        else if (infoAccount4.contains("Die") || infoAccount4.contains("Checkpoint") || infoAccount4.contains("Changed pass"))
        {
            Utils::changeRowColor(ui->tableView,indexRow,QColor("red"));
        }
    }
}

QString MainWindow::GetInfoAccount(int indexRow)
{
    return DatagridviewHelper::GetStatusDataGridView(ui->tableView, indexRow, "Info");
}

void MainWindow::CountCheckedAccount(int count){
    if(count ==-1){
        count = 0;
        for (int i = 0; i < ui->tableView->model()->rowCount(); i++)
        {
            if (ui->tableView->model()->index(i,Utils::findColumnByHeader(ui->tableView,"Chọn")).data().toInt() == 1)
            {
                count++;
            }
        }
    }
    ui->lblCountSelect->setText(QString::number(count));
}

void MainWindow::CountTotalAccount(){
    try {
        ui->lblCountTotal->setText(QString::number(ui->tableView->model()->rowCount()));
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

void MainWindow::KiemTraTaiKhoan(int type, bool useProxy){
    QAtomicInt iThread(0);
    int maxThread=SettingsTool::GetSettings("configGeneral").GetValueInt("nudHideThread", 10);
    QString tokenTrungGian = SettingsTool::GetSettings("configGeneral").GetValue("token");
    isStop = false;
    QThread::create([this, &tokenTrungGian, &iThread, &maxThread, &type](){
        cControl("start");
        switch (type) {
        case 0:
        {
            int num4=0;
            while (num4 <ui->tableWidget->rowCount() && !isStop) {
                if(ui->tableWidget->item(num4,0)->checkState() == Qt::Checked){
                    if(iThread <maxThread){
                        iThread.fetchAndAddOrdered(1);
                        int row3 = num4++;
                        QThread::create([&row3, this, &tokenTrungGian, &iThread]() {
                            SetStatusAccount(row3, Language::GetValue("Đang kiểm tra..."));
                            CheckMyWall(row3, tokenTrungGian);
                            iThread.fetchAndSubOrdered(1);
                        })->start();
                    }else{
                        QCoreApplication::processEvents();
                        QThread::msleep(200);
                    }
                }else
                {
                    num4++;
                }
            }
            break;
        }
        case 1:{
            int num6=0;
            while (num6 <ui->tableWidget->rowCount() && !isStop) {
                if(ui->tableWidget->item(num6,0)->checkState() == Qt::Checked){
                    if(iThread <maxThread){
                        iThread.fetchAndAddOrdered(1);
                        int row = num6++;
                        QThread::create([&row, this, &iThread]() {
                            SetStatusAccount(row, Language::GetValue("Đang kiểm tra..."));
                            CheckMyToken(row);
                            iThread.fetchAndSubOrdered(1);
                        })->start();
                    }else{
                        QCoreApplication::processEvents();
                        QThread::msleep(200);
                    }
                }else
                {
                    num6++;
                }
            }
        }
        case 2:{
            int num2 = 0;
            while (num2 <ui->tableWidget->rowCount() && !isStop)
            {
                if (ui->tableWidget->item(num2,0)->checkState() == Qt::Checked)
                {
                    if(iThread <maxThread){
                        iThread.fetchAndAddOrdered(1);
                        int row = num2++;
                        QThread::create([&row, this, &iThread]() {
                            SetStatusAccount(row, Language::GetValue("Đang kiểm tra..."));
                            CheckMyCookie(row);
                            iThread.fetchAndSubOrdered(1);
                        })->start();
                    }else{
                        QCoreApplication::processEvents();
                        QThread::msleep(200);
                    }
                }
                else
                {
                    num2++;
                }
            }
            break;
        }
        case 3:{
            int num5 = 0;
            while (num5 < ui->tableWidget->rowCount() && !isStop)
            {
                if (ui->tableWidget->item(num5,0)->checkState() == Qt::Checked)
                {
                    if (iThread < maxThread)
                    {
                        iThread.fetchAndAddOrdered(1);
                        int row2 = num5++;
                        QThread::create([&row2, this, &iThread]() {
                            SetStatusAccount(row2, Language::GetValue("Đang kiểm tra..."));
                            CheckDangCheckpoint(row2);
                            iThread.fetchAndSubOrdered(1);
                        })->start();
                    }else{
                        QCoreApplication::processEvents();
                        QThread::msleep(200);
                    }
                }
                else
                {
                    num5++;
                }
            }
            break;
        }
        case 4:{
            int num3 = 0;
            while (num3 < ui->tableWidget->rowCount() && !isStop)
            {
                if (ui->tableWidget->item(num3,0)->checkState() == Qt::Checked)
                {
                    if (iThread < maxThread)
                    {
                        iThread.fetchAndAddOrdered(1);
                        int row4 = num3++;
                        QThread::create([&row4, this, &iThread]() {
                            SetStatusAccount(row4, Language::GetValue("Đang kiểm tra..."));
                            CheckAccountMail(row4);
                            iThread.fetchAndSubOrdered(1);
                        })->start();
                    }
                    else
                    {
                        QCoreApplication::processEvents();
                        QThread::msleep(200);
                    }
                }
                else
                {
                    num3++;
                }
            }
            break;
        }
        default:
            break;
        }
    })->start();
}

void MainWindow::CheckAccountMail(int row){
    try {
        QString text = "";
        QString text2 = "";
        text = ui->tableWidget->item(row, Utils::GetIndexByColumnHeader(ui->tableWidget,"Email"))->text();
        text2 = ui->tableWidget->item(row, Utils::GetIndexByColumnHeader(ui->tableWidget,"Mật khẩu Mail"))->text();
    } catch (...) {
    }
}

void MainWindow::CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282){
    try {
        RequestHandle requestXNet(cookie, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);
        isCheckpoint282 = false;
        QString text = requestXNet.RequestGet("https://mbasic.facebook.com/");
        QString url = requestXNet.GetUrl();
        if(url.contains("checkpoint/disabled")){
            SetStatusAccount(indexRow, statusProxy + "Vô hiệu hóa!");
            SetInfoAccount(indexRow, "Checkpoint: vhh");
            SetRowColor(indexRow, 1);
        }else if (url.contains("828281030927956"))
        {
            QString text2 = "956";
            text2 = ((!text.contains("/stepper/")) ? (text2 + "-Tìm hiểu thêm") : (text2 + "-Bắt đầu"));
            SetStatusAccount(indexRow, statusProxy + "Checkpoint " + text2 + "!");
            SetInfoAccount(indexRow, "Checkpoint: " + text2);
            SetRowColor(indexRow, 1);
        }else if (url.contains("1501092823525282"))
        {
            SetInfoAccount(indexRow, "Checkpoint: 282");
            SetStatusAccount(indexRow, statusProxy + "Checkpoint 282!");
            isCheckpoint282 = true;
        }
        else if (url.contains("facebook.com/gettingstarted") || (text.contains("href=\"/menu/bookmarks/") && text.contains("id=\"mbasic_logout_button\"")))
        {
            SetInfoAccount(indexRow, "Live");
            SetStatusAccount(indexRow, "Tài khoản live!");
            SetRowColor(indexRow, 2);
        }
        else if (text.contains("https://mbasic.facebook.com/login.php") || text.contains("name=\"login\""))
        {
            SetStatusAccount(indexRow, statusProxy + "No login!");
        }
        else if (text.contains("confirmation"))
        {
            SetStatusAccount(indexRow, statusProxy + "Novery Live!");
            SetRowColor(indexRow, 2);
        }
        else if (text.contains("/login/device-based/validate-pin/"))
        {
            SetStatusAccount(indexRow, statusProxy + "Cookie bị đăng xuất!");
            SetRowColor(indexRow, 2);
        }
        else
        {
            SetStatusAccount(indexRow, statusProxy + "Dạng Checkpoint khác!");
            SetRowColor(indexRow, 1);
        }
    } catch (...) {
        SetStatusAccount(indexRow, statusProxy + "Không check được!");
    }
}


void MainWindow::SetRowColor(int indexRow, int typeColor){
    switch (typeColor) {
    case 1:
        Utils::changeRowColor(ui->tableWidget,indexRow,QColor(255, 118, 117));
        break;
    case 2:
        Utils::changeRowColor(ui->tableWidget,indexRow,QColor(184, 233, 148));
        break;
    default:
        break;
    }
}

void MainWindow::CheckDangCheckpoint(int row){
    QString cellAccount = GetCellAccount(row, "cCookies");
    if (cellAccount.trimmed() == "")
    {
        SetStatusAccount(row, Language::GetValue("Cookie trô\u0301ng!"));
        return;
    }
    // GetCellAccount(row, "cUseragent").trimmed();
    QString text = "";
    int typeProxy = 0;
    if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 9)
    {
        text = GetCellAccount(row, "cProxy");
        typeProxy = (text.endsWith("*1") ? 1 : 0);
        if (text.endsWith("*0") || text.endsWith("*1"))
        {
            text = text.left(text.length() - 2);
        }
    }
    SetStatusAccount(row, Language::GetValue("Checking..."));
    bool isCheckpoint = false;
    CheckDangCheckPoint(row, "", cellAccount, text, typeProxy,  isCheckpoint);
}
void MainWindow::CheckMyCookie(int row){
    try {
        QString text = "";
        GetCellAccount(row, "cId");
        QString cellAccount = GetCellAccount(row, "cCookies");
        if (cellAccount.trimmed() == "")
        {
            SetStatusAccount(row, Language::GetValue("Cookie trô\u0301ng!"));
            return;
        }
        QString userAgent = GetCellAccount(row, "cUseragent").trimmed();
        QString text2 = "";
        int typeProxy = 0;
        if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 9)
        {
            text2 = GetCellAccount(row, "cProxy");
            typeProxy = (text2.endsWith("*1") ? 1 : 0);
            if (text2.endsWith("*0") || text2.endsWith("*1"))
            {
                text2 = text2.left(text2.length() - 2);
            }
        }
        QString text3 = "";
        if (!CommonRequest::CheckLiveCookie(cellAccount, userAgent, text2, typeProxy).startsWith("1|"))
        {
            text3 = "Cookie die";
        }
        else
        {
            text = "Live";
            text3 = "Cookie live";
        }
        SetStatusAccount(row, text3);
        if (text != "")
        {
            SetInfoAccount(row, text);
        }
    } catch (...) {
    }
}
void MainWindow::CheckMyToken(int row){
    try {
        QString text = "";
        GetCellAccount(row, "cId");
        QString cellAccount = GetCellAccount(row, "cCookies");
        QString cellAccount2 = GetCellAccount(row, "cToken");
        if (cellAccount2.trimmed() == "")
        {
            SetStatusAccount(row, Language::GetValue("Token trô\u0301ng!"));
            return;
        }
        QString useragent = GetCellAccount(row, "cUseragent").trimmed();
        QString text2 = "";
        int typeProxy = 0;
        if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 9)
        {
            text2 = GetCellAccount(row, "cProxy");
            typeProxy = (text2.endsWith("*1") ? 1 : 0);
            if (text2.endsWith("*0") || text2.endsWith("*1"))
            {
                text2 = text2.left(text2.length() - 2);
            }
        }
        QString text3 = "";
        if (!CommonRequest::CheckLiveToken(cellAccount, cellAccount2, useragent, text2, typeProxy))
        {
            text3 = "Token die";
        }
        else
        {
            text = "Live";
            text3 = "Token live";
        }
        SetStatusAccount(row, text3);
        if (text != "")
        {
            SetInfoAccount(row, text);
        }

    } catch (...) {
        SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
    }
}


void MainWindow::CheckMyWall(int row, QString tokenTg){
    try {
        GetCellAccount(row,"Id");
        QString cellAccount = GetCellAccount(row,"Uid");
        if (!CheckIsUidFacebook(cellAccount))
        {
            SetStatusAccount(row, Language::GetValue("Uid không hợp lệ!"));
            return;
        }
        QString text = "";
        QString text2 = "";
        QString text3 = CommonRequest::CheckLiveWall(cellAccount);
        if (text3.startsWith("0|"))
        {
            text = "Die";
            text2 = "Wall die";
        }
        else if (text3.startsWith("1|"))
        {
            text = "Live";
            text2 = "Wall live";
        }
        else
        {
            text2 = Language::GetValue("Không check được!");
        }
        SetStatusAccount(row, text2);
        if (text != "")
        {
            SetInfoAccount(row, text);
        }
    } catch (...) {
        SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
    }
}
void MainWindow::SetInfoAccount(int indexRow, QString value){
    DatagridviewHelper::SetStatusDataGridView(ui->tableWidget, indexRow, "cInfo", value);
    SetRowColor(indexRow);
    Common::UpdateFieldToAccount(GetCellAccount(indexRow, "cId"), "info", value);
}
bool MainWindow::CheckIsUidFacebook(QString uid){
    if (Common::IsNumber(uid))
    {
        if (uid.startsWith("1")|| uid.startsWith("6"))
        {
            return true;
        }
    }
    return false;
}
void MainWindow::SetStatusAccount(int indexRow, QString value, int timeWait){
    Common::UpdateFieldToAccount(GetCellAccount(indexRow, "Id"), "status", value);
    switch (timeWait)
    {
    case -1:
        DatagridviewHelper::SetStatusDataGridView(ui->tableWidget, indexRow, "cStatus", value);
        break;
    default:
        DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableWidget, indexRow, "cStatus", timeWait, value);
        break;
    case 0:
        break;
    }
}

QString MainWindow::GetCellAccount(int indexRow, QString column){
    return DatagridviewHelper::GetStatusDataGridView(ui->tableWidget, indexRow, column);
}


void MainWindow::cControl(QString dt){
    try {
        if(dt == "start"){
            ui->btnDeleteFile->setEnabled(false);
            ui->btnEditFile->setEnabled(false);
            ui->btnLoadAcc->setEnabled(false);
            ui->addFileAccount->setEnabled(false);
            ui->frame_4->setEnabled(false);
            ui->btnInteract->setIcon(QIcon(":/img/img/stop-button.png"));
            ui->btnInteract->setText("Dừng tương tác");
            DisableSort();
        }else if(dt=="stop"){
            ui->btnDeleteFile->setEnabled(true);
            ui->btnEditFile->setEnabled(true);
            ui->btnLoadAcc->setEnabled(true);
            ui->addFileAccount->setEnabled(true);
            ui->frame_4->setEnabled(true);
            ui->btnInteract->setIcon(QIcon(":/img/img/play-button.png"));
            ui->btnInteract->setText("Chạy tương tác");
            EnableSort();
        }
    } catch (...) {
    }
}
void MainWindow::DisableSort(){
    try {
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Interactive);
            ui->tableWidget->horizontalHeader()->setSortIndicatorShown(false);
        }
        ui->tableWidget->setSortingEnabled(false);
    } catch (...) {
    }
}
void MainWindow::EnableSort(){
    try {
        ui->tableWidget->setSortingEnabled(true);
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            ui->tableWidget->horizontalHeader()->setSortIndicatorShown(true);
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

