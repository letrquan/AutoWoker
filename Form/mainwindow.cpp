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
    // QFutureWatcher<void> watcher;
    // QFuture<void> future;

    // connect(&watcher, &QFutureWatcher<void>::finished, this, [this]() {
    //     cControl("stop");
    // });

    // future = QtConcurrent::run([this, tokenTrunggian, &future, type]() {
    //     cControl("start");

    //     switch (type) {
    //     case 0:
    //         future = QtConcurrent::run([this, tokenTrunggian]() {
    //             int num = 0;
    //             while (num < ui->tableView->model()->rowCount() && !isStop) {
    //                 if (ui->tableView->model()->index(num, 0).data(Qt::CheckStateRole) == Qt::Checked) {
    //                     QtConcurrent::run(&MainWindow::CheckMyWall, this, num, tokenTrunggian);
    //                 }
    //                 num++;
    //             }
    //         });
    //         break;

    //     case 3:
    //         future = QtConcurrent::run([this]() {
    //             int num1 = 0;
    //             while (num1 < ui->tableView->model()->rowCount() && !isStop) {
    //                 if (ui->tableView->model()->index(num1, 0).data(Qt::CheckStateRole) == Qt::Checked) {
    //                     QtConcurrent::run(&MainWindow::CheckDangCheckpoint, this, num1);
    //                 }
    //                 num1++;
    //             }
    //         });
    //         break;

    //     default:
    //         break;
    //     }

    //     int tickCount = GetTickCount();
    //     while (QThreadPool::globalInstance()->activeThreadCount() > 0 && GetTickCount() - tickCount <= 60000) {
    //         QMetaObject::invokeMethod(QApplication::instance(), []() {
    //                 QApplication::processEvents();
    //             }, Qt::AutoConnection);
    //         QThread::sleep(1);
    //     }
    // });

    // watcher.setFuture(future);
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);

    connect(watcher, &QFutureWatcher<void>::started, this, ([this](){
                cControl("start");
            }));
    connect(watcher, &QFutureWatcher<void>::finished, this, ([this](){
                cControl("database");
                CommonSQL::UpdateStatuses(*statusSQL,"status");
                CommonSQL::UpdateStatuses(*infoSQL,"info");
                cControl("stop");
            }));

    QFuture<void> future = QtConcurrent::run([this, tokenTrunggian, type]() {
        switch (type) {
        case 0:
            QtConcurrent::run([this, tokenTrunggian]() {
                int num = 0;
                while (num < ui->tableView->model()->rowCount() && !isStop) {
                    if (ui->tableView->model()->index(num, 0).data(Qt::CheckStateRole) == Qt::Checked) {
                        QtConcurrent::run(&MainWindow::CheckMyWall, this, num, tokenTrunggian);
                    }
                    num++;
                }
            });
            break;

        case 3:
            QtConcurrent::run([this]() {
                int num1 = 0;
                while (num1 < ui->tableView->model()->rowCount() && !isStop) {
                    if (ui->tableView->model()->index(num1, 0).data(Qt::CheckStateRole) == Qt::Checked) {
                        QtConcurrent::run(&MainWindow::CheckDangCheckpoint, this, num1);
                    }
                    num1++;
                }
            });
            break;

        default:
            break;
        }

        // int tickCount = GetTickCount();
        // while (QThreadPool::globalInstance()->activeThreadCount() > 0 && GetTickCount() - tickCount <= 60000) {
        //     QMetaObject::invokeMethod(QCoreApplication::instance(), []() {
        //             QCoreApplication::processEvents();
        //         }, Qt::BlockingQueuedConnection);
        //     QThread::sleep(1);
        // }
    });

    watcher->setFuture(future);
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
            SetCellAccount(row, "Tên", value);
            SetCellAccount(row, "Bạn Bè", value2);
            SetCellAccount(row, "Ngày tạo tài khoản", value3);
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

