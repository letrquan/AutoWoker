#include "mainwindow.h"
#include "fcauhinhchung.h"
#include "fcauhinhtuongtac.h"
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
    connect(this, &MainWindow::updateStatusAccount, this, &MainWindow::SetStatusAccount, Qt::QueuedConnection);
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
void MainWindow::LoadDtgvAccFromDatatable(QVariantList* tableAccount){
    cusModel->loadDataFromDatabase(tableAccount);
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
            if (ui->tableView->model()->index(i,Utils::GetIndexByColumnHeader(ui->tableView,"Select")).data().toInt() == 1)
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

void MainWindow::KiemTraTaiKhoan(int type, bool useProxy) {
    QThreadPool::globalInstance()->setMaxThreadCount(SettingsTool::GetSettings("configGeneral").GetValueInt("nudHideThread", 10));
    auto tokenTrunggian = SettingsTool::GetSettings("configGeneral").GetValue("token");
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);

    connect(watcher, &QFutureWatcher<void>::started, this, [this]() {
        cControl("start");
    });
    connect(watcher, &QFutureWatcher<void>::finished, this, [this]() {
        cControl("database");
        if (CommonSQL::UpdateStatuses(*statusSQL, "status")) {
            statusSQL->clear();
        }
        if (CommonSQL::UpdateStatuses(*infoSQL, "info")) {
            infoSQL->clear();
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
        RequestHandle requestXNet(cookie, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36", proxy, typeProxy);
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


void MainWindow::CheckMyWall(int row, QString tokenTg){
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
    }catch (const std::exception& e) {
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
        if (ui->btnInteract->styleSheet().contains("stop-button.png"))
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
        int maxThread = SettingsTool::GetSettings("configGeneral").GetValueInt("nudInteractThread", 3);
        lstProxyTool = GetListProxy(maxThread);
        if(!lstProxyTool.isEmpty() && lstProxyTool.count() ==0){
            MessageBoxHelper::Show("Proxy không đủ, vui lòng cấu hình lại!", 2);
            return;
        }
        QList<int> lstPossition = *new QList<int>();
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
        QFuture<void> thread= QtConcurrent::run([this, settings, maxThread, &lstPossition, &curChangeIp, &isChangeIPSuccess]() {
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
                            QFuture<void> thread3 = QtConcurrent::run([this,&maxThread, &lstPossition, &idKichBan, &settings, &curChangeIp, &isChangeIPSuccess]{
                                try {
                                    int num13 = 0;
                                    while(num13<ui->tableView->model()->rowCount() && !isStop){
                                        if(ui->tableView->model()->index(num13,Utils::GetIndexByColumnHeader(ui->tableView,"Select")).data(Qt::CheckStateRole).toBool()){
                                            if(isStop){
                                                break;
                                            }
                                            if(QThreadPool::globalInstance()->activeThreadCount()< maxThread){
                                                if (isStop)
                                                {
                                                    break;
                                                }
                                                QFuture<void> thread6 = QtConcurrent::run([&num13, &lstPossition, &idKichBan, &settings, this]{
                                                    int indexOfPossitionApp2 = Common::GetIndexOfPositionApp(lstPossition);
                                                    try {
                                                        ExcuteOneThread(num13, indexOfPossitionApp2, idKichBan, settings);
                                                        Common::FillIndexPossition(lstPossition,indexOfPossitionApp2);
                                                        QString p = "Proxy chưa ủy quyền!";
                                                        if (!SettingsTool::GetSettings("configInteractGeneral").GetValueBool("ckbRepeatAll") || GetInfoAccount(num13) != "Live" || GetStatusAccount(num13).toLower().contains("checkpoint") || GetStatusAccount(num13).toLower().contains("invalid username or password") || GetStatusAccount(num13).toLower().contains(p.toLower()))
                                                        {
                                                            emit updateCellAccount(num13, "cChose", Qt::Unchecked);
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
    QString text3 = GetCellAccount(indexRow, "cUid");
    QString cellAccount = GetCellAccount(indexRow, "cId");
    QString cellAccount2 = GetCellAccount(indexRow, "cEmail");
    QString cellAccount3 = GetCellAccount(indexRow, "cPassMail");
    QString cellAccount4 = GetCellAccount(indexRow, "cFa2");
    QString cellAccount5 = GetCellAccount(indexRow, "cPassword");
    QString text4 = GetCellAccount(indexRow, "cCookies");
    QString text5 = GetCellAccount(indexRow, "cToken");
    QString cellAccount6 = GetCellAccount(indexRow, "cUseragent");
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

        }
    } catch (...) {
    }
}

void MainWindow::GetProxy(int indexRow, bool isStop, QString proxy, int typeProxy, QString statusProxy, QString ip, TinsoftProxy* tinsoft, XproxyProxy* xproxy, TMProxy* tmproxy, ProxyV6Net* proxyWeb, ShopLike* shopLike, MinProxy* minProxy, ObcProxy* obcProxy){
    while(true){
        bool flag2;
        int num;
        int num2;
        switch (SettingsTool::GetSettings("configGeneral").GetValueInt("ip_iTypeChangeIp")) {
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
                    DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "cStatus", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
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
                    QList<XproxyProxy> list3 = *new QList<XproxyProxy>();
                    for (auto item3: lstProxyTool)
                    {
                        XproxyProxy* xProxy3 = dynamic_cast<XproxyProxy*>(item3);
                        if (xProxy3)
                        {
                            if (xProxy3->isProxyLive)
                            {
                                if (xProxy3->daSuDung < xProxy3->limitThreadsUse)
                                {
                                    list3.append(*xProxy3);
                                }
                                else if (xProxy3->dangSuDung == 0)
                                {
                                    xProxy3->resetProxy();
                                    xProxy3->daSuDung = 0;
                                }
                            }
                        }

                    }
                    for (int l = 0; l < list3.count(); l++)
                    {
                        if (list3[l].checkLiveProxy(0))
                        {
                            xproxy = &list3[l];
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
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "cStatus", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
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
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "cStatus", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
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
                DatagridviewHelper::SetStatusDataGridViewWithWait(ui->tableView, indexRow, "cStatus", SettingsTool::GetSettings("configGeneral").GetValueInt("nudDelayCheckIP"), statusProxy + "Delay after change ip {time}s...");
            }
            bool flag4 = true;
            if (!SettingsTool::GetSettings("configGeneral").GetValueBool("ckbKhongCheckIP"))
            {
                statusProxy = "(IP: " + proxy.split(':')[0] + ") ";
                SetStatusAccount(indexRow, statusProxy + "Check IP...");
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
        default:
            break;
        }
    }
}

void MainWindow::ReadResultSpam(){
    dicSpamBaiVietIdPostOld = *new QMap<QString,QStringList>();
    try {
        QString value = SettingsTool::GetSettings("configGeneral").GetValue("pathResult", "output\\resultSpam");
        if (value == "output\\resultSpam")
        {
            Common::CreateFolder("output");
            Common::CreateFolder("output\\resultSpam");
        }
    } catch (...) {
    }
}

QMap<QString,QStringList> MainWindow::GetDictionaryIntoHanhDong(QString idKichBan, QString tenTuongTac, QString field){
    QMap<QString,QStringList> dictionary;
    try {
        QStringList idHanhDongByIdKichBanAndTenTuongTac = InteractSQL::GetIdHanhDongByIdKichBanAndTenTuongTac(idKichBan, tenTuongTac);
        if (idHanhDongByIdKichBanAndTenTuongTac.count() > 0){
            for (int i = 0; i < idHanhDongByIdKichBanAndTenTuongTac.count(); i++)
            {
                QString text = idHanhDongByIdKichBanAndTenTuongTac[i];
                JSON_Settings jSON_Settings = *new JSON_Settings(InteractSQL::GetCauHinhFromHanhDong(text), true);
                QStringList list;
                list = ((!(new QStringList { "txtUid", "lstNhomTuNhap", "txtLinkChiaSe", "txtIdPost", "txtLink" })->contains(field)) ? jSON_Settings.GetValueList(field, jSON_Settings.GetValueInt("typeNganCach")) : jSON_Settings.GetValueList(field));
                dictionary.insert(text, list);
            }
        }
    } catch (...) {
    }
    return dictionary;
}


void MainWindow::RandomThuTuTaiKhoan(int soLuot){
    try {
        for (int var = 0; var < soLuot; ++var) {
            if(ui->tableView->model()->rowCount() <=1){
                continue;
            }
            QVector<QVector<QVariant>> list;
            for(int i =0; i<ui->tableView->model()->rowCount();i++){
                QVector<QVariant> rowData;
                for (int col = 0; col < ui->tableView->model()->columnCount(); ++col) {
                    rowData.append(ui->tableView->model()->index(i, col).data());
                }
                list.append(rowData);
            }
            int num = list.count();
            while (num > 1){
                num--;
                int index = QRandomGenerator::global()->bounded(num+1);
                auto value = list[index];
                list[index] = list[num];
                list[num] = value;
            }
            CustomTableModel *customModel = qobject_cast<CustomTableModel *>(ui->tableView->model());
            customModel->clearRows();
            for(auto item:list){
                customModel->addRow(item);
            }
        }
    } catch (...) {
    }
}
void ShowTrangThai(const QString& content, QWidget* plTrangThai, QLabel* lblTrangThai) {
    // Ensure plTrangThai visibility is set in the main thread
    QMetaObject::invokeMethod(plTrangThai, [plTrangThai]() {
            if (!plTrangThai->isVisible()) {
                plTrangThai->setVisible(true);
            }
        }, Qt::QueuedConnection);

    // Set lblTrangThai text in the main thread
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
            auto json = Utils::parseJsonString((new RequestHandle("", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;)", "", 0))->RequestGet("http://proxy.tinsoftsv.com/api/getUserKeys.php?key=" + SettingsTool::GetSettings("configGeneral").GetValue("txtApiUser")))["data"].toArray();
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
