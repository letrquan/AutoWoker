#include "mainwindow.h"
#include "fcauhinhchung.h"
#include "fcauhinhtuongtac.h"
#include "fimportaccount.h"
#include "qnetworkreply.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include "../MCommon/RequestHandle.h"
#include <QNetworkAccessManager>
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
#include "../maxcare/ImapHelper.h"
#include <QClipboard>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include "../maxcare/MessageBoxHelper.h"
#include "../MCommon/ProxyTool.h"
#include "../MCommon/tinsoftproxy.h"
#include "../MCommon/xproxyproxy.h"
#include "../MCommon/tmproxy.h"
#include "../MCommon/proxyv6net.h"
#include "../MCommon/shoplike.h"
#include "../MCommon/minproxy.h"
#include "../MCommon/obcdcom.h"
#include "../Form/fviewchrome.h"
#include "../maxcare/interactsql.h"
#include "../MCommon/account.h"
#include "../MCommon/chrome.h"
#include "../maxcare/Enum/GetContentStatusChrome.h"
#include <QDateTime>
MainWindow::MainWindow(QString tokemem, QString namemem, QString phoneMem, QString maxDeviceMem,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cusModel(new CustomTableModel(this)), statusSQL(new QMap<QString,QString>()),infoSQL(new QMap<QString,QString>())
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
    connect(ui->tableView, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setStyleSheet("QHeaderView::section { background-color: #222831; color: white; }");
    QHeaderView* vHeader = ui->tableView->verticalHeader();
    vHeader->setStyleSheet("QHeaderView::section { background-color: #222831; color: white; }");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->installEventFilter(this);
    connect(this, &MainWindow::updateCellAccount, this, &MainWindow::SetCellAccount, Qt::QueuedConnection);
    connect(this, &MainWindow::updateStatusAccount, this,static_cast<void (MainWindow::*)(int, QString, int)>(&MainWindow::SetStatusAccount), Qt::QueuedConnection);
    connect(this, &MainWindow::updateInfoAccount, this, &MainWindow::SetInfoAccount, Qt::QueuedConnection);
    connect(this, &MainWindow::updateRowColor2, this, static_cast<void (MainWindow::*)(int, int)>(&MainWindow::SetRowColor), Qt::QueuedConnection);
    connect(this, &MainWindow::updateRowColor, this, static_cast<void (MainWindow::*)(int)>(&MainWindow::SetRowColor), Qt::QueuedConnection);
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
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\windows\\CurrentVersion\\Internet Settings", QSettings::NativeFormat);
    
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
    QVariantList allFilesFromDatabase = *CommonSQL::GetAllFilesFromDatabase(true,false);
    for (int i = 0; i < allFilesFromDatabase.size(); ++i) {
        auto rowMap = allFilesFromDatabase[i].toMap();
        ui->cbbThuMuc->addItem(rowMap["name"].toString() , rowMap["id"].toString());
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
        }
        ui->cbbTinhTrang->setCurrentIndex(0);
        on_cbbTinhTrang_currentIndexChanged(0);
    } catch (...) {
    }
}

void MainWindow::OnLoaded(){
    lstMailDomainAw = *EmailHelper::getListMailDomain();
    QFile file("update.ini");
    try {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            // QTextStream in(&file);
            // QString textUpdate = in.readAll();
            // file.close();
            // QString namesoft = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[0].replace("[", "").replace("]", "");
            // QString currentVersion = textUpdate.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts)[1].replace("Version=", "");
            // if(!QFile::exists("AutoUpdate.exe") || QFileInfo("AutoUpdate.exe").size() != 165376 ){
            //     Common::DownloadFile("https://storage.giau.cc/"+namesoft+"/autoupdate.zip");
            // }
        }
        SetupFolder::StartApplication();
        LoadcbbSearch();
        LoadCbbThuMuc(2);
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
void MainWindow::LoadDtgvAccFromDatatable(QVariantList* tableAccount){
    cusModel->loadDataFromDatabase(tableAccount);
    connect(cusModel, &CustomTableModel::checkedCountChanged, this, &MainWindow::CountCheckedAccount);
    ui->tableView->setModel(cusModel);
    QCoreApplication::processEvents();
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
    setColumnVisibility("Id",false);
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
    int columnIndex = Utils::GetIndexByColumnHeader(ui->tableView,headerLabel);
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
    return DatagridviewHelper::GetStatusDataGridView(ui->tableView, indexRow, "Tình Trạng");
}

QString MainWindow::GetStatusAccount(int indexRow){
    QString statusDataGridView = ui->tableView->model()->index(indexRow, Utils::GetIndexByColumnHeader(ui->tableView,"Trạng thái")).data().toString();
    if(statusDataGridView.startsWith("(")){
        
        return statusDataGridView.mid(statusDataGridView.indexOf(')') + 1).trimmed();
    }
    return statusDataGridView;
}

void MainWindow::CountCheckedAccount(int count){
    if(count ==-1){
        count = 0;
        for (int i = 0; i < ui->tableView->model()->rowCount(); i++)
        {
            if (ui->tableView->model()->index(i,Utils::GetIndexByColumnHeader(ui->tableView,"Select")).data(Qt::CheckStateRole) == Qt::Checked)
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
        QSharedPointer<fImportAccount> fImportAccount2(new fImportAccount(text));
        Common::ShowForm(fImportAccount2.data());
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

void MainWindow::KiemTraTaiKhoan(int type, bool useProxy) {
    QThreadPool::globalInstance()->setMaxThreadCount(SettingsTool::GetSettings("configGeneral").GetValueInt("nudHideThread", 10));
    auto tokenTrunggian = SettingsTool::GetSettings("configGeneral").GetValue("token");
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    
    connect(watcher, &QFutureWatcher<void>::started, this, [this]() {
        cControl("start");
    });
    connect(watcher, &QFutureWatcher<void>::finished, this, [this]() {
        cControl("database");
        if(!statusSQL->isEmpty()){
            if (CommonSQL::UpdateStatuses(*statusSQL, "status")) {
                statusSQL->clear();
            }
        }
        if(!infoSQL->isEmpty()){
            if (CommonSQL::UpdateStatuses(*infoSQL, "info")) {
                infoSQL->clear();
            }
        }
        cControl("stop");
    });
    
    QFuture<void> future = QtConcurrent::run([this, tokenTrunggian, type]() {
        switch (type) {
        case 0:
            checkAccounts([this, tokenTrunggian](int num) {
                QtConcurrent::run(&MainWindow::CheckMyWall, this, num, tokenTrunggian);
            });
            break;
            
        case 3:
            checkAccounts([this](int num) {
                QtConcurrent::run(&MainWindow::CheckDangCheckpoint, this, num);
            });
            break;
            
        default:
            break;
        }
        
        // auto tickCount = QDateTime::currentSecsSinceEpoch();
        // while (QThreadPool::globalInstance()->activeThreadCount() > 0 && QDateTime::currentSecsSinceEpoch() - tickCount <= 60) {
        //     QMetaObject::invokeMethod(QCoreApplication::instance(), []() {
        //             QCoreApplication::processEvents();
        //         }, Qt::BlockingQueuedConnection);
        //     QThread::sleep(1);
        // }
    });
    
    watcher->setFuture(future);
}

void MainWindow::checkAccounts(const std::function<void(int)>& task) {
    int num = 0;
    while (num < ui->tableView->model()->rowCount() && !isStop) {
        if (ui->tableView->model()->index(num, 0).data(Qt::CheckStateRole) == Qt::Checked) {
            task(num);
        }
        num++;
    }
}


void MainWindow::CheckNameVN(int row){
    try
    {
        QString text = GetCellAccount(row, "cName");
        QString text2;
        if (text.trimmed() == "")
        {
            text2 = Language::GetValue("Không tìm thấy tên!");
        }
        else if (Common::IsVNName(text))
        {
            text2 = Language::GetValue("Yes");
        }
        else
        {
            text2 = Language::GetValue("No");
        }
        SetStatusAccount(row, text2, -1);
    }
    catch(...)
    {
        SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"), -1);
    }
}

void MainWindow::CheckInfoUid(int row, bool useProxy){
    try {
        QString cellAccount = GetCellAccount(row, "Id");
        QString cellAccount2 = GetCellAccount(row, "Uid");
        QString text = "";
        int typeProxy = 0;
        if(useProxy){
            text = GetCellAccount(row, "cProxy");
            typeProxy = (text.endsWith("*1") ? 1 : 0);
            if (text.endsWith("*0") || text.endsWith("*1"))
            {
                text = text.left(text.length() - 2);
            }
        }
        if(!CheckIsUidFacebook(cellAccount2)){
            SetStatusAccount(row, Language::GetValue("Uid không hợp lệ!"));
            return;
        }
        QString text2 = "";
        QString text3 = CommonRequest::CheckInfoUsingUid(cellAccount2, text, typeProxy);
        if (text3.startsWith("0|"))
        {
            if (CommonRequest::CheckLiveWall(cellAccount2).startsWith("0|"))
            {
                SetStatusAccount(row, Language::GetValue("Tài khoản Die!"));
                SetInfoAccount(row, "Die");
            }
            else
            {
                SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
            }
        }
        else if (text3.startsWith("1|"))
        {
            QStringList array = text3.split('|');
            QString value = array[1];
            QString value2 = array[2];
            QString value3 = array[3];
            CommonSQL::UpdateMultiFieldToAccount(cellAccount, "name|friends|dateCreateAcc", value+"|"+value2+"|"+value3);
            emit updateCellAccount(row, "Tên", value);
            emit updateCellAccount(row, "Bạn Bè", value2);
            emit updateCellAccount(row, "Ngày tạo tài khoản", value3);
            SetInfoAccount(row, "Live");
            text2 = Language::GetValue("Câ\u0323p nhâ\u0323t thông tin tha\u0300nh công!");
            SetStatusAccount(row, text2);
        }
        else
        {
            SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
        }
    } catch (...) {
        SetStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
    }
    
}
void MainWindow::SetCellAccount(int indexRow, QString column, QVariant value, bool isAllowEmptyValue){
    if ((!(column == "Uid") || !(value.toString().trimmed() == "")) && (isAllowEmptyValue || !(value.toString().trimmed() == "")))
    {
        DatagridviewHelper::SetStatusDataGridView(ui->tableView, indexRow, column, value);
    }
}


void MainWindow::CheckAccountMail(int row){
    try {
        QString text = "";
        QString text2 = "";
        text = ui->tableView->model()->index(row, Utils::GetIndexByColumnHeader(ui->tableView,"Email")).data().toString();
        text2 = ui->tableView->model()->index(row, Utils::GetIndexByColumnHeader(ui->tableView,"Mật khẩu Mail")).data().toString();
        if (text == "" || text2 == "")
        {
            SetStatusAccount(row, Language::GetValue("Không tìm thấy mail!"));
        }
        else if (ImapHelper::CheckConnectImap(text, text2))
        {
            SetStatusAccount(row, Language::GetValue("Tài khoản mail: live!"));
        }
        else
        {
            SetStatusAccount(row, Language::GetValue("Tài khoản mail: die!"));
        }
    } catch (...) {
        SetStatusAccount(row, Language::GetValue("Lỗi!"));
    }
}

void MainWindow::CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282){
    try {
        RequestHandle requestXNet(cookie, "Mozilla/5.0 (windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);
        isCheckpoint282 = false;
        QString text = requestXNet.RequestGet("https://mbasic.facebook.com/");
        QString url = requestXNet.GetUrl();
        if(url.contains("checkpoint/disabled")){
            emit updateStatusAccount(indexRow, statusProxy + "Vô hiệu hóa!");
            emit updateInfoAccount(indexRow, "Checkpoint: vhh");
            emit updateRowColor2(indexRow, 1);
        }else if (url.contains("828281030927956"))
        {
            QString text2 = "956";
            text2 = ((!text.contains("/stepper/")) ? (text2 + "-Tìm hiểu thêm") : (text2 + "-Bắt đầu"));
            emit updateStatusAccount(indexRow, statusProxy + "Checkpoint " + text2 + "!");
            emit updateInfoAccount(indexRow, "Checkpoint: " + text2);
            emit updateRowColor2(indexRow, 1);
        }else if (url.contains("1501092823525282"))
        {
            emit updateInfoAccount(indexRow, "Checkpoint: 282");
            emit updateStatusAccount(indexRow, statusProxy + "Checkpoint 282!");
            isCheckpoint282 = true;
        }
        else if (url.contains("facebook.com/gettingstarted") || (text.contains("href=\"/menu/bookmarks/") && text.contains("id=\"mbasic_logout_button\"")))
        {
            emit updateInfoAccount(indexRow, "Live");
            emit updateStatusAccount(indexRow, "Tài khoản live!");
            emit updateRowColor2(indexRow, 2);
        }
        else if (text.contains("https://mbasic.facebook.com/login.php") || text.contains("name=\"login\""))
        {
            emit updateStatusAccount(indexRow, statusProxy + "No login!");
        }
        else if (text.contains("confirmation"))
        {
            emit updateStatusAccount(indexRow, statusProxy + "Novery Live!");
            emit updateRowColor2(indexRow, 2);
        }
        else if (text.contains("/login/device-based/validate-pin/"))
        {
            emit updateStatusAccount(indexRow, statusProxy + "Cookie bị đăng xuất!");
            emit updateRowColor2(indexRow, 2);
        }
        else
        {
            emit updateStatusAccount(indexRow, statusProxy + "Dạng Checkpoint khác!");
            emit updateRowColor2(indexRow, 1);
        }
    } catch (...) {
        emit updateStatusAccount(indexRow, statusProxy + "Không check được!");
    }
}


void MainWindow::SetRowColor(int indexRow, int typeColor){
    switch (typeColor) {
    case 1:
        Utils::changeRowColor(ui->tableView,indexRow,QColor(255, 118, 117));
        break;
    case 2:
        Utils::changeRowColor(ui->tableView,indexRow,QColor(184, 233, 148));
        break;
    default:
        break;
    }
}

void MainWindow::CheckDangCheckpoint(int row){
    QString cellAccount = GetCellAccount(row, "Cookies");
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


void MainWindow::CheckMyWall(int row, QString tokenTg) {
    try {
        GetCellAccount(row, "Id");
        QString cellAccount = GetCellAccount(row, "Uid");
        if (!CheckIsUidFacebook(cellAccount)) {
            emit updateStatusAccount(row, Language::GetValue("Uid không hợp lệ!"));
            return;
        }
        emit updateStatusAccount(row, Language::GetValue("Checking.."));
        QString text3 = CommonRequest::CheckLiveWall(cellAccount);
        QString text = "";
        QString text2 = "";
        if (text3.startsWith("0|")) {
            text = "Die";
            text2 = "Wall die";
        } else if (text3.startsWith("1|")) {
            text = "Live";
            text2 = "Wall live";
        } else {
            text2 = Language::GetValue("Không check được!");
        }
        emit updateStatusAccount(row, text2);
        if (text != "") {
            emit updateInfoAccount(row, text);
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception in CheckMyWall:" << e.what();
    } catch (...) {
        emit updateStatusAccount(row, Language::GetValue("Không check đươ\u0323c!"));
    }
}

void MainWindow::SetInfoAccount(int indexRow, QString value){
    DatagridviewHelper::SetStatusDataGridView(ui->tableView, indexRow, "Tình Trạng", value);
    emit updateRowColor(indexRow);
    // QtConcurrent::run(&Common::UpdateFieldToAccount, GetCellAccount(indexRow, "Id"), "info", value);
    infoSQL->insert(GetCellAccount(indexRow, "Id"),value);
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
    // QtConcurrent::run(&Common::UpdateFieldToAccount, GetCellAccount(indexRow, "Id"), "status", value);
    statusSQL->insert(GetCellAccount(indexRow, "Id"),value);
    switch (timeWait)
    {
    case -1:
        DatagridviewHelper::SetStatusDataGridView(ui->tableView, indexRow, "Trạng thái", value);
        // cusModel->setData(cusModel->index(indexRow,Utils::GetIndexByColumnHeader(ui->tableView,"Trạng thái")),value,Qt::EditRole);
        break;
    default:
        DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", timeWait, value);
        break;
    case 0:
        break;
    }
}

QString MainWindow::GetCellAccount(int indexRow, QString column){
    return DatagridviewHelper::GetStatusDataGridView(ui->tableView, indexRow, column);
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
        for (int column = 0; column < ui->tableView->model()->columnCount(); ++column) {
            ui->tableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Interactive);
            ui->tableView->horizontalHeader()->setSortIndicatorShown(false);
        }
        ui->tableView->setSortingEnabled(false);
    } catch (...) {
    }
}
void MainWindow::EnableSort(){
    try {
        ui->tableView->setSortingEnabled(true);
        for (int column = 0; column < ui->tableView->model()->columnCount(); ++column) {
            ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
        }
    } catch (...) {
    }
}
void MainWindow::on_cbbThuMuc_currentIndexChanged(int index)
{
    QString text = ui->cbbThuMuc->itemData(index).toString();
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
    QString text = ui->cbbThuMuc->currentData().toString();
    if(!(text == "-1")){
        if (text == "999999")
        {
            LoadAccountFromFile(fChonThuMuc::lstChooseIdFiles, ui->cbbTinhTrang->itemText(index));
        }
        else
        {
            LoadAccountFromFile(GetIdFile(), ui->cbbTinhTrang->itemText(index));
        }
    }else{
        LoadAccountFromFile(QList<QString>(), ui->cbbTinhTrang->itemText(index));
    }
    indexCbbTinhTrangOld =index;
    LoadConfigManHinh();
}

void MainWindow::showContextMenu(const QPoint &pos) {
    // Create the context menu
    QMenu contextMenu(this);
    contextMenu.setStyleSheet("background-color: #424769; color: white;");
    // Create main actions with icons
    QAction *actionSelect = new QAction(QIcon(":/img/img/select-all.png"), "Chọn", this);
    QAction *actionDeselect = new QAction(QIcon(":/img/img/check.png"),"Bỏ chọn tất cả", this);
    QAction *actionHideList = new QAction(QIcon(":/img/img/hide.png"),"Ẩn khỏi danh sách", this);
    QAction *actionInputProxy = new QAction(QIcon(":/img/img/up-arrow.png"),"Nhập Proxy", this);
    QAction *actionInputUserAgent = new QAction(QIcon(""),"Nhập Useragent", this);
    QAction *actionCopy = new QAction(QIcon(""),"Copy", this);
    QAction *actionOpenProgram = new QAction(QIcon(""),"Mở trình duyệt", this);
    QAction *actionDeleteAccount = new QAction(QIcon(""),"Xóa tài khoản", this);
    QAction *actionCheckAccount = new QAction("Kiểm tra tài khoản", this);
    
    // connect(actionSelect, &QAction::triggered, this, &MainWindow::onActionSelect);
    connect(actionDeselect, &QAction::triggered, this, &MainWindow::onActionDeselect);
    // connect(actionHideList, &QAction::triggered, this, &MainWindow::onActionHideList);
    // connect(actionInputProxy, &QAction::triggered, this, &MainWindow::onActionInputProxy);
    // connect(actionInputUserAgent, &QAction::triggered, this, &MainWindow::onActionInputUserAgent);
    connect(actionCopy, &QAction::triggered, this, &MainWindow::onActionCopy);
    // connect(actionOpenProgram, &QAction::triggered, this, &MainWindow::onActionOpenProgram);
    // connect(actionDeleteAccount, &QAction::triggered, this, &MainWindow::onActionDeleteAccount);
    
    // Create a submenu for "Chọn"
    QMenu *subMenuSelect = new QMenu("Chọn", this);
    subMenuSelect->setStyleSheet("background-color: #424769; color: white;");
    QAction *subActionAll = new QAction("Tất cả", this);
    QAction *subActionBlackList = new QAction("Bôi đen", this);
    QAction *subActionCondition = new QAction("Tình trạng", this);
    QAction *subActionStatus = new QAction("Trạng thái", this);
    QAction *subActionSelectByUID = new QAction("Chọn danh sách theo UID", this);
    
    connect(subActionAll, &QAction::triggered, this, &MainWindow::onSubActionAll);
    // connect(subActionBlackList, &QAction::triggered, this, &MainWindow::onSubActionBlackList);
    // connect(subActionCondition, &QAction::triggered, this, &MainWindow::onSubActionCondition);
    // connect(subActionStatus, &QAction::triggered, this, &MainWindow::onSubActionStatus);
    // connect(subActionSelectByUID, &QAction::triggered, this, &MainWindow::onSubActionSelectByUID);
    // Add actions to the submenu
    subMenuSelect->addAction(subActionAll);
    subMenuSelect->addAction(subActionBlackList);
    subMenuSelect->addAction(subActionCondition);
    subMenuSelect->addAction(subActionStatus);
    subMenuSelect->addAction(subActionSelectByUID);
    
    
    
    //sub menu for Kiểm tra tài khoản
    QMenu *subMenuCheckAccount = new QMenu("Kiểm tra tài khoản", this);
    subMenuCheckAccount->setStyleSheet("background-color: #424769; color: white;");
    QAction *checkWall = new QAction("Check Wall", this);
    QAction *checkInfoUid = new QAction("Check Info Uid", this);
    QAction *checkCookie = new QAction("Check Cookies", this);
    QAction *checkToken = new QAction("Check Token", this);
    QAction *checkAvatar = new QAction("Check Avatar", this);
    QAction *checkProfile = new QAction("Check Profile", this);
    QAction *checkBackup = new QAction("Check Back Up", this);
    
    
    subMenuCheckAccount->addAction(checkWall);
    subMenuCheckAccount->addAction(checkInfoUid);
    subMenuCheckAccount->addAction(checkToken);
    subMenuCheckAccount->addAction(checkCookie);
    subMenuCheckAccount->addAction(checkAvatar);
    subMenuCheckAccount->addAction(checkProfile);
    subMenuCheckAccount->addAction(checkBackup);
    
    
    connect(checkWall, &QAction::triggered, this, &MainWindow::checkWall);
    connect(checkCookie, &QAction::triggered, this, &MainWindow::checkCookie);
    
    // Add the submenu to the main action
    actionSelect->setMenu(subMenuSelect);
    actionCheckAccount->setMenu(subMenuCheckAccount);
    // Create a QWidgetAction with a QLineEdit for "Ghi chú"
    QWidgetAction *widgetActionNote = new QWidgetAction(this);
    QLineEdit *lineEditNote = new QLineEdit(this);
    widgetActionNote->setDefaultWidget(lineEditNote);
    
    // Add actions and submenus to the context menu
    contextMenu.addAction(actionSelect);
    contextMenu.addAction(actionDeselect);
    contextMenu.addAction(actionHideList);
    contextMenu.addAction(actionInputProxy);
    contextMenu.addAction(actionInputUserAgent);
    contextMenu.addAction(actionCopy);
    contextMenu.addAction(actionOpenProgram);
    contextMenu.addAction(actionDeleteAccount);
    contextMenu.addAction(actionCheckAccount);
    contextMenu.addSeparator();
    contextMenu.addAction(widgetActionNote);
    contextMenu.addAction(widgetActionNote);
    
    
    // Show the context menu at the cursor position
    contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos));
}
void MainWindow::onSubActionAll(){
    for(int i =0; i<ui->tableView->model()->rowCount();i++){
        ui->tableView->model()->setData(ui->tableView->model()->index(i,0),Qt::Checked,Qt::CheckStateRole);
    }
}
void MainWindow::onActionDeselect(){
    for(int i =0; i<ui->tableView->model()->rowCount();i++){
        ui->tableView->model()->setData(ui->tableView->model()->index(i,0),Qt::Unchecked,Qt::CheckStateRole);
    }
}
void MainWindow::checkWall(){
    KiemTraTaiKhoan(0);
}
void MainWindow::checkCookie(){
    KiemTraTaiKhoan(3);
}
void MainWindow::onActionCopy(){
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (selection->hasSelection()) {
        QModelIndex index = selection->currentIndex();
        QString cellValue = index.data().toString();
        
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(cellValue);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    Common::ShowForm(new fCauhinhtuongtac());
}


void MainWindow::on_pushButton_clicked()
{
    JSON_Settings data = *new JSON_Settings();
    Common::ShowForm(new fCauHinhChung(data));
    if(data.GetValueBool("isChangePathDatabase")){
        LoadCbbThuMuc();
        indexCbbThuMucOld = -1;
        ui->cbbThuMuc->setCurrentIndex(-1);
        ui->cbbThuMuc->setCurrentIndex(0);
    }
}


void MainWindow::on_btnInteract_clicked()
{
    try
    {
        if (ui->btnInteract->text() == "Dừng tương tác")
        {
            isStop = true;
            ui->btnInteract->setEnabled(false);
            ui->btnInteract->setText(Language::GetValue("Đang dư\u0300ng..."));
        }
        else
        {
            JSON_Settings jSON_Settings = *new JSON_Settings();
            jSON_Settings.Update("Interact", true);
            Execute(jSON_Settings);
        }
    }
    catch(...)
    {
    }
}

void MainWindow::Execute(const JSON_Settings &settings){
    try {
        if(!IsChooseRow()){
            return;
        }
        QAtomicInt maxThread = SettingsTool::GetSettings("configGeneral").GetValueInt("nudInteractThread", 3);
        lstProxyTool = GetListProxy(maxThread);
        if(!lstProxyTool.isEmpty() && lstProxyTool.count() ==0){
            MessageBoxHelper::Show("Proxy không đủ, vui lòng cấu hình lại!", 2);
            return;
        }
        QList<int> lstPossition;
        for (int i = 0; i < maxThread; i++)
        {
            lstPossition.append(0);
        }
        cControl("start");
        if (SettingsTool::GetSettings("configGeneral").GetValueBool("ckbAddChromeIntoForm"))
        {
            OpenFormViewChrome();
        }
        dic_GroupShared = *new QMap<QString, QStringList>();
        dic_GroupPosted = *new QMap<QString, QStringList>();
        isCountCheckAccountWhenChayTuongTac = true;
        isStop = false;
        int curChangeIp = 0;
        bool isChangeIPSuccess = false;
        checkDelayChrome = 0;
        QFuture<void> thread= QtConcurrent::run([this, settings, maxThread, lstPossition, &curChangeIp, &isChangeIPSuccess]() mutable {
            if (const_cast<JSON_Settings&>(settings).GetValueBool("Interact")){
                QStringList list;
                QString idKichBan="";
                QString text = "";
                int num = SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudSoLuotChay", 1);
                if (num == 0)
                {
                    num = 1;
                }
                for (int j = 0; j < num; j++){
                    if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRepeatAll")){
                        if (num > 1) {
                            QString templateStr = Language::GetValue("Lượt %1/%2. ");
                            text = templateStr.arg(j + 1).arg(num);
                        } else {
                            text = "";
                        }
                        if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("RepeatAllVIP")){
                            list = SettingsTool::GetSettings("configInteractGeneral").GetValueList("lstIdKichBan");
                            if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRandomKichBan")){
                                list = Common::ShuffleList(list);
                                list = Common::ShuffleList(list);
                                list = Common::ShuffleList(list);
                            }
                        }else{
                            list.append(SettingsTool::GetSettings("configInteractGeneral").GetValue("cbbKichBan"));
                        }
                    }else{
                        list.append(SettingsTool::GetSettings("configInteractGeneral").GetValue("cbbKichBan"));
                    }
                    for (int k = 0; k < list.count(); k++){
                        if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbXoaCache")){
                            int maxThread2 = SettingsTool::GetSettings("configGeneral").GetValueInt("nudHideThread", 10);
                            QThreadPool::globalInstance()->setMaxThreadCount(maxThread2);
                            QFuture<void> thread2 = QtConcurrent::run([this]() {
                                int num19 = 0;
                                while (num19 < ui->tableView->model()->rowCount()){
                                    if(ui->tableView->model()->index(num19,0).data(Qt::CheckStateRole).toBool()){
                                        QFuture<void> future = QtConcurrent::run([this, &num19]() {
                                            emit updateStatusAccount(num19, Language::GetValue("Đang xóa Cache Profile..."));
                                            DeleteCacheProfile(num19);
                                        });

                                    }
                                    num19++;
                                }
                            });
                        }
                        if(isStop){
                            break;
                        }
                        idKichBan = list[k];
                        if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRandomThuTuTaiKhoan"))
                        {
                            QMetaObject::invokeMethod(ui->tableView, [this]() {
                                    RandomThuTuTaiKhoan();
                                }, Qt::QueuedConnection);
                        }
                        dicUidNhom = GetDictionaryIntoHanhDong(idKichBan, "HDThamGiaNhomUid");
                        dicUidNhom2 = GetDictionaryIntoHanhDong(idKichBan, "HDThamGiaNhomUidv2");
                        dicUidCaNhan = GetDictionaryIntoHanhDong(idKichBan, "HDKetBanTepUid");
                        dicUidCaNhan2 = GetDictionaryIntoHanhDong(idKichBan, "HDKetBanTepUidv2");
                        dicUidBaivietProfile = GetDictionaryIntoHanhDong(idKichBan, "HDBaiVietProfile");
                        dicUidSpamBaiViet = GetDictionaryIntoHanhDong(idKichBan, "HDSpamBaiViet");
                        dicUidSpamBaiVietv2 = GetDictionaryIntoHanhDong(idKichBan, "HDSpamBaiVietv2");
                        dicCommentSpamBaiViet = GetDictionaryIntoHanhDong(idKichBan, "HDSpamBaiViet", "txtComment");
                        dicCommentSpamBaiVietv2 = GetDictionaryIntoHanhDong(idKichBan, "HDSpamBaiVietv2", "txtComment");
                        dicUidTinNhanProfile = GetDictionaryIntoHanhDong(idKichBan, "HDBuffTinNhanProfile");
                        dicKetBanUidNew = GetDictionaryIntoHanhDong(idKichBan, "HDKetBanTepUidNew", "txtLink");
                        dicBuffLikeComment_Comment = GetDictionaryIntoHanhDong(idKichBan, "HDBuffLikeComment", "txtComment");
                        dicBuffLikeComment_CommentGoc = GetDictionaryIntoHanhDong(idKichBan, "HDBuffLikeComment", "txtComment");
                        dicDangStatus_NoiDung = GetDictionaryIntoHanhDong(idKichBan, "HDDangStatus", "txtNoiDung");
                        dicDangStatus_NoiDungGoc = GetDictionaryIntoHanhDong(idKichBan, "HDDangStatus", "txtNoiDung");
                        dicDangStatusV2_NoiDung = GetDictionaryIntoHanhDong(idKichBan, "HDDangStatusV2", "txtNoiDung");
                        dicDangStatusV2_NoiDungGoc = GetDictionaryIntoHanhDong(idKichBan, "HDDangStatusV2", "txtNoiDung");
                        dicDangBai_NoiDung = GetDictionaryIntoHanhDong(idKichBan, "HDDangBai", "txtNoiDung");
                        dicDangBai_NoiDungGoc = GetDictionaryIntoHanhDong(idKichBan, "HDDangBai", "txtNoiDung");
                        dicUidPhanHoiComment = GetDictionaryIntoHanhDong(idKichBan, "HDPhanHoiBinhLuan");
                        dicIdBaiViet = GetDictionaryIntoHanhDong(idKichBan, "HDBuffLikeComment", "txtIdPost");
                        dicIdBaiVietClone = GetDictionaryIntoHanhDong(idKichBan, "HDDangBaiTheoID", "txtIdPost");
                        dicIdPageBuff = GetDictionaryIntoHanhDong(idKichBan, "HDBuffFollowLikePage");
                        dicHDShareBaiTut_txtLinkChiaSe = GetDictionaryIntoHanhDong(idKichBan, "HDShareBaiTut", "txtLinkChiaSe");
                        dicHDLinkToInstagram_txtBio = GetDictionaryIntoHanhDong(idKichBan, "HDLinkToInstagram", "txtBio");
                        dicHDLinkToInstagram_txtBioGoc = GetDictionaryIntoHanhDong(idKichBan, "HDLinkToInstagram", "txtBio");
                        dicHDReviewPage_txtUid = GetDictionaryIntoHanhDong(idKichBan, "HDReviewPage");
                        dic_HDNhanTinBanBe_txtTinNhan = GetDictionaryIntoHanhDong(idKichBan, "HDNhanTinBanBe", "txtTinNhan");
                        dic_HDNhanTinBanBe_txtTinNhan_Goc = GetDictionaryIntoHanhDong(idKichBan, "HDNhanTinBanBe", "txtTinNhan");
                        dic_HDDangBai_lstNhomTuNhap = GetDictionaryIntoHanhDong(idKichBan, "HDDangBai", "lstNhomTuNhap");
                        dic_HDDangBai_txtIdPost = GetDictionaryIntoHanhDong(idKichBan, "HDDangBai", "txtIdPost");
                        dic_HDTuongTacLivestream_txtComment = GetDictionaryIntoHanhDong(idKichBan, "HDTuongTacLivestream", "txtComment");
                        dic_HDAddMail_lstHotmail = GetDictionaryIntoHanhDong(idKichBan, "HDAddMail", "lstHotmail");
                        dic_HDUpAvatar_lstImage = *new QMap<QString, QStringList>();
                        dic_HDUpCover_lstImage = *new QMap<QString, QStringList>();
                        dic_BuffLikeComment_LimitPerLink = *new QMap<QString, QMap<QString,int>>();
                        dic_HDPhanHoiBinhLuan_Comment = GetDictionaryIntoHanhDong(idKichBan, "HDPhanHoiBinhLuan", "txtComment");
                        ReadResultSpam();
                        dicCommentPathOld = *new QMap<QString, QStringList>();
                        dicCommentPathToRun = *new QMap<QString, QStringList>();
                        dicImagePathOld = *new QMap<QString, QStringList>();
                        dicImagePathToRun = *new QMap<QString, QStringList>();
                        if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 8 && SettingsTool::GetSettings("configGeneral").GetValueInt("typeRunXproxy") == 1)
                        {
                            for (int l = 0; l < lstProxyTool.count(); l++)
                            {
                                (qobject_cast<XproxyProxy *>(lstProxyTool[l]))->resetProxy();
                            }
                        }
                        if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 14)
                        {
                            for (int m = 0; m < listObcDcom.count(); m++)
                            {
                                listObcDcom[m]->ResetDcom();
                            }
                        }
                        QFuture<void> thread3 = QtConcurrent::run([this, maxThread, lstPossition, idKichBan, settings, curChangeIp, isChangeIPSuccess] () mutable {
                            try {
                                int num13 = 0;
                                while(num13<ui->tableView->model()->rowCount() && !isStop){
                                    if(ui->tableView->model()->index(num13,Utils::GetIndexByColumnHeader(ui->tableView,"Select")).data(Qt::CheckStateRole).toBool()){
                                        if(isStop){
                                            break;
                                        }
                                        if(lstThread.count() < maxThread){
                                            if (isStop)
                                            {
                                                break;
                                            }
                                            QFuture<void> thread6 = QtConcurrent::run([this, &lstPossition, idKichBan, settings, num13] () mutable {
                                                int indexOfPossitionApp2;
                                                {
                                                    QMutexLocker locker(&mutex);
                                                    indexOfPossitionApp2 = Common::GetIndexOfPositionApp(lstPossition);
                                                }
                                                try {
                                                    ExcuteOneThread(num13, indexOfPossitionApp2, idKichBan, settings);
                                                    {
                                                        QMutexLocker locker(&mutex);
                                                        Common::FillIndexPossition(lstPossition,indexOfPossitionApp2);
                                                    }
                                                    QString p = "Proxy chưa ủy quyền!";
                                                    if (!SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRepeatAll") || GetInfoAccount(num13) != "Live" || GetStatusAccount(num13).toLower().contains("checkpoint") || GetStatusAccount(num13).toLower().contains("invalid username or password") || GetStatusAccount(num13).toLower().contains(p.toLower()))
                                                    {
                                                        emit updateCellAccount(num13, "Select", Qt::Unchecked);
                                                    }
                                                } catch (const std::exception &ex6) {
                                                    QString ex6Str = QString::fromStdString(ex6.what());
                                                    if (ex6Str.contains("Thread was being aborted.")) {
                                                        Common::FillIndexPossition(lstPossition, indexOfPossitionApp2);
                                                        if (!SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRepeatAll")) {
                                                            emit updateCellAccount(num13, "Select", Qt::Unchecked);
                                                        }
                                                    }
                                                }
                                            });
                                            lstThread.append(&thread6);
                                            Common::DelayTime(1);
                                        }else{
                                            if (isStop)
                                            {
                                                break;
                                            }
                                            if ((SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 7 && SettingsTool::GetSettings("configGeneral").GetValueBool("ckbWaitDoneAllTinsoft")) || (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 8 && SettingsTool::GetSettings("configGeneral").GetValueBool("ckbWaitDoneAllXproxy")) || (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 10 && SettingsTool::GetSettings("configGeneral").GetValueBool("ckbWaitDoneAllTMProxy")))
                                            {
                                                for (int num14 = 0; num14 < lstThread.count(); num14++)
                                                {
                                                    lstThread[num14]->waitForFinished();
                                                    lstThread.removeAt(num14--);
                                                }
                                            }else if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 1 || SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 2){
                                                for (int num15 = 0; num15 < lstThread.count(); num15++)
                                                {
                                                    lstThread[num15]->waitForFinished();
                                                    lstThread.removeAt(num15--);
                                                }
                                                if (isStop)
                                                {
                                                    break;
                                                }
                                                {
                                                    QMutexLocker locker(&mutex);
                                                    curChangeIp++;
                                                }
                                                if (curChangeIp >= SettingsTool::GetSettings("configGeneral").GetValueInt("ip_nudChangeIpCount", 1)){
                                                    for (int num16 = 0; num16 < 3; num16++)
                                                    {
                                                        isChangeIPSuccess = Common::ChangeIP(SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp"), SettingsTool::GetSettings("configGeneral").GetValueInt("typeDcom"), SettingsTool::GetSettings("configGeneral").GetValue("ip_txtProfileNameDcom"), SettingsTool::GetSettings("configGeneral").GetValue("txtUrlHilink"), SettingsTool::GetSettings("configGeneral").GetValueInt("ip_cbbHostpot"), SettingsTool::GetSettings("configGeneral").GetValue("ip_txtNordVPN"));
                                                        if (isChangeIPSuccess)
                                                        {
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    num13++;
                                    if (isStop)
                                    {
                                        break;
                                    }
                                }
                            } catch (...) {
                            }
                        });
                    }
                }
            }
        });
    } catch (...) {
    }
}

void MainWindow::ExcuteOneThread(int indexRow, int indexPos, QString idKichBan, JSON_Settings settings){
    int limitTimeRun = 0;
    if (settings.GetValueBool("Interact") && SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGioiHanThoiGianChayTaiKhoan"))
    {
        limitTimeRun = QRandomGenerator::global()->bounded(SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayTaiKhoanFrom"), SettingsTool::GetSettings("configInteractGeneral").GetValueInt("nudThoiGianChayTaiKhoanTo") + 1);
    }
    Account* account = new Account(QThread::currentThread(), limitTimeRun);
    QString proxy = "";
    Chrome* chrome = nullptr;
    int num = 0;
    QString statusProxy = "";
    int typeProxy = 0;
    QString ip = "";
    TinsoftProxy* tinsoft = nullptr;
    XproxyProxy* xproxy = nullptr;
    TMProxy* tmproxy = nullptr;
    ProxyV6Net* proxyWeb = nullptr;
    ShopLike* shopLike = nullptr;
    MinProxy* minProxy = nullptr;
    ObcProxy* obcProxy = nullptr;
    bool flag = false;
    QString text = "";
    int checkPostSuccess = 0;
    int num2 = 0;
    bool flag2 = false;
    bool flag3 = false;
    QString text2 = "";
    int num3 = 0;
    int num4 = 0;
    QString check_HDNhanTinBanBe = "";
    QString check_HDKetBanTepUid = "";
    QString check_HDKetBanGoiY = "";
    QString check_HDXoaSdt = "";
    QString check_HDAddMail = "";
    QString check_HDXoaMail = "";
    QString check_HDDoiMatKhau = "";
    QString check_HDDoiTen = "";
    QString check_HDUpAvatar = "";
    QString check_HDUpCover = "";
    QString check_HDOnOff2FA = "";
    QString text177 = "";
    QString text3 = GetCellAccount(indexRow, "Uid");
    QString cellAccount = GetCellAccount(indexRow, "Id");
    QString cellAccount2 = GetCellAccount(indexRow, "Email");
    QString cellAccount3 = GetCellAccount(indexRow, "Mật khẩu Mail");
    QString cellAccount4 = GetCellAccount(indexRow, "Mã 2FA");
    QString cellAccount5 = GetCellAccount(indexRow, "Mật khẩu");
    QString text4 = GetCellAccount(indexRow, "Cookies");
    QString text5 = GetCellAccount(indexRow, "Token");
    QString cellAccount6 = GetCellAccount(indexRow, "Useragent");
    if (text3.isEmpty())
    {
        QRegularExpression regex("c_user=(\\d+)");
        QRegularExpressionMatch match = regex.match(text4);
        
        if (match.hasMatch())
        {
            text3 = match.captured(1);
        }
    }
    try {
        if(SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCheckLiveUid") && CheckIsUidFacebook(text3) && CommonRequest::CheckLiveWall(text3).startsWith("0|") && settings.GetValueBool("Interact")){
            emit updateInfoAccount(indexRow, "Die");
            emit updateStatusAccount(indexRow, Language::GetValue("Tài khoản Die!"));
            num2 =1;
        }else if(isStop){
            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
            num2 = 1;
        }else{
            GetProxy(indexRow,  isStop,  proxy,  typeProxy,  statusProxy,  ip,  tinsoft,  xproxy,  tmproxy,  proxyWeb,  shopLike,  minProxy,  obcProxy);
            if (isStop)
            {
                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                num2 = 1;
            }else{
                if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP")){
                    if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 0 || SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 1 || SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 2 || SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 9){
                        if (proxy != "")
                        {
                            statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                        }
                        emit updateStatusAccount(indexRow, statusProxy + "Check IP...");
                        bool flag4 = false;
                        int num5 = 0;
                        while (num5 < 30)
                        {
                            Common::DelayTime(1.0);
                            ip = Common::CheckProxyNew(proxy, typeProxy);
                            if (ip != "")
                            {
                                flag4 = true;
                                break;
                            }
                            if (!isStop)
                            {
                                num5++;
                                continue;
                            }
                            goto IL_0396;
                        }
                        if (!flag4)
                        {
                            if (proxy != "")
                            {
                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Không thể kết nối proxy!"));
                            }
                            else
                            {
                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Không có kết nối Internet!"));
                            }
                            num2 = 1;
                            goto IL_5233;
                        }
                    }
                    statusProxy = "(IP: +"+proxy+"=>"+ip+") ";
                }
                if (isStop)
                {
                    emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                    num2 = 1;
                }else{
                    try {
                        bool flag5 = false;
                        QString text6 = "data:,";
                        QPoint position;
                        QPoint size;
                        QString value = "Get Token fail!";
                        QString pathProfile = SettingsTool::GetPathProfile();
                        QString text7 = "";
                        QVariantList dataTable = *InteractSQL::GetAllHanhDongByKichBan(idKichBan);
                        QString text12 = "";
                        QString text13 = "";
                        QVariantList dataTable2;
                        JSON_Settings jSON_Settings(InteractSQL::GetCauHinhFromKichBan(idKichBan), true);
                        int valueInt = jSON_Settings.GetValueInt("typeSoLuongHanhDong");
                        int valueInt2 = jSON_Settings.GetValueInt("nudHanhDongFrom");
                        int valueInt3 = jSON_Settings.GetValueInt("nudHanhDongTo");
                        int num9 = dataTable.count();
                        int num10 = 0;
                        QDir dir(text7);
                        QString text10;
                        if (settings.GetValueBool("Unlock282"))
                        {
                            flag5 = true;
                            ExcuteUnlock282(indexRow, statusProxy, text4, proxy, typeProxy);
                        }
                        if (!settings.GetValueBool("GetTokenEAAAAU"))
                        {
                            goto IL_0533;
                        }
                        flag5 = true;
                        emit updateStatusAccount(indexRow, "Get Token...");
                        
                        text5 = CommonRequest::GetTokenEAAAAU(text3, cellAccount5, cellAccount4, text4, proxy, typeProxy);
                        if (!(text5 == "Invalid username or password"))
                        {
                            if (text5 != "")
                            {
                                emit updateCellAccount(indexRow, "Token", text5, "token");
                                value = "Get Token Success!";
                            }
                            emit updateStatusAccount(indexRow, value);
                            goto IL_0533;
                        }
                        emit updateStatusAccount(indexRow, "Get token fail (Sai pass)");
                        num2 = 1;
                        goto end_IL_0482;
                    IL_0863:
                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Chờ đến lượt..."));
                        {
                            QMutexLocker locker(&mutex);
                            if (checkDelayChrome > 0){
                                int num6 = QRandomGenerator::global()->bounded(SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayOpenChromeFrom", 1), SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayOpenChromeTo", 1) + 1);
                                if (num6 > 0)
                                {
                                    int tickCount = GetTickCount();
                                    while ((GetTickCount() - tickCount) / 1000 - num6 < 0)
                                    {
                                        QString status = " {time}s...";
                                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Mở tri\u0300nh duyê\u0323t sau") + status.replace("{time}", QString::number(num6 - (GetTickCount() - tickCount) / 1000)));
                                        Common::DelayTime(0.5);
                                        if (!isStop)
                                        {
                                            continue;
                                        }
                                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                                        num2 = 1;
                                        goto end_IL_0482;
                                    }
                                }
                            }else
                            {
                                checkDelayChrome++;
                            }
                        }
                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đang mơ\u0309 tri\u0300nh duyê\u0323t..."));
                        
                        if (SettingsTool::GetSettings("configGeneral").GetValueBool("ckbAddChromeIntoForm"))
                        {
                            if (text6 == "")
                            {
                                position = *new QPoint(-1000, 0);
                                size = *new QPoint(SettingsTool::GetSettings("configGeneral").GetValueInt("nudWidthChrome") + 16, SettingsTool::GetSettings("configGeneral").GetValueInt("nudHeighChrome") + 132);
                            }
                            else
                            {
                                position = *new QPoint(-1000, 0);
                                size = *new QPoint(SettingsTool::GetSettings("configGeneral").GetValueInt("nudWidthChrome") + 33, SettingsTool::GetSettings("configGeneral").GetValueInt("nudHeighChrome") + 39);
                            }
                        }else{
                            Common::initializeScreenDimensions();
                            position = Common::GetPointFromIndexPosition(indexPos, SettingsTool::GetSettings("configGeneral").GetValueInt("cbbColumnChrome", 3), SettingsTool::GetSettings("configGeneral").GetValueInt("cbbRowChrome", 2));
                            size = Common::GetSizeChrome(SettingsTool::GetSettings("configGeneral").GetValueInt("cbbColumnChrome", 3), SettingsTool::GetSettings("configGeneral").GetValueInt("cbbRowChrome", 2));
                        }
                        
                        if (pathProfile != "" && text3 != ""){
                            text7 = pathProfile + "\\" + text3;
                            
                            if (!SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbCreateProfile") && !dir.exists())
                            {
                                text7 = "";
                            }
                            if (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp") == 13)
                            {
                                typeProxy = ((SettingsTool::GetSettings("configGeneral").GetValueInt("typeProxyMin") >= 2) ? 1 : 0);
                            }
                            chrome = new Chrome();
                            chrome->indexChrome = indexRow;
                            chrome->DisableImage = (!settings.GetValueBool("Unlock956") && !SettingsTool::GetSettings("configGeneral").GetValueBool("ckbShowImageInteract"));
                            chrome->UserAgent = cellAccount6;
                            chrome->ProfilePath = text7;
                            chrome->Size = size;
                            chrome->Position = position;
                            chrome->TimeWaitForSearchingElement = 3;
                            chrome->TimeWaitForLoadingPage = 120;
                            chrome->Proxy = proxy;
                            chrome->TypeProxy = typeProxy;
                            chrome->DisableSound = true;
                            chrome->IsUsePortable = SettingsTool::GetSettings("configGeneral").GetValueBool("ckbUsePortable");
                            chrome->PathToPortableZip = SettingsTool::GetSettings("configGeneral").GetValue("txtPathToPortableZip");
                            if (SettingsTool::GetSettings("configGeneral").GetValue("sizeChrome").contains("x"))
                            {
                                chrome->IsUseEmulator = true;
                                QString text8 = SettingsTool::GetSettings("configGeneral").GetValue("sizeChrome").mid(0, SettingsTool::GetSettings("configGeneral").GetValue("sizeChrome").lastIndexOf('x'));
                                int pixelRatio = SettingsTool::GetSettings("configGeneral").GetValue("sizeChrome").split('x')[2].toInt();
                                chrome->Size_Emulator = *new QPoint(text8.split('x')[0].toInt(), text8.split('x')[1].toInt());
                                chrome->UserAgent = cellAccount6;
                                chrome->PixelRatio = pixelRatio;
                            }
                            
                            if (isStop)
                            {
                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                                num2 = 1;
                            }else{
                                QString text9 = SettingsTool::GetSettings("configGeneral").GetValue("txtLinkToOtherBrowser").trimmed();
                                if (text9 != "")
                                {
                                    chrome->LinkToOtherBrowser = text9;
                                }
                                int num7 = 0;
                                while (true){
                                    if (!chrome->Open()){
                                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Lỗi mở trình duyệt!"));
                                        num2 = 1;
                                        break;
                                    }
                                    if(!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP") && proxy.split(':').length() >1){
                                        chrome->GotoURL("https://api.myip.com/");
                                        chrome->DelayTime(1.0);
                                        if(!chrome->GetPageSource().contains("ip")){
                                            chrome->Close();
                                            num7++;
                                            if(num7 >= 3){
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Lỗi kết nối proxy!"));
                                                num2 = 1;
                                                break;
                                            }
                                            continue;
                                        }
                                    }
                                    if (SettingsTool::GetSettings("configGeneral").GetValueBool("ckbAddChromeIntoForm")){
                                        if(text6 != ""){
                                            
                                        }
                                    }
                                    if (settings.GetValueBool("RecoverPass")){
                                        chrome->GotoURL(text10);
                                        bool flag6 = false;
                                        int num8 = 0;
                                        while (true)
                                        {
                                            // if (num8 < 60)
                                            // {
                                            //     if (chrome->CheckExistElement("[name=\"password_new\"]") == 1)
                                            //     {
                                            //         flag6 = true;
                                            //     }
                                            //     else if (chrome->CheckExistElement("[href*=\"/login/identify/?ctx=recover\"]") != 1)
                                            //     {
                                            //         if (CommonChrome.CheckCheckpoint(chrome))
                                            //         {
                                            //             SetStatusAccount(indexRow, "Checkpoint!");
                                            //             SetInfoAccount(indexRow, "Checkpoint");
                                            //             num2 = 1;
                                            //             break;
                                            //         }
                                            //         chrome->DelayTime(1.0);
                                            //         num8++;
                                            //         continue;
                                            //     }
                                            // }
                                            if (flag6)
                                            {
                                                // flag6 = false;
                                                // chrome->DelayTime(2.0);
                                                // QString passwordRecoverPass = GetPasswordRecoverPass();
                                                // chrome->sendKeys(4, "[name=\"password_new\"]", passwordRecoverPass);
                                                // chrome->DelayRandom(2, 3);
                                                // chrome->sendEnter("[name=\"password_new\"]");
                                                // SetCellAccount(cellAccount, "pass", indexRow, "cPassword", passwordRecoverPass);
                                                // for (int i = 0; i < 60; i++)
                                                // {
                                                //     if (chrome->CheckExistElement("[name=\"approvals_code\"]") == 1)
                                                //     {
                                                //         flag6 = true;
                                                //         break;
                                                //     }
                                                //     if (chrome->CheckExistElement("[name=\"submit[Continue]\"]") == 1)
                                                //     {
                                                //         chrome.Click(4, "[name=\"submit[Continue]\"]");

                                                //     }
                                                //     if (chrome.CheckExistElement("[name=\"submit_action\"]") == 1)
                                                //     {
                                                //         chrome.DelayRandom(2, 3);
                                                //         chrome.Click(4, "[name=\"submit_action\"]");
                                                //         if (chrome.CheckExistElement("[value=\"OK\"]", 10.0) == 1)
                                                //         {
                                                //             chrome.DelayRandom(2, 3);
                                                //             chrome.Click(4, "[value=\"OK\"]");
                                                //         }
                                                //         flag6 = true;
                                                //         break;
                                                //     }
                                                //     if (chrome.CheckExistElement("[data-sigil=\"m_login_email\"]") == 1)
                                                //     {
                                                //         break;
                                                //     }
                                                //     if (CommonChrome.CheckCheckpoint(chrome))
                                                //     {
                                                //         SetInfoAccount(indexRow, "Checkpoint");
                                                //         flag6 = true;
                                                //         break;
                                                //     }
                                                //     chrome.DelayTime(1.0);
                                                // }
                                            }
                                            if (flag6)
                                            {
                                                SetInfoAccount(indexRow, "Live");
                                                SetRowColor(indexRow, 2);
                                                SetStatusAccount(indexRow, statusProxy + "Khôi phục mật khẩu thành công!");
                                            }
                                            else
                                            {
                                                SetRowColor(indexRow, 1);
                                                SetStatusAccount(indexRow, statusProxy + "Khôi phục mật khẩu thất bại!");
                                            }
                                            num2 = 1;
                                            break;
                                        }
                                        break;
                                    }
                                    emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đang đăng nhâ\u0323p..."));
                                    bool flag7 = false;
                                    bool isLoginVia = false;
                                    QString text11 = "https://www.facebook.com/";
                                    switch (SettingsTool::GetSettings("configInteractGeneral").GetValueInt("typeBrowserLogin"))
                                    {
                                    case 0:
                                        text11 = "https://mobile.facebook.com/";
                                        break;
                                    case 2:
                                        text11 = "https://mbasic.facebook.com";
                                        break;
                                    case 3:
                                        isLoginVia = true;
                                        break;
                                    }
                                    if(!chrome->GetUrl().startsWith("https://")){
                                        chrome->GotoURL(text11);
                                    }
                                    if (chrome->Proxy != "")
                                    {
                                        chrome->DelayTime(2.0);
                                        if (chrome->GetPageSource() == "<html><head></head><body></body></html>")
                                        {
                                            emit updateStatusAccount(indexRow, statusProxy + "Proxy yêu cầu User/Pass!");
                                            num2 = 1;
                                            break;
                                        }
                                    }
                                    bool flag8 = false;
                                    if (text7.trimmed() != ""){
                                        chrome->AcceptCookie();
                                        num = CommonChrome::CheckLiveCookie(chrome, text11);
                                        switch (num)
                                        {
                                        case 1:
                                            flag7 = true;
                                            goto IL_1322;
                                        case -2:
                                            chrome->Status = StatusChromeAccount::ChromeClosed;
                                            goto end_IL_0d65;
                                        case -3:
                                            chrome->Status = StatusChromeAccount::NoInternet;
                                            goto end_IL_0d65;
                                        case 2:
                                            break;
                                        default:
                                            goto IL_1322;
                                        }
                                        chrome->Status = StatusChromeAccount::Checkpoint;
                                        flag = !CheckIsUidFacebook(text3);
                                        if (flag)
                                        {
                                            text = text3;
                                            text3 = chrome->GetUid();
                                            SetCellAccount(indexRow, "cUid", text3, "uid");
                                        }
                                        if (settings.GetValueBool("Unlock956"))
                                        {
                                            flag8 = true;
                                            goto IL_17a9;
                                        }
                                        if (!CheckDangCheckpointNew(chrome, indexRow, statusProxy))
                                        {
                                            num2 = 1;
                                            break;
                                        }
                                        flag7 = true;
                                    }
                                    goto IL_1322;
                                IL_17a9:
                                    if (settings.GetValueBool("Unlock956")){
                                        if (flag8)
                                        {
                                            chrome->Status = StatusChromeAccount::Empty;
                                            CheckDangCheckpointNew(chrome, indexRow, statusProxy, settings.GetValueBool("Unlock956"), settings.GetValueInt("TypeUnlock956"));
                                        }else if(flag7){
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhâ\u0323p tha\u0300nh công!"));
                                            emit updateRowColor2(indexRow, 2);
                                            emit updateInfoAccount(indexRow, "Live");
                                        }
                                        if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGetCookie") || text4 == "")
                                        {
                                            text4 = chrome->GetCookie();
                                            if (text4 != "")
                                            {
                                                emit updateCellAccount(indexRow, "Cookies", text4, "cookie1");
                                            }
                                        }
                                        num2 = 1;
                                        break;
                                    }
                                    emit updateInfoAccount(indexRow, "Live");
                                    emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhâ\u0323p tha\u0300nh công!"));
                                    emit updateRowColor2(indexRow, 2);
                                    chrome->AcceptCookie();
                                    if (chrome->GetUrl().startsWith("https://m.facebook.com/si/actor_experience/actor_gateway") && chrome->CheckExistElement("[data-nt=\"NT:IMAGE\"]", 15.0) == 1)
                                    {
                                        chrome->ClickJs("[data-nt=\"NT:IMAGE\"]");
                                        chrome->DelayTime(2.0);
                                    }
                                    if (chrome->CheckExistElement("[data-cookiebanner=\"accept_button\"]") == 1)
                                    {
                                        chrome->ClickJs("[data-cookiebanner=\"accept_button\"]");
                                    }
                                    if (chrome->GetFbWeb() == 2)
                                    {
                                        chrome->ClickJs(0, QStringList{"[href^=\"/a/preferences.php?fast_switch_site\"]"});
                                    }
                                    if (chrome->GetUrl().startsWith("https://free.facebook.com/") || chrome->CheckExistElement("[href^=\"/upsell/advanced_upsell/in_line\"]") == 1)
                                    {
                                        chrome->ClickJs(0, QStringList{"[href^=\"/upsell/advanced_upsell/in_line\"]"});
                                        chrome->ClickJs(5, QStringList{"#upsell_upgrade_confirm_button"});
                                    }
                                    flag = !CheckIsUidFacebook(text3);
                                    if (flag)
                                    {
                                        text = text3;
                                        text3 = chrome->GetUid();
                                        Common::UpdateFieldToAccount(cellAccount, "uid", text3);
                                        emit updateCellAccount(indexRow, "Uid", text3);
                                    }
                                    if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGetCookie") || text4 == "")
                                    {
                                        text4 = chrome->GetCookie();
                                        if (text4 != "")
                                        {
                                            emit updateCellAccount(indexRow, "Cookies", text4, "cookie1");
                                        }
                                    }
                                    if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRandomHanhDong"))
                                    {
                                        dataTable = Common::shuffleVariantList(dataTable);
                                        dataTable = Common::shuffleVariantList(dataTable);
                                        dataTable = Common::shuffleVariantList(dataTable);
                                    }
                                    if (valueInt == 1 && valueInt2 <= valueInt3)
                                    {
                                        num9 = QRandomGenerator::global()->bounded(valueInt2, valueInt3 + 1);
                                        if (num9 > dataTable.count())
                                        {
                                            num9 = dataTable.count();
                                        }
                                    }
                                    while(true){
                                        if (num10 < num9){
                                            if (isStop)
                                            {
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                                                num2 = 1;
                                                break;
                                            }
                                        }
                                        try {
                                            text13 = dataTable[num10].toMap()["TenHanhDong"].toString();
                                            text12 = dataTable[num10].toMap()["Id_HanhDong"].toString();
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đang") + " " + text13 + "...");
                                            dataTable2 = *InteractSQL::GetHanhDongById(text12);
                                            JSON_Settings jSON_Settings2(dataTable2[0].toMap()["CauHinh"].toString(), true);
                                            // try {
                                            //     auto tenTuongTac = dataTable2[0].toMap()["TenTuongTac"].toString();
                                            //     if (tenTuongTac == "HDXoaNhatKyHoatDong") {
                                            //         num = HDXoaNhatKyHoatDong(indexRow, statusProxy, chrome, jSON_Settings2);
                                            //     } else if (tenTuongTac == "HDTaoPage") {
                                            //         num = HDTaoPage_Fix(text177, indexRow, statusProxy, chrome, jSON_Settings2, text13, text12);
                                            //     } else if (tenTuongTac == "HDDocThongBao") {
                                            //         num = HDDocThongBao(indexRow, statusProxy, chrome, jSON_Settings2.GetValueInt("nudSoLuongFrom"), jSON_Settings2.GetValueInt("nudSoLuongTo"), jSON_Settings2.GetValueInt("typeDocThongBao"), jSON_Settings2.GetValueInt("nudDelayFrom"), jSON_Settings2.GetValueInt("nudDelayTo"), text13);
                                            //     } else if (tenTuongTac == "HDDocThongBaov2") {
                                            //         num = HDDocThongBaov2(indexRow, statusProxy, chrome, jSON_Settings2.GetValueInt("nudSoLuongFrom"), jSON_Settings2.GetValueInt("nudSoLuongTo"), jSON_Settings2.GetValueInt("nudDelayFrom"), jSON_Settings2.GetValueInt("nudDelayTo"), text13);
                                            //     } else if (tenTuongTac == "HDXemStory") {
                                            //         num = HDXemStory(indexRow, statusProxy, chrome, jSON_Settings2.GetValueInt("nudSoLuongFrom"), jSON_Settings2.GetValueInt("nudSoLuongTo"), jSON_Settings2.GetValueInt("nudDelayFrom"), jSON_Settings2.GetValueInt("nudDelayTo"), jSON_Settings2.GetValueBool("ckbInteract"), jSON_Settings2.GetValue("typeReaction"), jSON_Settings2.GetValueBool("ckbComment"), jSON_Settings2.GetValueList("txtComment"), text13);
                                            //     } else if (tenTuongTac == "HDXemStoryv2") {
                                            //         num = HDXemStoryv2(indexRow, statusProxy, chrome, jSON_Settings2.GetValueInt("nudSoLuongFrom"), jSON_Settings2.GetValueInt("nudSoLuongTo"), jSON_Settings2.GetValueInt("nudDelayFrom"), jSON_Settings2.GetValueInt("nudDelayTo"), jSON_Settings2.GetValueBool("ckbInteract").toBool(), jSON_Settings2.GetValue("typeReaction"), jSON_Settings2.GetValueBool("ckbComment"), jSON_Settings2.GetValueList("txtComment"), text13);
                                            //     } else if (tenTuongTac == "HDXemStoryChiDinh") {
                                            //         num = HDXemStoryChiDinh(indexRow, statusProxy, chrome, jSON_Settings2, text13);
                                            //     } else if (tenTuongTac == "HDDangStory") {
                                            //         num = HDDangStory(indexRow, statusProxy, chrome, jSON_Settings2, text13);
                                            //     } else if (tenTuongTac == "HDXemWatch") {
                                            //         num = HDXemWatch(indexRow, statusProxy, chrome, jSON_Settings2.GetValueInt("nudSoLuongFrom"), jSON_Settings2.GetValueInt("nudSoLuongTo"), jSON_Settings2.GetValueInt("nudTimeWatchFrom"), jSON_Settings2.GetValueInt("nudTimeWatchTo"), jSON_Settings2.GetValueBool("ckbInteract"), jSON_Settings2.GetValueInt("nudCountLikeFrom"), jSON_Settings2.GetValueInt("nudCountLikeTo"), jSON_Settings2.GetValueBool("ckbShareWall"), jSON_Settings2.GetValueInt("nudCountShareFrom"), jSON_Settings2.GetValueInt("nudCountShareTo"), jSON_Settings2.GetValueBool("ckbComment"), jSON_Settings2.GetValueList("txtComment"), jSON_Settings2.GetValueInt("nudCountCommentFrom"), jSON_Settings2.GetValueInt("nudCountCommentTo"), jSON_Settings2.GetValueBool("ckbFollow"), jSON_Settings2.GetValueInt("nudFollowFrom"), jSON_Settings2.GetValueInt("nudFollowTo"), text13);
                                            // } catch (...) {
                                            // }
                                        } catch (...) {
                                        }
                                    }
                                    break;
                                IL_1322:
                                    if (!flag7) {
                                        int num11 = SettingsTool::GetSettings("configInteractGeneral").GetValueInt("typeLogin");
                                        QString text14;
                                        while (true) {
                                            switch (num11) {
                                            case 0:
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhập bằng uid|pass..."));
                                                break;
                                            case 1:
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhập bằng email|pass..."));
                                                break;
                                            case 2:
                                            case 3:
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhập bằng cookie..."));
                                                break;
                                            }

                                            text14 = LoginFacebook(chrome, num11, "https://mobile.facebook.com/", text3, cellAccount2, cellAccount5, cellAccount4, text4,
                                                                   SettingsTool::GetSettings("configGeneral").GetValueInt("tocDoGoVanBan"),
                                                                   SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbDontSaveBrowser"),
                                                                   SettingsTool::GetSettings("configGeneral").GetValueInt("type2Fa"),
                                                                   isLoginVia);

                                            if (num11 != 3 || QStringList({"1", "2", "8"}).contains(text14)) {
                                                break;
                                            }
                                            num11 = 0;
                                        }

                                        if (text14 == "-3") {
                                            chrome->Status = StatusChromeAccount::NoInternet;
                                            goto end_IL_0d65;
                                        } else if (text14 == "-2") {
                                            chrome->Status = StatusChromeAccount::ChromeClosed;
                                            goto IL_178b;
                                        } else if (text14 == "0") {
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đăng nhập thất bại!"));
                                            goto IL_178b;
                                        } else if (text14 == "1") {
                                            flag7 = true;
                                            goto IL_178b;
                                        } else if (text14 == "2") {
                                            chrome->Status = StatusChromeAccount::Checkpoint;
                                            flag = !CheckIsUidFacebook(text3);
                                            if (flag) {
                                                text = text3;
                                                text3 = chrome->GetUid();
                                                Common::UpdateFieldToAccount(cellAccount, "uid", text3);
                                                emit updateCellAccount(indexRow, "Uid", text3);
                                            }
                                            if (settings.GetValueBool("Unlock956")) {
                                                flag8 = true;
                                            } else {
                                                flag7 = CheckDangCheckpointNew(chrome, indexRow, statusProxy);
                                            }
                                            goto IL_178b;
                                        } else if (text14 == "3") {
                                            if (num11 != 2) {
                                                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Không có 2fa!"));
                                            } else {
                                                flag7 = true;
                                            }
                                            goto IL_178b;
                                        } else if (text14 == "4") {
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Tài khoản không đúng!"));
                                            goto IL_178b;
                                        } else if (text14 == "5") {
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Mật khẩu không đúng!"));
                                            emit updateInfoAccount(indexRow, "Changed pass");
                                            goto IL_178b;
                                        } else if (text14 == "6") {
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Mã 2fa không đúng!"));
                                            goto IL_178b;
                                        } else if (text14 == "8") {
                                            emit updateInfoAccount(indexRow, "Live");
                                            emit updateRowColor2(indexRow, 2);
                                            if (SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbGetCookie") || text4.isEmpty()) {
                                                text4 = chrome->GetCookie();
                                                if (!text4.isEmpty()) {
                                                    emit updateCellAccount(indexRow, "Cookies", text4, "cookie1");
                                                }
                                            }
                                            emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Account Novery!"));
                                            goto IL_178b;
                                        } else {
                                            emit updateStatusAccount(indexRow, statusProxy + text14);
                                            goto IL_178b;
                                        }

                                    IL_178b:
                                        if (flag7) {
                                            break;
                                        }
                                        emit updateRowColor2(indexRow, 1);
                                        ScreenCaptureError(chrome, text3, 1);
                                        num2 = 1;
                                        goto end_IL_0d65;
                                    }

                                    goto IL_17a9;
                                    continue;

                                end_IL_0d65:
                                    break;

                                }

                            }
                            goto end_IL_0482;
                        IL_0533:
                            if (settings.GetValueBool("Bat2FA"))
                            {
                                flag5 = true;
                                emit updateStatusAccount(indexRow, "Bật 2FA...");
                                QString value2 = "Bật 2fa fail!";
                                if (text5.trimmed() != "")
                                {
                                    QString text15 = TurnOn2FA(cellAccount5, text5, proxy, typeProxy);
                                    if (text15 != "")
                                    {
                                        emit updateCellAccount(indexRow, "cFa2", text15, "fa2");
                                        value2 = "Bật 2fa Success!";
                                    }
                                }
                                emit updateStatusAccount(indexRow, value2);
                            }
                            if (settings.GetValueBool("UpAvatar"))
                            {
                                flag5 = true;
                                emit updateStatusAccount(indexRow, "Up Avatar...");
                                QString value3 = "Up Avatar fail!";
                                if (text5.trimmed() != "")
                                {
                                    std::unique_ptr<RequestHandle> requestXNet = std::make_unique<RequestHandle>("", "", proxy, typeProxy);
                                    QString text16 = "";
                                    try {
                                        text16 = requestXNet->RequestPost("https://graph.facebook.com/me/photos?access_token=" + text5,
                                                                          "url=" + RequestHandle("", "", "", 0).RequestGet("https://download.minsoftware.vn/photos/"));
                                        if (!text16.isEmpty()) {
                                            QString text17 = Utils::parseJsonString(text16)["id"].toString();
                                            text16 = requestXNet->RequestPost("https://graph.facebook.com/me/picture?access_token=" + text5,
                                                                              "focus_y=0.49902534&focus_x=0.5&photo=" + text17 + "&no_feed_story=false&locale=en_US&client_country_code=VN&fb_api_req_friendly_name=set_cover_photo&fb_api_caller_class=SetCoverPhotoHandlerImpl");
                                            if (!text16.isEmpty()) {
                                                value3 = "Up Avatar Success!";
                                            }
                                        }
                                    } catch (const QException& e) {
                                        // Handle the exception properly
                                        qDebug() << "Exception caught: " << e.what();
                                    }
                                }
                                emit updateStatusAccount(indexRow, value3);
                            }
                            if (flag5)
                            {
                                num2 = 1;
                            }
                            else
                            {
                                text10 = "";
                                if (!settings.GetValueBool("RecoverPass"))
                                {
                                    goto IL_0863;
                                }
                                emit updateStatusAccount(indexRow, statusProxy + "Gư\u0309i yêu câ\u0300u khôi phục mật khẩu...");
                                num = QuenMatKhau(cellAccount2, proxy, typeProxy);
                                switch (num)
                                {
                                case 0:
                                    emit updateStatusAccount(indexRow, statusProxy + "Mail chưa đăng ky\u0301 Fb!");
                                    break;
                                case 1:
                                    emit updateStatusAccount(indexRow, statusProxy + "Gư\u0309i yêu câ\u0300u tha\u0300nh công!");
                                    break;
                                case 2:
                                    emit updateStatusAccount(indexRow, statusProxy + "Lô\u0303i gửi yêu cầu!");
                                    break;
                                case 3:
                                    emit updateStatusAccount(indexRow, statusProxy + "Gư\u0309i yêu câ\u0300u thâ\u0301t ba\u0323i!");
                                    break;
                                case 4:
                                    emit updateStatusAccount(indexRow, statusProxy + "Chặn tính năng!");
                                    break;
                                }
                                if (num != 1)
                                {
                                    num2 = 1;
                                }
                                else
                                {
                                    for (int j = 0; j < 2; j++)
                                    {
                                        emit updateStatusAccount(indexRow, statusProxy + "Get otp...");
                                        // text10 = GetOtpFromEmail(2, cellAccount2, cellAccount3, 60, text3);
                                        if (text10.startsWith("https://m.facebook.com") || j == 1)
                                        {
                                            break;
                                        }
                                        emit updateStatusAccount(indexRow, statusProxy + "Gư\u0309i yêu câ\u0300u khôi phục mật khẩu (2)...");
                                        QuenMatKhau(cellAccount2, proxy, typeProxy);
                                    }
                                    if (!(text10 == "") && text10.startsWith("https://m.facebook.com"))
                                    {
                                        emit updateStatusAccount(indexRow, statusProxy + "Get otp thành công!");
                                        goto IL_0863;
                                    }
                                    emit updateStatusAccount(indexRow, statusProxy + "Không lấy được otp!");
                                    num2 = 1;
                                }
                            }
                        end_IL_0482:;
                        }
                    } catch (QException ex5) {
                        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Lô\u0303i không xa\u0301c đi\u0323nh!"));
                        num2 = 1;
                    }
                }
            }
        }
        goto IL_5233;
    IL_0396:
        emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
        num2 = 1;
        goto IL_5233;
    IL_5233:
        QString text18 = "";
        if(num2 == 1){
            if(chrome != nullptr){
                if(chrome->Status == StatusChromeAccount::Checkpoint){
                    ScreenCaptureError(chrome,text3, 0);
                }
                StatusChromeAccount status = chrome->Status;
                if (status == StatusChromeAccount::ChromeClosed || status == StatusChromeAccount::Checkpoint || status == StatusChromeAccount::NoInternet)
                {
                    SetRowColor(indexRow, 1);
                    text18 = GetContentStatusChrome::GetContent(chrome->Status);
                }
                else
                {
                    text18 = GetStatusAccount(indexRow);
                }
            }else{
                text18 = GetStatusAccount(indexRow);
            }
        }else if (CheckIsUidFacebook(text3) && CommonRequest::CheckLiveWall(text3).startsWith("0|"))
        {
            SetInfoAccount(indexRow, "Die");
            text18 = Language::GetValue("Tài khoản Die!");
        }else{
            chrome->Status = StatusChromeAccount::Empty;
            CommonChrome::CheckStatusAccount(chrome, true);
            StatusChromeAccount status = chrome->Status;
            if (status == StatusChromeAccount::ChromeClosed || status == StatusChromeAccount::Checkpoint || status == StatusChromeAccount::NoInternet)
            {
                SetRowColor(indexRow, 1);
                text18 = GetContentStatusChrome::GetContent(chrome->Status);
            }
        }
        try
        {
            if (chrome != nullptr)
            {
                if (!chrome->CheckChromeClose() && SettingsTool::GetSettings("configGeneral").GetValueBool("ckbDelayCloseChrome"))
                {
                    int timeWait = QRandomGenerator::global()->bounded(SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCloseChromeFrom"), SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCloseChromeTo") + 1);
                    SetStatusAccount(indexRow, statusProxy + "Đóng tri\u0300nh duyê\u0323t sau {time}s...", timeWait);
                }
                CloseChrome(indexRow, statusProxy, chrome);
            }
        }
        catch(...)
        {
        }
        QString text19 = "";
        if (check_HDNhanTinBanBe != "")
        {
            text19 = text19 + "- " + check_HDNhanTinBanBe;
        }
        if (check_HDKetBanTepUid != "")
        {
            text19 = text19 + "- " + check_HDKetBanTepUid;
        }
        if (check_HDKetBanGoiY != "")
        {
            text19 = text19 + "- " + Language::GetValue("Gợi ý Kb: ") + check_HDKetBanGoiY;
        }
        if (check_HDXoaSdt != "")
        {
            text19 = text19 + "- " + Language::GetValue("Xóa Sđt: ") + check_HDXoaSdt;
        }
        if (check_HDAddMail != "")
        {
            text19 = text19 + "- Add mail: " + check_HDAddMail;
        }
        if (check_HDXoaMail != "")
        {
            text19 = text19 + "- Xóa mail: " + check_HDXoaMail;
        }
        if (check_HDDoiMatKhau != "")
        {
            text19 = text19 + "- Đổi pass: " + check_HDDoiMatKhau;
        }
        if (check_HDDoiTen != "")
        {
            text19 = text19 + "- Đổi tên: " + check_HDDoiTen;
        }
        if (check_HDUpAvatar != "")
        {
            text19 = text19 + "- Up avatar: " + check_HDUpAvatar;
        }
        if (check_HDUpCover != "")
        {
            text19 = text19 + "- Up cover: " + check_HDUpCover;
        }
        if (check_HDOnOff2FA != "")
        {
            text19 = text19 + "- 2FA: " + check_HDOnOff2FA;
        }
        if (text18 == "")
        {
            QString text20 = "";
            switch (num4)
            {
            case 1:
                text20 += " -Like page success!";
                break;
            case 2:
                text20 += " -Like page fail!";
                break;
            }
            switch (num3)
            {
            case 1:
                text20 += " -Follow success!";
                break;
            case 2:
                text20 += " -Follow fail!";
                break;
            }
            SetStatusAccount(indexRow, statusProxy + Language::GetValue("Đã tương tác xong!") + (flag2 ? "- Facebook blocked!" : "") + (flag3 ? "- Facebook spam!" : "") + text20 + ((text2 != "") ? ("- " + text2) : "") + text19 + " [" /*+ account.GetTimeRun()*/ + "(s)]");
            SetCellAccount(indexRow, "cInteractEnd", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"), "interactEnd");
            if (GetInfoAccount(indexRow) != "Changed pass")
            {
                SetInfoAccount(indexRow, "Live");
            }
        }
        else
        {
            SetStatusAccount(indexRow, statusProxy + text18 + (flag2 ? "- Facebook blocked!" : ""));
        }
        if (flag && QFileInfo::exists(SettingsTool::GetSettings("configGeneral").GetValue("txbPathProfile") + "\\" + text) && QFileInfo(SettingsTool::GetSettings("configGeneral").GetValue("txbPathProfile") + "\\" + text).isDir() && text != "")
        {
            QString text21 = SettingsTool::GetSettings("configGeneral").GetValue("txbPathProfile") + "\\" + text;
            QString pathTo = SettingsTool::GetSettings("configGeneral").GetValue("txbPathProfile") + "\\" + text3;
            if (!Common::moveFolder(text21, pathTo) && Common::copyFolder(text21, pathTo))
            {
                Common::deleteFolder(text21);
            }
        }
        FinishProxy(tinsoft, xproxy, tmproxy, proxyWeb, shopLike, minProxy, obcProxy);
    } catch (QException ex6) {
        QString exceptionString = QString::fromLatin1(ex6.what());
        if (QString::fromLatin1(ex6.what()).contains("Thread was being aborted."))
        {
            try
            {
                CloseChrome(indexRow, statusProxy, chrome);
                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã tương tác xong!") + (flag2 ? "- Facebook blocked!" : "") + " [" + account->getTimeRun() + "(s)]");
                emit updateCellAccount(indexRow, "cInteractEnd", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));
                Common::UpdateFieldToAccount(cellAccount, "interactEnd", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));
                FinishProxy(tinsoft, xproxy, tmproxy, proxyWeb, shopLike, minProxy, obcProxy);
                return;
            }
            catch (QException ex)
            {
                return;
            }
        }
    }
}

int MainWindow::HDXoaNhatKyHoatDong(int indexRow, const QString& statusProxy, Chrome& chrome, JSON_Settings& cauHinh) {
    int num = cauHinh.GetValueInt("nudSoLuong");
    try {
        QString format = "https://m.facebook.com/%1/allactivity/?category_key=all&timestart=%2&timeend=%3";
        QString arg = chrome.ExecuteScript("return (document.cookie + ';').match(new RegExp('c_user=(.*?);'))[1]");
        QString text, text2, text3;
        int i = 0;
        if (cauHinh.GetValueBool("ckbXoaThangNay")) {
            i = -1;
            num--;
        }
        for (; i < num; i++) {
            QList<QString> list;
            QDateTime dateTime = QDateTime::currentDateTime().addMonths(-1 - i);
            QDateTime dateTime2 = QDateTime::currentDateTime().addMonths(-i);

            // Corrected QDateTime construction
            QDateTime startOfMonth = QDateTime(QDate(dateTime.date().year(), dateTime.date().month(), 1), QTime(0, 0));
            QDateTime startOfNextMonth = QDateTime(QDate(dateTime2.date().year(), dateTime2.date().month(), 1), QTime(0, 0));

            text = QString::number(Common::ConvertDatetimeToTimestamp(startOfMonth));
            text2 = QString::number(Common::ConvertDatetimeToTimestamp(startOfNextMonth));
            text3 = format.arg(arg).arg(text).arg(text2);
            chrome.GotoURL(text3);
            chrome.DelayTime(1.0);
            if (chrome.CheckExistElement("[href*=\"allactivity/?category_key=trash\"]", 30.0) != 1) {
                continue;
            }
            SetStatusAccount(indexRow, statusProxy + tr("Đang lấy link xóa tháng %1...").arg(dateTime.date().month()));
            if (chrome.CheckExistElement(QString("[id*=\"month_%1_%2_more\"]").arg(dateTime.date().year()).arg(dateTime.date().month()), 5.0) != 1) {
                continue;
            }
            for (int j = 0; j < 5; j++) {
                if (chrome.CheckExistElement(QString("[id*=\"month_%1_%2_more\"]").arg(dateTime.date().year()).arg(dateTime.date().month()), 5.0) != 1) {
                    break;
                }
                chrome.ScrollSmoothv2(QString("document.querySelector('[id*=\"month_%1_%2_more\"]')").arg(dateTime.date().year()).arg(dateTime.date().month()));
                chrome.click(4, QString("[id*=\"month_%1_%2_more\"]").arg(dateTime.date().year()).arg(dateTime.date().month()));
                chrome.DelayTime(1.0);
            }
            int num2 = chrome.ExecuteScript("return document.querySelectorAll('[href*=\"activity_log/confirm_dialog\"]').length").toInt();
            for (int k = 0; k < num2; k++) {
                list.append(chrome.ExecuteScript(QString("return document.querySelectorAll('[href*=\"activity_log/confirm_dialog\"]')[%1].href").arg(k)));
            }
            for (int l = 0; l < list.count(); l++) {
                if (isStop) {
                    return 0;
                }
                SetStatusAccount(indexRow, statusProxy + tr("Đang xóa (%1/%2) - Tháng %3...").arg(l + 1).arg(list.count()).arg(dateTime.date().month()));
                chrome.GotoURL(list[l]);
                chrome.DelayTime(1.0);
                if (chrome.CheckExistElement("[rel=\"async-post\"]", 10.0) != 1) {
                    continue;
                }
                chrome.click(4, "[rel=\"async-post\"]");
                chrome.DelayTime(1.0);
                for (int m = 0; m < 20; m++) {
                    if (chrome.GetUrl() != list[l]) {
                        break;
                    }
                    chrome.DelayTime(1.0);
                }
                chrome.DelayTime(QRandomGenerator::global()->bounded(cauHinh.GetValueInt("nudDelayFrom"), cauHinh.GetValueInt("nudDelayTo") + 1));
            }
        }
    } catch (...) {
        // Handle exceptions
    }
    return 0;
}

int MainWindow::HDTaoPage_Fix(QString& F62A033F, int B5193F02, const QString& string_1, Chrome& b901B28A_0, JSON_Settings& cauHinh, const QString& string_2, const QString& text12) {
    int num = cauHinh.GetValueInt("nudSoLuongFrom");
    int num2 = cauHinh.GetValueInt("nudSoLuongTo");
    int num3 = cauHinh.GetValueInt("nudDelayFrom");
    int num4 = cauHinh.GetValueInt("nudDelayTo");
    QStringList list = cauHinh.GetValueList("txtPageName");
    QStringList list2 = cauHinh.GetValueList("txtCatagory");
    QString text = cauHinh.GetValue("txtToCookie", "");
    QStringList list3 = list;
    QStringList list4 = list2;
    int num5 = QRandomGenerator::global()->bounded(num, num2 + 1);
    QString text2;
    QRegularExpression regex("c_user=(\\d+)");
    QRegularExpressionMatch match = regex.match(text);
    if (match.hasMatch()) {
        text2 = match.captured(1);
    }
    if (text2.isEmpty() && Common::smethod_28(text)) {
        text2 = text;
    }
    int num6 = 0;
    int num7 = 0;
    int num8 = 2;
    for (int i = 0; i < num5 + 10; i++) {
        SetStatusAccount(B5193F02, string_1 + Language::GetValue("Đang") + QString(" %1 (%2/%3)...").arg(string_2).arg(num6 + 1).arg(num5), -1);
        QString text3;
        if (list3.isEmpty()) {
            list3 = list;
        }
        if (!list3.isEmpty()) {
            text3 = list3.takeLast();
        }
        QString text4;
        if (list4.isEmpty()) {
            list4 = list2;
        }
        if (!list4.isEmpty()) {
            text4 = list4.takeFirst();
        }
        QString text5 = b901B28A_0.method_72(text3, text4);
        if (text5.isEmpty()) {
            num7++;
            if (num7 >= num8) {
                break;
            }
        } else {
            num6++;
            if (!text2.isEmpty()) {
                // Do something with text2 if needed
            }
            if (num6 >= num5) {
                break;
            }
            SetStatusAccount(B5193F02,
                             string_1 + Language::GetValue("Đang") +
                                 QString(" %1 (%2/%3), %4 {{time}}s...")
                                     .arg(string_2)
                                     .arg(num6)
                                     .arg(num5)
                                     .arg(Language::GetValue("đợi")),
                             num3, num4);
        }
    }
    F62A033F = QString::number(num6);
    return 0;
}


void MainWindow::SetStatusAccount(int indexRow, QString value, int timeWaitFrom, int timeWaitTo)
{
    int timeWait = QRandomGenerator::global()->bounded(timeWaitFrom, timeWaitTo + 1);
    emit updateStatusAccount(indexRow, value, timeWait);
}

void MainWindow::FinishProxy(TinsoftProxy* tinsoft, XproxyProxy* xproxy, TMProxy* tmproxy,
                 ProxyV6Net* proxyWeb, ShopLike* shopLike, MinProxy* minProxy,
                 ObcProxy* obcProxy)
{
    QMutexLocker locker(&mutex);

    QSettings settings("configGeneral");
    int ipChangeType = settings.value("ip_iTypeChangeIp").toInt();

    switch (ipChangeType) {
    case 7:
    case 15:
        if (tinsoft) tinsoft->decrementDangSuDung();
        break;
    case 8:
        if (xproxy) xproxy->decrementDangSuDung();
        break;
    case 10:
        if (tmproxy) tmproxy->DecrementDangSuDung();
        break;
    case 11:
        if (proxyWeb) proxyWeb->DecrementDangSuDung();
        break;
    case 12:
        if (shopLike) shopLike->DecrementDangSuDung();
        break;
    case 13:
        if (minProxy) minProxy->DecrementDangSuDung();
        break;
    case 14:
        if (obcProxy) obcProxy->DecrementDangSuDung();
        break;
    case 9:
        break;
    }
}


void MainWindow::CloseChrome(int indexRow, QString statusProxy, Chrome* chrome){
    try
    {
        SetStatusAccount(indexRow, statusProxy + "Close chrome...");
        chrome->Close();
        // if (SettingsTool::GetSettings("configGeneral").GetValueBool("ckbAddChromeIntoForm"))
        // {
        //     fViewChrome.remote.RemovePanelDevice(chrome.IndexChrome);
        // }
    }
    catch(...)
    {
    }
}



QString MainWindow::LoginFacebook(Chrome* chrome, int typeLogin, const QString &typeWeb, const QString &uid, const QString &email, QString &pass, QString &fa2, const QString &cookie, int tocDoGoVanBan, bool isDontSaveBrowser, int type2Fa, bool isLoginVia)
{
    QString result;
    switch (typeLogin) {
    case 0:
        if (uid.trimmed().isEmpty() || pass.trimmed().isEmpty()) {
            if (uid.trimmed().isEmpty()) {
                result = Language::GetValue("Không tìm thấy UID!");
            } else if (pass.trimmed().isEmpty()) {
                result = Language::GetValue("Không tìm thấy Pass!");
            }
        } else {
            result = CommonChrome::LoginFacebookUsingUidPassNew(chrome, uid, pass, fa2, typeWeb, tocDoGoVanBan, isDontSaveBrowser, type2Fa, 120, isLoginVia);
        }
        break;
    case 1:
        if (email.trimmed().isEmpty() || pass.trimmed().isEmpty()) {
            if (email.trimmed().isEmpty()) {
                result = Language::GetValue("Không tìm thấy Email!");
            } else if (pass.trimmed().isEmpty()) {
                result = Language::GetValue("Không tìm thấy Pass!");
            }
        } else {
            result = CommonChrome::LoginFacebookUsingUidPassNew(chrome, email, pass, fa2, typeWeb, tocDoGoVanBan, isDontSaveBrowser, type2Fa, 120, isLoginVia);
        }
        break;
    case 2:
    case 3:
        result = (!cookie.trimmed().isEmpty()) ? CommonChrome::LoginFacebookUsingCookie(chrome, cookie, typeWeb) : Language::GetValue("Không tìm thấy Cookie!");
        break;
    }
    return result;
}


int MainWindow::QuenMatKhau(QString mail, QString proxy, int typeProxy){
    try {
        std::unique_ptr<RequestHandle> request = std::make_unique<RequestHandle>("", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);

        QString input = request->RequestGet("https://mobile.facebook.com/login/identify/?ctx=recover&c=https%3A%2F%2Fm.facebook.com%2F&multiple_results=0&ars=facebook_login&lwv=100&_rdr");
        QString value = QRegularExpression("name=\"lsd\" value=\"(.*?)\"").match(input).captured(1);
        QString value2 = QRegularExpression("name=\"jazoest\" value=\"(.*?)\"").match(input).captured(1);
        QString data = "lsd=" + value + "&jazoest=" + value2 + "&email=" + QUrl::toPercentEncoding(mail) + "&did_submit=T%C3%ACm+ki%E1%BA%BFm";
        QString text = request->RequestPost("https://mobile.facebook.com/login/identify/?ctx=recover&c=%2Flogin%2F&search_attempts=1&ars=facebook_login&alternate_search=0&show_friend_search_filtered_list=0&birth_month_search=0&city_search=0", data);

        if (text.contains("login_identify_search_error_msg"))
        {
            return 0;
        }
        if (text.contains("571927962827151"))
        {
            return 4;
        }

        text = request->RequestGet("https://mobile.facebook.com/recover/initiate/?c=%2Flogin%2F&fl=initiate_view&ctx=msite_initiate_view");
        value = QRegularExpression("name=\"lsd\" value=\"(.*?)\"").match(input).captured(1);
        value2 = QRegularExpression("name=\"jazoest\" value=\"(.*?)\"").match(input).captured(1);
        text = request->RequestPost("https://mobile.facebook.com/ajax/recover/initiate/?c=%2Flogin%2F&sr=0", "lsd=" + value + "&jazoest=" + value2 + "&recover_method=send_email&reset_action=Ti%E1%BA%BFp+t%E1%BB%A5c");

        if (text.contains("name=\"n\"") && text.contains(QUrl::toPercentEncoding(mail)))
        {
            return 1;
        }
        return 3;
    } catch (QException) {
        return 2;
    }
}



QString MainWindow::TurnOn2FA(QString password, QString token, QString proxy, int typeProxy){
    QString text = "";
    try{
        QString userAgent = "[FBAN/FB4A;FBAV/322.0.0.35.121;FBBV/297186297;FBDM/{density=2.75,width=1080,height=2130};FBLC/en_US;FBRV/298570471;FBCR/Viettel;FBMF/Xiaomi;FBBD/xiaomi;FBPN/com.facebook.katana;FBDV/Redmi Note 8;FBSV/10;FBOP/1;FBCA/arm64-v8a:;]";
        RequestHandle request("", userAgent, proxy, typeProxy);
        request.addHeader("Authorization", "OAuth " + token.toUtf8());
        QString data = "method=POST&challenge_type=PASSWORD&challenge_params={\"password\":\"" + password + "\"}&locale=en_US&client_country_code=VN&fb_api_req_friendly_name=validate_challenge&fb_api_caller_class=SecuredActionServiceHandler";
        request.RequestPost("https://graph.facebook.com/secured_action/validate_challenge", data);
        request.addHeader("X-FB-Net-HNI", " 45204");
        request.addHeader("X-FB-SIM-HNI", " 45201");
        request.addHeader("Authorization", " OAuth " + token.toUtf8());
        request.addHeader("X-FB-Connection-Type", " WIFI");
        request.addHeader("X-Tigon-Is-Retry", " False");
        request.addHeader("x-fb-rmd", " state=NO_MATCH");
        request.addHeader("x-fb-session-id", " nid=OMyw5/7ZxImN;pid=Main;tid=947;nc=0;fc=0;bc=0;cid=f36ca4f6f658dd2e6a1f0ff6e43e6051");
        request.addHeader("x-fb-device-group", " 5120");
        request.addHeader("X-FB-Friendly-Name", " PageCreationNewPage");
        request.addHeader("X-FB-Request-Analytics-Tags", " graphservice");
        request.addHeader("X-FB-HTTP-Engine", " Liger");
        request.addHeader("X-FB-Client-IP", " True");
        request.addHeader("X-FB-Server-Cluster", " True");
        request.addHeader("x-fb-connection-token", " f36ca4f6f658dd2e6a1f0ff6e43e6051");
        data = "doc_id=4330798123599254&method=post&locale=en_US&pretty=false&format=json&purpose=fetch&variables={\"params\":{\"nt_context\":{\"using_white_navbar\":true,\"pixel_ratio\":3,\"styles_id\":\"b6ae3d50d6f559cf2e62adb67b77fd9e\",\"bloks_version\":\"3b5a444c99b7214e5eefefb79bcaf6e89b80ae7db8ced15a5588301589a164c1\"},\"path\":\"security/2fac/nt/setup/qr_code\",\"params\":\"{\\\"start_screen_id\\\":\\\"[\\\\\\\"__ntid:uu97dx:0__\\\\\\\",null]\\\"}\",\"extra_client_data\":{}},\"scale\":\"3\",\"nt_context\":{\"using_white_navbar\":true,\"pixel_ratio\":3,\"styles_id\":\"b6ae3d50d6f559cf2e62adb67b77fd9e\",\"bloks_version\":\"3b5a444c99b7214e5eefefb79bcaf6e89b80ae7db8ced15a5588301589a164c1\"}}&fb_api_req_friendly_name=NativeTemplateScreenQuery&fb_api_caller_class=graphservice&fb_api_analytics_tags=[\"GraphServices\"]&server_timestamps=true";
        QString text = QRegularExpression("secret=(.*?)&").match(request.RequestPost("https://graph.facebook.com/graphql/", data)).captured(1);
        if(text != ""){
            QString topt = Common::GetTotp(text);
            request.addHeader("X-FB-Net-HNI", " 45204");
            request.addHeader("X-FB-SIM-HNI", " 45201");
            request.addHeader("Authorization", "OAuth " + token.toUtf8());
            request.addHeader("X-FB-Connection-Type", " WIFI");
            request.addHeader("X-Tigon-Is-Retry", " False");
            request.addHeader("x-fb-rmd", " state=NO_MATCH");
            request.addHeader("x-fb-session-id", " nid=OMyw5/7ZxImN;pid=Main;tid=947;nc=0;fc=0;bc=0;cid=f36ca4f6f658dd2e6a1f0ff6e43e6051");
            request.addHeader("x-fb-device-group", " 5120");
            data = "doc_id=6091464777534071&method=post&locale=en_US&pretty=false&format=json&variables=%7B%22scale%22%3A%223%22%2C%22params%22%3A%7B%22nt_context%22%3A%7B%22using_white_navbar%22%3Atrue%2C%22pixel_ratio%22%3A3%2C%22styles_id%22%3A%22b6ae3d50d6f559cf2e62adb67b77fd9e%22%2C%22bloks_version%22%3A%223b5a444c99b7214e5eefefb79bcaf6e89b80ae7db8ced15a5588301589a164c1%22%7D%2C%22payload%22%3A%22security%2F2fac%2Fnt%2Fsetup%2Fcode_entry%2Fsubmit%3Fcontent_id%3D%255B%2522__ntid%253Av10gun%253A1__%2522%252Cnull%255D%26error_element_id%3D%255B%2522__ntid%253Av10gun%253A6__%2522%252Cnull%255D%26submit_button_id%3D%255B%2522__ntid%253Av10gun%253A4__%2522%252Cnull%255D%26progress_id%3D%255B%2522__ntid%253Av10gun%253A5__%2522%252Cnull%255D%26form_id%3D%255B%2522__ntid%253Av10gun%253A2__%2522%252Cnull%255D%26start_screen_id%3D%255B%2522__ntid%253Auu97dx%253A0__%2522%252Cnull%255D%22%2C%22client_data%22%3A%7B%22sensitive_string_value%22%3A%22%5B%5B%5C%22code%5B%5D%5C%22%2C%5C%22" + topt + "%5C%22%5D%2C%5B%5C%22code_handler_type%5C%22%2C%5C%22third_party_qr_auth%5C%22%5D%5D%22%7D%7D%2C%22nt_context%22%3A%7B%22using_white_navbar%22%3Atrue%2C%22pixel_ratio%22%3A3%2C%22styles_id%22%3A%22b6ae3d50d6f559cf2e62adb67b77fd9e%22%2C%22bloks_version%22%3A%223b5a444c99b7214e5eefefb79bcaf6e89b80ae7db8ced15a5588301589a164c1%22%7D%2C%22profile_image_size%22%3A258%2C%22include_image_ranges%22%3Atrue%7D&fb_api_req_friendly_name=NativeTemplateAsyncQuery&fb_api_caller_class=graphservice&fb_api_analytics_tags=%5B%22GraphServices%22%5D&server_timestamps=true";
            if (request.RequestPost("https://graph.facebook.com/graphql/", data).contains("error"))
            {
                text = "";
                return text;
            }
            return text;
            
        }
        return text;
    }catch (std::exception ex) {
        qDebug() << ex.what();
        return text;
    }
}

void MainWindow::ExcuteUnlock282(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy){
    new RequestHandle(cookie, "Mozilla/5.0 (windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);
}

void MainWindow::GetProxy(int indexRow, bool &isStop, QString &proxy, int &typeProxy, QString &statusProxy, QString &ip, TinsoftProxy* tinsoft, XproxyProxy* xproxy, TMProxy* tmproxy, ProxyV6Net* proxyWeb, ShopLike* shopLike, MinProxy* minProxy, ObcProxy* obcProxy){
    while(true){
        bool flag2;
        int num;
        int num2;
        auto check = SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp");
        switch (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp")) {
        case 7:
        case 15:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            {
                QMutexLocker locker(&mutex);
                while(!isStop){
                    tinsoft = nullptr;
                    while(!isStop){
                        for (auto proxy : lstProxyTool)
                        {
                            TinsoftProxy* tinsoftProxy = dynamic_cast<TinsoftProxy*>(proxy);
                            if (tinsoftProxy)
                            {
                                if (!tinsoft || tinsoftProxy->daSuDung < tinsoft->daSuDung)
                                {
                                    tinsoft = tinsoftProxy;
                                }
                                
                            }
                        }
                        if (tinsoft->daSuDung != tinsoft->limitThreadsUse)
                        {
                            break;
                        }
                    }
                    if (isStop)
                    {
                        break;
                    }
                    if (tinsoft->daSuDung > 0 || tinsoft->changeProxy())
                    {
                        proxy = tinsoft->proxy;
                        if (proxy == "")
                        {
                            proxy = tinsoft->getProxy();
                        }
                        tinsoft->dangSuDung++;
                        tinsoft->daSuDung++;
                        break;
                    }
                }
                if (isStop)
                {
                    return;
                }
                if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
                {
                    DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
                }
                bool flag8 = true;
                if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP")){
                    statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                    SetStatusAccount(indexRow, statusProxy + "Check IP...");
                    ip = Common::CheckProxyNew(proxy, 0);
                    if (ip == "")
                    {
                        flag8 = false;
                    }
                }
                if (!flag8)
                {
                    tinsoft->dangSuDung--;
                    tinsoft->daSuDung--;
                    break;
                }
                return;
            }
        }
        case 8:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            QMutexLocker locker(&mutex);
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("typeRunXproxy") == 0){
                while (!isStop){
                    xproxy = nullptr;
                    while (!isStop){
                        for(auto item2:lstProxyTool){
                            XproxyProxy* xProxy = dynamic_cast<XproxyProxy*>(item2);
                            if (xProxy)
                            {
                                if (xProxy->isProxyLive && (xproxy == nullptr || xProxy->daSuDung < xproxy->daSuDung))
                                {
                                    xproxy = xProxy;
                                }
                            }
                        }
                        if (xproxy->daSuDung != xproxy->limitThreadsUse)
                        {
                            break;
                        }
                    }
                    if (isStop)
                    {
                        break;
                    }
                    if (xproxy->isProxyLive){
                        bool flag6 = false;
                        if (xproxy->daSuDung > 0)
                        {
                            flag6 = true;
                        }
                        else
                        {
                            switch (xproxy->changeProxy())
                            {
                            case 0:
                                xproxy->isProxyLive = false;
                                break;
                            case 1:
                                flag6 = true;
                                break;
                            }
                        }
                        if (flag6)
                        {
                            proxy = xproxy->proxy;
                            typeProxy = xproxy->typeProxy;
                            xproxy->dangSuDung++;
                            xproxy->daSuDung++;
                            break;
                        }
                    }else
                    {
                        xproxy->isProxyLive = false;
                    }
                }
            }else
            {
                while (!isStop)
                {
                    xproxy = nullptr;
                    QList<XproxyProxy*> list3;

                    for (auto item3 : lstProxyTool)
                    {
                        if (auto xProxy3 = dynamic_cast<XproxyProxy*>(item3))
                        {
                            if (xProxy3->isProxyLive)
                            {
                                if (xProxy3->daSuDung < xProxy3->limitThreadsUse)
                                {
                                    list3.append(xProxy3);
                                }
                                else if (xProxy3->dangSuDung == 0)
                                {
                                    xProxy3->resetProxy();
                                    xProxy3->daSuDung = 0;
                                }
                            }
                        }
                    }

                    for (auto proxy : list3)
                    {
                        if (proxy->checkLiveProxy(0))
                        {
                            xproxy = proxy;
                            break;
                        }
                    }

                    if (xproxy != nullptr)
                    {
                        proxy = xproxy->proxy;
                        typeProxy = xproxy->typeProxy;
                        xproxy->dangSuDung++;
                        xproxy->daSuDung++;
                        break;
                    }
                }
            }
            if(isStop){
                return;
            }
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
            {
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag7 = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP")){
                statusProxy = "(IP: " + proxy + ") ";
                emit updateStatusAccount(indexRow, statusProxy + "Check IP...");
                ip = Common::CheckProxyNew(proxy, typeProxy, SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayResetXProxy", 1) * 60);
                if (ip == "")
                {
                    xproxy->isProxyLive = false;
                    flag7 = false;
                }
            }
            if (!flag7)
            {
                xproxy->dangSuDung--;
                xproxy->daSuDung--;
                break;
            }
            return;
        }
        case 9:{
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("cbbProxy") == 0)
            {
                proxy = GetCellAccount(indexRow, "cProxy");
                typeProxy = (proxy.endsWith("*1") ? 1 : 0);
                if (proxy.endsWith("*0") || proxy.endsWith("*1"))
                {
                    proxy = proxy.mid(0, proxy.length() - 2);
                }
            }
            else
            {
                proxy = CollectionHelper::GetRandomItem(SettingsTool::GetSettings("configGeneral").GetValueList("txtProxy"));
                if (proxy == nullptr)
                {
                    proxy = "";
                }
                typeProxy = SettingsTool::GetSettings("configGeneral").GetValueInt("cbbProxyType");
            }
            return;
        }
        case 10:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            QMutexLocker locker(&mutex);
            while (!isStop){
                tmproxy = nullptr;
                while (!isStop){
                    for(auto item4:lstProxyTool){
                        TMProxy* tmProxy = dynamic_cast<TMProxy*>(item4);
                        if(tmProxy){
                            if (tmproxy == nullptr || tmProxy->daSuDung < tmproxy->daSuDung)
                            {
                                tmproxy = tmProxy;
                            }
                        }
                    }
                    if (tmproxy->daSuDung != tmproxy->limit_theads_use)
                    {
                        break;
                    }
                }
                if (isStop)
                {
                    break;
                }
                if (tmproxy->daSuDung > 0 || tmproxy->ChangeProxy())
                {
                    proxy = tmproxy->proxy;
                    if (proxy == "")
                    {
                        proxy = tmproxy->GetProxy();
                    }
                    tmproxy->dangSuDung++;
                    tmproxy->daSuDung++;
                    break;
                }
            }
            if (isStop)
            {
                return;
            }
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
            {
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag3 = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
            {
                statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                SetStatusAccount(indexRow, statusProxy + "Check IP...");
                ip = Common::CheckProxyNew(proxy, 0);
                if (ip == "")
                {
                    flag3 = false;
                }
            }
            if (!flag3)
            {
                tmproxy->dangSuDung--;
                tmproxy->daSuDung--;
                break;
            }
            return;
        }
        case 11:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            QMutexLocker locker(&mutex);
            while(!isStop){
                proxyWeb = nullptr;
                while (!isStop){
                    for(auto item5: lstProxyTool){
                        ProxyV6Net* v6 = dynamic_cast<ProxyV6Net*>(item5);
                        if(v6){
                            if (proxyWeb == nullptr || v6->daSuDung < proxyWeb->daSuDung)
                            {
                                proxyWeb = v6;
                            }
                        }
                    }
                    if (proxyWeb->daSuDung != proxyWeb->limitThreadsUse)
                    {
                        break;
                    }
                }
                if (isStop)
                {
                    break;
                }
                if (proxyWeb->daSuDung > 0 || proxyWeb->ChangeProxy())
                {
                    proxy = proxyWeb->proxy;
                    typeProxy = proxyWeb->typeProxy;
                    proxyWeb->dangSuDung++;
                    proxyWeb->daSuDung++;
                    break;
                }
            }
            if (isStop)
            {
                return;
            }
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
            {
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag4 = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
            {
                statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                emit updateStatusAccount(indexRow, statusProxy + "Check IP...");
                for (int k = 0; k < 30; k++)
                {
                    Common::DelayTime(1.0);
                    ip = Common::CheckProxyNew(proxy, typeProxy);
                    if (ip != "")
                    {
                        break;
                    }
                    if (isStop)
                    {
                        return;
                    }
                }
                if (ip == "")
                {
                    flag4 = false;
                }
            }
            if (!flag4)
            {
                proxyWeb->dangSuDung--;
                proxyWeb->daSuDung--;
                break;
            }
            return;
        }
        case 12:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            QMutexLocker locker(&mutex);
            while(!isStop){
                shopLike = nullptr;
                while (!isStop){
                    for(auto item6:lstProxyTool){
                        ShopLike* sL = dynamic_cast<ShopLike*>(item6);
                        if(sL){
                            if (shopLike == nullptr || sL->daSuDung < shopLike->daSuDung)
                            {
                                shopLike = sL;
                            }
                        }
                    }
                    if (shopLike->daSuDung != shopLike->limitThreadsUse)
                    {
                        break;
                    }
                }
                if (isStop)
                {
                    break;
                }
                if (shopLike->daSuDung > 0 || shopLike->ChangeProxy())
                {
                    proxy = shopLike->proxy;
                    if (proxy == "")
                    {
                        proxy = shopLike->GetProxy();
                    }
                    shopLike->dangSuDung++;
                    shopLike->daSuDung++;
                    break;
                }
            }
            if (isStop)
            {
                return;
            }
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
            {
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag5 = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
            {
                statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                SetStatusAccount(indexRow, statusProxy + "Check IP...");
                ip = Common::CheckProxy(proxy, 0);
                if (ip == "")
                {
                    flag5 = false;
                }
            }
            if (!flag5)
            {
                shopLike->dangSuDung--;
                shopLike->daSuDung--;
                break;
            }
            return;
        }
        case 13:{
            emit updateStatusAccount(indexRow, Language::GetValue("Đang lấy Api MinProxy..."));
            minProxy = nullptr;
            flag2 = false;
            num = 0;
            if (isStop)
            {
                return;
            }
            QMutexLocker locker(&mutex);
            while (!isStop)
            {
                for (auto item7 : lstProxyTool)
                {
                    MinProxy* mProxy = dynamic_cast<MinProxy*>(item7);
                    if(mProxy){
                        if (mProxy->dangSuDung == 0)
                        {
                            minProxy = mProxy;
                            break;
                        }
                        if (minProxy == nullptr || mProxy->daSuDung < minProxy->daSuDung)
                        {
                            minProxy = mProxy;
                        }
                    }
                }
                if (minProxy->daSuDung < minProxy->limit_theads_use)
                {
                    break;
                }
            }
            if (minProxy != nullptr)
            {
                minProxy->dangSuDung++;
                minProxy->daSuDung++;
                num = minProxy->daSuDung;
                goto IL_0d06;
            }
            goto IL_0f67;
        }
        case 14:{
            emit updateStatusAccount(indexRow, "Get Proxy...");
            QMutexLocker locker(&mutex);
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("typeRunObcProxy") == 0){
                while (!isStop){
                    obcProxy = nullptr;
                    QList<ObcProxy*> list;
                    for(auto item8:lstProxyTool){
                        ObcProxy* oProxy = dynamic_cast<ObcProxy*>(item8);
                        if(oProxy){
                            if (oProxy->isProxyLive)
                            {
                                if (oProxy->daSuDung < oProxy->limit_theads_use)
                                {
                                    list.append(oProxy);
                                }
                                else if (oProxy->dangSuDung == 0)
                                {
                                    oProxy->ResetProxy();
                                    oProxy->daSuDung = 0;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < list.count(); i++)
                    {
                        if (list.at(i)->CheckLiveProxy(0))
                        {
                            obcProxy = list.at(i);
                            break;
                        }
                    }
                    if (obcProxy != nullptr)
                    {
                        proxy = obcProxy->proxy;
                        typeProxy = obcProxy->typeProxy;
                        obcProxy->dangSuDung++;
                        obcProxy->daSuDung++;
                        break;
                    }
                }
            }else{
                while (!isStop)
                {
                    obcProxy = nullptr;
                    QList<ObcProxy*> list2;
                    for (auto item9 : listObcDcom)
                    {
                        if (item9->IsCanReset())
                        {
                            item9->ResetDcom();
                            list2.append(item9->GetListProxy());
                        }
                        else
                        {
                            list2.append(item9->GetListProxyCanUse());
                        }
                    }
                    for (int j = 0; j < list2.count(); j++)
                    {
                        if (list2.at(j)->CheckLiveProxy(0))
                        {
                            obcProxy = list2.at(j);
                            break;
                        }
                    }
                    if (obcProxy != nullptr)
                    {
                        proxy = obcProxy->proxy;
                        typeProxy = obcProxy->typeProxy;
                        obcProxy->dangSuDung++;
                        obcProxy->daSuDung++;
                        break;
                    }
                }
            }
            if (isStop)
            {
                emit updateStatusAccount(indexRow, statusProxy + Language::GetValue("Đã dừng!"));
                return;
            }
            if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
            {
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "Trạng thái", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
            {
                statusProxy = "(IP: " + proxy + ") ";
                SetStatusAccount(indexRow, statusProxy + "Check IP...");
                ip = Common::CheckProxy(proxy, typeProxy, SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIPObcProxy", 1) * 60);
                if (ip == "")
                {
                    obcProxy->isProxyLive = false;
                    flag = false;
                }
            }
            if (!flag)
            {
                obcProxy->dangSuDung--;
                obcProxy->daSuDung--;
                break;
            }
            return;
        }
        IL_0f67:{
            if (!flag2)
            {
                minProxy->dangSuDung--;
                minProxy->daSuDung--;
                break;
            }
            return;
        }
        IL_0d06:{
            emit updateStatusAccount(indexRow, Language::GetValue("Đang lấy Proxy từ API..."));
            num2 = 0;
            if (num > 1)
            {
                while (minProxy->isBlock)
                {
                    Common::DelayTime(1.0);
                    num2++;
                    if (num2 > 60)
                    {
                        break;
                    }
                }
                proxy = minProxy->GetProxy();
            }
            else
            {
                while (!isStop)
                {
                    switch (minProxy->ChangeProxy())
                    {
                    case -2:{
                        emit updateStatusAccount(indexRow, Language::GetValue("Api không đúng"));
                        QMutexLocker locker(&mutex);
                        lstProxyTool.removeOne(minProxy);
                        break;
                    }
                    case -1:{
                        emit updateStatusAccount(indexRow, Language::GetValue("Api hết hạn"));
                        QMutexLocker locker(&mutex);
                        lstProxyTool.removeOne(minProxy);
                        break;
                    }
                    case 0:{
                        emit updateStatusAccount(indexRow, Language::GetValue("Đang lấy Proxy từ API: Chờ " + QString::number(minProxy->next_change) + " s"));
                        if (minProxy->next_change > 10)
                        {
                            Common::DelayTime(10.0);
                        }
                        else if (minProxy->next_change > 0)
                        {
                            Common::DelayTime(minProxy->next_change);
                        }
                        goto IL_0e83;
                    }
                    case 1:
                        proxy = minProxy->proxy;
                        minProxy->isBlock = false;
                        goto IL_0e83;
                    default:
                        goto IL_0e83;
                    }
                    goto end_IL_0019;
                IL_0e83:
                    if (proxy != "")
                    {
                        break;
                    }
                }
            }
            if (!(proxy == ""))
            {
                flag2 = true;
                if (SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP") > 0)
                {
                    SetStatusAccount(indexRow, statusProxy + "Delay check IP...");
                    Common::DelayTime(SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"));
                }
                if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
                {
                    statusProxy = "(IP: " + proxy + ") ";
                    SetStatusAccount(indexRow, statusProxy + "Check IP...");
                    ip = Common::CheckProxyNew(proxy, (SettingsTool::GetSettings("configGeneral").GetValueInt("typeProxyMin") >= 2) ? 1 : 0);
                    if (ip == "")
                    {
                        flag2 = false;
                    }
                }
            }
            goto IL_0f67;
        end_IL_0019:
            break;
        }
        default:
            return;
        }
    }
}

void MainWindow::ReadResultSpam(){
    dicSpamBaiVietIdPostOld = QMap<QString,QStringList>(); // Stack-allocated QMap

    try {
        QString value = SettingsTool::GetSettings("configGeneral").GetValue("pathResult", "output\\resultSpam");
        if (value == "output\\resultSpam")
        {
            Common::CreateFolder("output");
            Common::CreateFolder("output\\resultSpam");
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception caught: " << e.what();
    } catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

QMap<QString,QStringList> MainWindow::GetDictionaryIntoHanhDong(QString idKichBan, QString tenTuongTac, QString field){
    QMutexLocker locker(&mutex);
    QMap<QString,QStringList> dictionary;
    try {
        QStringList idHanhDongByIdKichBanAndTenTuongTac = InteractSQL::GetIdHanhDongByIdKichBanAndTenTuongTac(idKichBan, tenTuongTac);
        for (const auto& text : idHanhDongByIdKichBanAndTenTuongTac)
        {
            JSON_Settings jSON_Settings(InteractSQL::GetCauHinhFromHanhDong(text), true);
            QStringList fieldList = {"txtUid", "lstNhomTuNhap", "txtLinkChiaSe", "txtIdPost", "txtLink"};
            QStringList list = fieldList.contains(field) ?
                                   jSON_Settings.GetValueList(field) :
                                   jSON_Settings.GetValueList(field, jSON_Settings.GetValueInt("typeNganCach"));
            dictionary.insert(text, list);
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception caught: " << e.what();
    } catch (...) {
        qDebug() << "Unknown exception caught";
    }
    return dictionary;
}


void MainWindow::RandomThuTuTaiKhoan(int soLuot){
    try {
        auto model = ui->tableView->model();
        CustomTableModel *customModel = qobject_cast<CustomTableModel *>(model);
        if (!customModel) {
            throw std::runtime_error("Invalid model type");
        }

        for (int var = 0; var < soLuot; ++var) {
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            if (rowCount <= 1) {
                continue;
            }

            QVector<QVector<QVariant>> list;
            list.reserve(rowCount);

            for (int i = 0; i < rowCount; i++) {
                QVector<QVariant> rowData;
                rowData.reserve(columnCount);
                for (int col = 0; col < columnCount; ++col) {
                    rowData.append(model->index(i, col).data());
                }
                list.append(std::move(rowData));
            }

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(list.begin(), list.end(), g);

            customModel->clearRows();
            for (const auto &item : list) {
                customModel->addRow(item);
            }
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception caught: " << e.what();
    } catch (...) {
        qDebug() << "Unknown exception caught";
    }
}
void ShowTrangThai(const QString& content, QWidget* plTrangThai, QLabel* lblTrangThai) {
    QMetaObject::invokeMethod(plTrangThai, [plTrangThai]() {
            if (!plTrangThai->isVisible()) {
                plTrangThai->setVisible(true);
            }
        }, Qt::QueuedConnection);
    
    QMetaObject::invokeMethod(lblTrangThai, [lblTrangThai, content]() {
            lblTrangThai->setText(content);
        }, Qt::QueuedConnection);
}
void MainWindow::DeleteCacheProfile(int row){
    try {
        QString text = ui->tableView->model()->index(row,Utils::GetIndexByColumnHeader(ui->tableView,"Uid")).data().toString();
        if(text.trimmed() == ""){
            emit updateStatusAccount(row, Language::GetValue("Chưa tạo profile!"));
            return;
        }
        QString text2 = SettingsTool::GetSettings("configGeneral").GetValue("txbPathProfile") + "\\" + text;
        QDir dir(text2);
        if(dir.exists()){
            Common::deleteDirectory(text2 + "\\Default\\Cache");
            Common::deleteDirectory(text2 + "\\Default\\Code Cache");
            Common::deleteDirectory(text2 + "\\OptimizationGuidePredictionModels");
            Common::deleteDirectory(text2 + "\\Default\\optimization_guide_prediction_model_downloads");
            Common::deleteDirectory(text2 + "\\SwReporter");
            Common::deleteDirectory(text2 + "\\pnacl");
            emit updateStatusAccount(row, Language::GetValue("Xóa Cache Profile thành công!"));
        }else{
            emit updateStatusAccount(row, Language::GetValue("Chưa tạo profile!"));
        }
    } catch (...) {
        emit updateStatusAccount(row, Language::GetValue("Xóa Cache Profile thất bại!"));
    }
}
bool MainWindow::IsChooseRow(){
    int result = 0 ;
    try {
        if(CountChooseRowInDatagridview() == 0){
            MessageBoxHelper::Show("Vui lòng chọn tài khoản muốn sử dụng chức năng này!", 3);
            return false;
        }
        return true;
    } catch (...) {
    }
}

int MainWindow::CountChooseRowInDatagridview(){
    int result = 0;
    try {
        QDir dir("settings/setting");
        if (dir.exists()) {
            // Directory exists, do nothing or add your logic here if needed
        }
        
        bool ok;
        int count = ui->lblCountSelect->text().toInt(&ok);
        if (ok) {
            result = count;
        } else {
            // Handle the case where the conversion fails if necessary
            qDebug() << "Conversion to integer failed.";
        }
    } catch (...) {
        // Handle any unexpected exceptions
        qDebug() << "An unexpected error occurred.";
    }
    
    return result;
}


QList<ProxyTool*> MainWindow::GetListProxy(int maxThread){
    QList<ProxyTool*> list ;
    switch (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp")) {
    case 7:{
        QList<QString> listKeyTinsoft = GetListKeyTinsoft();
        if(listKeyTinsoft.size() != 0){
            for (int num2 = 0; num2 < listKeyTinsoft.size(); num2++)
            {
                list.append(new TinsoftProxy("http://proxy.tinsoftsv.com", listKeyTinsoft[num2], SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTinsoft"), SettingsTool::GetSettings("configGeneral").GetValueInt("cbbLocationTinsoft")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTinsoft") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTinsoft");
            }
        }
        break;
    }
    case 8:{
        QList<QString> valueList2 = SettingsTool::GetSettings("configGeneral").GetValueList("txtListProxy");
        if(valueList2.count() != 0){
            for (int var = 0; var < valueList2.count(); var++) {
                list.append(new XproxyProxy(SettingsTool::GetSettings("configGeneral").GetValue("txtServiceURLXProxy"), valueList2[var], SettingsTool::GetSettings("configGeneral").GetValueInt("typeProxy"), SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPXProxy")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPXProxy") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPXProxy");
            }
        }
        break;
    }
    case 10:{
        QList<QString> valueList7 = SettingsTool::GetSettings("configGeneral").GetValueList("txtApiKeyTMProxy");
        if(valueList7.count() != 0){
            for(int num3 = 0; num3 < valueList7.count();num3++){
                list.append(new TMProxy(valueList7[num3], 0, SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTMProxy")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTMProxy") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPTMProxy");
            }
        }
        break;
    }
    case 11:{
        auto valueList5 = SettingsTool::GetSettings("configGeneral").GetValueList("txtListProxyv6");
        if(valueList5.count() != 0){
            for(int num4 = 0; num4 < valueList5.count();num4++){
                list.append(new ProxyV6Net(valueList5[num4], SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyv6")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyv6") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyv6");
            }
        }
        break;
    }
    case 12:{
        auto valueList3 = SettingsTool::GetSettings("configGeneral").GetValueList("txtApiShopLike");
        if(valueList3.count() != 0){
            for(int num4 = 0; num4 < valueList3.count();num4++){
                list.append(new ShopLike(valueList3[num4], 0, SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPShopLike")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPShopLike") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPShopLike");
            }
        }
        break;
    }
    case 13:{
        auto valueList4 = SettingsTool::GetSettings("configGeneral").GetValueList("txtApiKeyMinProxy");
        if (valueList4.count() != 0)
        {
            for (int m = 0; m < valueList4.count(); m++)
            {
                list.append(new MinProxy(SettingsTool::GetSettings("configGeneral").GetValueInt("typeMin"), valueList4[m], SettingsTool::GetSettings("configGeneral").GetValueInt("typeProxyMin"), SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPMinProxy")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPMinProxy") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPMinProxy");
            }
        }
        break;
    }
    case 14:{
        QList<QString> valueList6 = SettingsTool::GetSettings("configGeneral").GetValueList("txtListObcProxy");
        if (valueList6.count() == 0)
        {
            break;
        }
        QMap<QString, QList<QString>> listDcomPort = ObcDcom::GetListDcomPort(SettingsTool::GetSettings("configGeneral").GetValue("txtLinkWebObcProxy"));
        for (int num = 0; num < valueList6.count(); num++)
        {
            QString port = valueList6[num].split(':')[1];
            QString key = Utils::findKeyWithPort(listDcomPort, port);
            if (!key.isEmpty()) {
                ObcDcom* obcDcom = ObcDcom::GetExistObcDcom(listObcDcom, key);
                if (obcDcom == nullptr) {
                    obcDcom = new ObcDcom(key);
                    listObcDcom.append(obcDcom);
                }
                ObcProxy* obcProxy = new ObcProxy(
                    SettingsTool::GetSettings("configGeneral").GetValue("txtLinkWebObcProxy"),
                    valueList6[num],
                    0,
                    SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPObcProxy"),
                    key
                    );
                obcDcom->AddProxy(obcProxy);
            }
        }
        if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPObcProxy") < maxThread)
        {
            maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPObcProxy");
        }
        break;
    }
    case 15 :{
        QList<QString> valueList = SettingsTool::GetSettings("configGeneral").GetValueList("txtApiKeyProxyFb");
        if (valueList.count() != 0)
        {
            for (int i = 0; i < valueList.count(); i++)
            {
                list.append(new TinsoftProxy("http://api.proxyfb.com", valueList[i], SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyFb")));
            }
            if (list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyFb") < maxThread)
            {
                maxThread = list.count() * SettingsTool::GetSettings("configGeneral").GetValueInt("nudLuongPerIPProxyFb");
            }
        }
        break;
    }
    default:
        list.clear();
        break;
    }
    return list;
}



QList<QString> MainWindow::GetListKeyTinsoft(){
    QList<QString> list;
    try
    {
        if (SettingsTool::GetSettings("configGeneral").GetValueInt("typeApiTinsoft") == 0)
        {
            auto json = Utils::parseJsonString((new RequestHandle("", "Mozilla/4.0 (compatible; MSIE 6.0; windows NT 5.2; .NET CLR 1.0.3705;)", "", 0))->RequestGet("http://proxy.tinsoftsv.com/api/getUserKeys.php?key=" + SettingsTool::GetSettings("configGeneral").GetValue("txtApiUser")))["data"].toArray();
            for (const QJsonValue &value : json) {
                QJsonObject item = value.toObject();
                if (item["success"].toBool()) {
                    list.append(item["key"].toString());
                }
            }
            return list;
        }
        for(const QString &value:SettingsTool::GetSettings("configGeneral").GetValueList("txtApiProxy")){
            if(TinsoftProxy::checkApiProxy(value)){
                list.append(value);
            }
        }
        return list;
    }
    catch(...)
    {
        return list;
    }
}

void MainWindow::OpenFormViewChrome(){
    bool flag = false;
    foreach (QWidget *openForm, QApplication::topLevelWidgets())
    {
        if (openForm->objectName() == "fViewChrome")
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        (new fViewChrome(this))->show();
    }
}

void MainWindow::ScreenCaptureError(Chrome* chrome, const QString& uid, int type)
{
    try {
        if (chrome != nullptr) {
            QString path = QDir::currentPath() + "/log_capture";

            switch (type) {
            case 0:
                path += "/checkpoint";
                break;
            case 1:
                path += "/loginfail";
                break;
            case 2:
                path += "/disconnect";
                break;
            }

            QDir().mkpath(path);

            chrome->ScreenCapture(path, uid);

            QFile urlFile(path + "/" + uid + ".txt");
            if (urlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&urlFile);
                out << chrome->GetUrl();
                urlFile.close();
            }

            QFile htmlFile(path + "/" + uid + ".html");
            if (htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&htmlFile);
                out << chrome->GetPageSource();
                htmlFile.close();
            }
        }
    }
    catch (const std::exception& e) {
        // Handle or log the exception
        qDebug() << "Exception in ScreenCaptureError: " << e.what();
    }
}


bool MainWindow::CheckDangCheckpointNew(Chrome* chrome, int indexRow, QString statusAction, bool isUnlock956, int typeWebUnlock956){
    QString text = "";
    QString cssSelectorsOrXpath = "[href*=\"facebook.com/security/2fac/setup/intro/\"]";
    auto check = chrome->CheckExistElement(cssSelectorsOrXpath);
    if(chrome->CheckExistElement(cssSelectorsOrXpath) == 1){
        QString cellAccount = GetCellAccount(indexRow, "Mật khẩu");
        if (!(cellAccount == "")){
            int num = 0;
            int num2 = 3;
            QString text2 = "";
            // do{
            //     auto list =  *new QStringList { "[type=\"submit\"]" };
            //     QString text3 = chrome->CheckExistElements(0.0, list);
            //     if (text3 == "[type=\"submit\"]"){
            //         auto check = chrome->CheckExistElement("[href^=\"/security/2fac/setup/turn_off/\"]");
            //         if (chrome->CheckExistElement("[href^=\"/security/2fac/setup/turn_off/\"]").toInt() == 1){
            //             if (text2 != "")
            //             {
            //                 emit updateCellAccount(indexRow, "cFa2", text2, "fa2");
            //                 return true;
            //             }
            //             auto check =chrome->CheckExistElement("[href*=\"/security/2fac/setup/qrcode/generate/\"]");
            //             if (chrome->CheckExistElement("[href*=\"/security/2fac/setup/qrcode/generate/\"]").toInt() == 1)
            //             {
            //                 text3 = "[href*=\"/security/2fac/setup/qrcode/generate/\"]";
            //                 QString value = QRegularExpression("https://(.*?)facebook\\.com")
            //                                     .match(chrome->GetUrl())
            //                                     .captured(0);
            //                 QString text4 = chrome->GetAttributeValue(text3, "href");
            //                 if (!text4.startsWith("http"))
            //                 {
            //                     text4 = value + text4;
            //                 }
            //                 chrome->GotoURL(text4);
            //             }
            //         }else if(chrome->CheckExistElement("[name=\"pass\"]").toInt() == 1){
            //             if (chrome->ExecuteScript("return document.querySelector('[data-sigil=\"marea\"] .mfsm').innerText") != "")
            //             {
            //                 emit updateInfoAccount(indexRow, "Changed pass");
            //                 emit updateStatusAccount(indexRow, statusAction + Language::GetValue("Mật khẩu không đúng!"));
            //                 return false;
            //             }
            //         }
            //     }
            // }while();
        }
    }
}

void MainWindow::on_metroButton1_clicked()
{
    Common::KillProcess("undetected_chromedriver");
}

// QString MainWindow::GetPasswordRecoverPass()
// {
//     QString content = Common::createRandomString(6) + Common::createRandomNumber(4) + Common::createRandomString(5);
//     if (SettingsTool::GetSettings("configGeneral").GetValueInt("typePass") == 0)
//     {
//         content = SettingsTool::GetSettings("configGeneral").GetValue("txtPass");
//     }
//     return content.RandomChar(1);
// }
