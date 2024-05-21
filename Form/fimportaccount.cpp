#include "fimportaccount.h"
#include "fimportaccountformatinput.h"
#include "ui_fimportaccount.h"
#include "../maxcare/Language.h"
#include "../MCommon/commonsql.h"
#include "../MCommon/Common.h"
#include "../maxcare/MessageBoxHelper.h"
#include <QThread>
#include "../MCommon/connector.h"
#include "faddfile.h"
#include "../Utils/Utils.h"
fImportAccount::fImportAccount(QString idFile,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fImportAccount)
{
    ui->setupUi(this);
    Language::SetLanguage(this);
    Load_cbbThuMuc();
    if (idFile != "" && idFile != "-1" && idFile != "999999")
    {
        ui->cbbThuMuc->setItemData(ui->cbbThuMuc->currentIndex(),idFile);
    }
    lstCbbDinhDang =
        {
            ui->cbbDinhDang1, ui->cbbDinhDang2, ui->cbbDinhDang3, ui->cbbDinhDang4, ui->cbbDinhDang5, ui->cbbDinhDang6, ui->cbbDinhDang7, ui->cbbDinhDang8, ui->cbbDinhDang9, ui->cbbDinhDang10,
            ui->cbbDinhDang11
        };
    ui->cbbThuMuc->setCurrentIndex(0);
    isAddFile = false;
    isAddAccount = false;
    idFileAdded =-1;
    this->setWindowTitle("Import Account");
    fImportAccount_Load();
}

fImportAccount::~fImportAccount()
{
    delete ui;
}

void fImportAccount::Load_cbbThuMuc(){
    indexOld = ui->cbbThuMuc->currentIndex();
    QVariantList allFilesFromDatabase = CommonSQL::GetAllFilesFromDatabase(false,true);
    if(!allFilesFromDatabase.isEmpty() || allFilesFromDatabase.count()>0){
        for(const QVariant &item:allFilesFromDatabase){
            QVariantMap rowMap = item.toMap();
            ui->cbbThuMuc->addItem(rowMap["name"].toString(),rowMap["id"].toString());
        }
        if(indexOld ==-1){
            indexOld =0;
        }
        ui->cbbThuMuc->setCurrentIndex(indexOld);
    }
}

void fImportAccount::on_btnCancel_clicked()
{
    this->close();
}


void fImportAccount::on_btnAdd_clicked()
{
    try {
        QList<QString> lst = ui->txbAccount->toPlainText().split(QRegularExpression("\\r\\n|\\n"), Qt::SkipEmptyParts);
        lst = Common::RemoveEmptyItems(lst);
        if (lst.count() == 0)
        {
            MessageBoxHelper::Show(Language::GetValue("Vui lòng nhâ\u0323p thông tin ta\u0300i khoa\u0309n!"), 3);
            ui->txbAccount->setFocus();
            return;
        }
        if (ui->cbbThuMuc->currentData().isNull())
        {
            MessageBoxHelper::Show(Language::GetValue("Vui lòng cho\u0323n thư mu\u0323c!"), 3);
            return;
        }
        QString idFile = ui->cbbThuMuc->currentData().toString();
        QString text = ui->cbbDinhDangNhap->currentText();
        if(ui->cbbDinhDangNhap->currentIndex() == ui->cbbDinhDangNhap->count()-1){
            bool flag = false;
            for (int i = 0; i < lstCbbDinhDang.count(); i++)
            {
                if (lstCbbDinhDang[i]->currentIndex() > -1)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                MessageBoxHelper::Show("Vui lo\u0300ng cho\u0323n đi\u0323nh da\u0323ng ta\u0300i khoa\u0309n!", 3);
                return;
            }
            text ="";
            for(int j=0; j<lstCbbDinhDang.count();j++){
                text += lstCbbDinhDang[j]->currentText() + "|";
            }
            text=Utils::trimEnd(text,'|');
        }
        if(text==""){
            // MessageBoxHelper::Show("Vui lo\u0300ng cho\u0323n đi\u0323nh da\u0323ng ta\u0300i khoa\u0309n!", "Thông ba\u0301o", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            return;
        }
        if (lst.size() < 100) {
            // Equivalent to the discard variable in C#, simply evaluating lst.size()
            int count = lst.size();
            qDebug() << "Count:" << count;
        }
        ui->lblSuccess->setText("0");
        ui->lblError->setText("0");
        lstAccount = new QList<QString>;
        QList<QString> list = text.split('|').toList();
        QString uid, pass, token, cookie, mail, passMail, fa2, useragent, proxy, birthday, friends, dateCreated, mailKhoiPhuc;
        for(int k =0; k<lst.count();k++){
            QStringList array = lst[k].split('|');
            try {
                for (int l = 0; l < list.size(); l++) {
                    QString key = list[l];
                    QString value = array.value(l).trimmed();

                    if (key == "Uid") {
                        uid = value;
                    } else if (key == "Pass") {
                        pass = value;
                    } else if (key == "Token") {
                        token = value;
                    } else if (key == "Cookie") {
                        cookie = value;
                    } else if (key == "Email") {
                        mail = value;
                    } else if (key == "Pass Email") {
                        passMail = value;
                    } else if (key == "2FA") {
                        fa2 = value;
                    } else if (key == "Useragent") {
                        useragent = value;
                    } else if (key == "Proxy") {
                        proxy = value.isEmpty() ? "" : value + "*0";
                    } else if (key == "Ngày sinh" || key == "Birthday") {
                        birthday = value;
                    } else if (key == "Bạn bè" || key == "Friends") {
                        friends = value;
                    } else if (key == "Ngày tạo" || key == "Date Created") {
                        dateCreated = value;
                    } else if (key == "Mail khôi phục" || key == "Mail Recover") {
                        mailKhoiPhuc = value;
                    }   
                }
                uid = uid.isEmpty() ? "" : uid;
                pass = pass.isEmpty() ? "" : pass;
                token = token.isEmpty() ? "" : token;
                cookie = cookie.isEmpty() ? "" : cookie;
                mail = mail.isEmpty() ? "" : mail;
                passMail = passMail.isEmpty() ? "" : passMail;
                fa2 = fa2.isEmpty() ? "" : fa2;
                useragent = useragent.isEmpty() ? "" : useragent;
                proxy = proxy.isEmpty() ? "" : proxy;
                birthday = birthday.isEmpty() ? "" : birthday;
                friends = friends.isEmpty() ? "" : friends;
                dateCreated = dateCreated.isEmpty() ? "" : dateCreated;
                mailKhoiPhuc = mailKhoiPhuc.isEmpty() ? "" : mailKhoiPhuc;
                lstAccount->append(uid+"|"+pass+"|"+token+"|"+cookie+"|"+mail+"|"+passMail+"|"+fa2+"|"+useragent+"|"+proxy+"|"+birthday+"|"+friends+"|"+dateCreated+"|"+mailKhoiPhuc);
            } catch (...) {
            }
        }
        QList<QString> lstQuery;
        try {
            ui->btnAdd->setEnabled(false);
            ui->lblStatus->setText("Chuẩn bị thêm tài khoản...");
            for(const QString& text2 : *lstAccount){
                try {
                    if (text2.trimmed().isEmpty())
                        return;

                    QStringList array2 = text2.split('|');
                    QString uid = array2[0];
                    QString pass = array2[1];
                    QString token = array2[2];
                    QString cookie = array2[3];
                    QString mail = array2[4];
                    QString passMail = array2[5];
                    QString fa2 = array2[6];
                    QString useragent = array2[7];
                    QString proxy = array2[8];
                    QString birthday = array2[9];
                    QString friends = array2[10];
                    QString dateCreated = array2[11];
                    QString mailKhoiPhuc = array2[12];
                    QString name = "";
                    QString groups = "";
                    QString gender = "";
                    QString info = "unknow";
                    if(uid==""){
                        QRegularExpression re("c_user=(\\d+)");
                        QRegularExpressionMatch match = re.match(cookie);
                        if (match.hasMatch())
                        {
                            uid = match.captured(1);
                        }
                    }
                    lstQuery.append(CommonSQL::ConvertToSqlInsertAccount(uid, pass, token, cookie, mail, name, friends, groups, birthday, gender, info, fa2, idFile, passMail, useragent, proxy, dateCreated, mailKhoiPhuc));
                } catch (...) {
                }
            }
            ui->lblStatus->setText(Language::GetValue("Đang thêm tài khoản..."));
            if(lstQuery.size() >=0){
                lstQuery = CommonSQL::ConvertToSqlInsertAccount(lstQuery);
                for(int n=0;n<lstQuery.size();n++){
                    int count = Connector::getInstance().ExecuteNonQuery(lstQuery[n]);
                    if(count==-1){
                        ui->lblSuccess->setText(QString::number(ui->lblSuccess->text().toInt()+1));
                    }else{
                        ui->lblSuccess->setText(QString::number(ui->lblSuccess->text().toInt()+count));
                    }
                }
            }
            ui->lblStatus->setText(QString::number(ui->lblTotal->text().toInt() - ui->lblSuccess->text().toInt()));
            ui->btnAdd->setEnabled(true);
            ui->lblStatus->setText(Language::GetValue("Thêm tài khoản thành công!"));
            MessageBoxHelper::Show("Thêm tài khoản thành công!");
            isAddAccount=true;
            idFileAdded = idFile.toInt();
        } catch (...) {
        }
    } catch (const std::exception& ex2) {
        MessageBoxHelper::Show("Đa\u0303 co\u0301 lô\u0303i xa\u0309y ra, vui lo\u0300ng thư\u0309 la\u0323i sau!", 2);
    }
}


void fImportAccount::on_txbAccount_textChanged()
{
    try {
        QList<QString> lst = ui->txbAccount->toPlainText().split("\n", Qt::SkipEmptyParts);
        lst = Common::RemoveEmptyItems(lst);
        ui->lblTotal->setText(QString::number(lst.size()));
        QString lines = lst[0];
        QStringList clone = lines.split('|');
        QString dinhdang = "";
        bool passmail = true;
        bool checkm = true;
        for(QString cl : clone){
            if(cl.startsWith("100") || cl.startsWith("61")){
                dinhdang += "0|1|";
            }
            if (cl.startsWith("EAA"))
            {
                dinhdang += "2|";
            }
            if (cl.length() == 32)
            {
                dinhdang += "6|";
            }
            if (cl.contains("@")&& cl.contains("."))
            {
                dinhdang += "4|5|";
            }
            if (cl == "")
            {
                if (!checkm)
                {
                    dinhdang += "-1|";
                }
                if (checkm)
                {
                    if (dinhdang.contains("5"))
                    {
                        passmail = false;
                        checkm= false;
                    }
                }
            }
            if (cl.contains("xs=")|| cl.contains("user=") || cl.contains("xr="))
            {
                dinhdang += "3|";
            }
        }
        if (!passmail)
        {
            dinhdang=dinhdang.replace("5", "-1");
        }
        ui->frame_3->setVisible(true);
        if(ui->frame_3->isVisible()){
            ui->cbbDinhDangNhap->setCurrentIndex(ui->cbbDinhDangNhap->count()-1);
            ResetDinhDang();
            try {
                QStringList dd = dinhdang.split('|');
                int dds = dd.size()-1;
                for (int i = 0; i < lstCbbDinhDang.size(); i++) {
                    if(i<dds){
                        lstCbbDinhDang[i]->setCurrentIndex(dinhdang.split('|')[i].toInt());
                    }else{
                        lstCbbDinhDang[i]->setCurrentIndex(-1);
                    }

                }
            } catch (const std::exception &e)
            {
                qWarning() << "Standard exception caught:" << e.what();
            }
            catch (...)
            {
                qWarning() << "Unknown exception caught.";
            }
            QList<QComboBox*> list =
                {
                    ui->cbbDinhDang1, ui->cbbDinhDang2, ui->cbbDinhDang3, ui->cbbDinhDang4, ui->cbbDinhDang5, ui->cbbDinhDang6, ui->cbbDinhDang7, ui->cbbDinhDang8, ui->cbbDinhDang9, ui->cbbDinhDang10,
                    ui->cbbDinhDang11
                };
            for(int i =0;i<list.count();i++){
                format = format + list[i]->currentText() + "|";
            }
            format = Utils::trimEnd(format,'|');
            ui->button2->setVisible(false);
            ui->button3->setVisible(false);
        }
        QThread::sleep(1);

    } catch (...) {
    }
}

void fImportAccount::ResetDinhDang(){
    try {
        for (int i = 0; i < lstCbbDinhDang.size(); i++)
        {
            lstCbbDinhDang[i]->setCurrentIndex(-1);
        }
    } catch (...) {
    }
}

void fImportAccount::on_cbbDinhDangNhap_currentIndexChanged(int index)
{
    bool vi = ui->cbbDinhDangNhap->currentIndex() == ui->cbbDinhDangNhap->count() - 1;
    ui->frame_3->setVisible(vi);
    if(ui->frame_3->isVisible()){
        LoadDinhDang();
    }
}
void fImportAccount::LoadDinhDang(){
    try
    {
        QFile file("settings/format_paste.txt");
        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QString text = in.readAll();
                file.close();

                QStringList items = text.split('|');
                for (int i = 0; i < lstCbbDinhDang.size(); ++i)
                {
                    if (i < items.size())
                    {
                        bool ok;
                        int index = items[i].toInt(&ok);
                        if (ok)
                        {
                            lstCbbDinhDang[i]->setCurrentIndex(index);
                        }
                    }
                }
            }
        }
    }
    catch (...)
    {
        qDebug() << "An error occurred while loading the format.";
    }
}

void fImportAccount::on_pushButton_3_clicked()
{
    auto add = new fAddFile(this);
    add->exec();
    if (fAddFile::isAdd)
    {
        Load_cbbThuMuc();
        ui->cbbThuMuc->setCurrentIndex(ui->cbbThuMuc->count() - 1);
        isAddFile = true;
    }
}




void fImportAccount::on_cbbDinhDang1_currentIndexChanged(int index)
{
    if (false)
    {
        MessageBoxHelper::Show("Tu\u0300y cho\u0323n na\u0300y đa\u0303 tô\u0300n ta\u0323i, vui lo\u0300ng cho\u0323n tu\u0300y cho\u0323n kha\u0301c!", 3);
        ui->cbbDinhDang1->setCurrentIndex(-1);
    }
}


void fImportAccount::on_button2_clicked()
{
    ResetDinhDang();
}


void fImportAccount::on_button3_clicked()
{
    SaveDinhDang();
}
void fImportAccount::SaveDinhDang()
{
    try
    {
        QString text = "";
        for (int i = 0; i < lstCbbDinhDang.size(); i++)
        {
            text = text + QString::number(lstCbbDinhDang[i]->currentIndex()) + "|";
        }
        if (text.endsWith('|')) {
            text.chop(1);
        }
        QFile file("settings\\format_paste.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << text;
            file.close();
            qDebug() << "File written successfully.";
        }else{
            qDebug() << "Fail written file";
        }
    }
    catch(...)
    {
    }
}

void fImportAccount::on_addFileAccount_clicked()
{
    fImportAccountFormatInput* obj = new fImportAccountFormatInput();
    Common::ShowDialog(obj);
    QString text = obj->format.trimmed();
    if(text != "" && lstDinhDangNhap.contains(text)){
        lstDinhDangNhap.append(text);
        Utils::writeAllLines(fileDinhDangNhapPath, lstDinhDangNhap);
        LoadCbbDinhDangNhap();
        ui->cbbDinhDangNhap->setCurrentIndex(ui->cbbDinhDangNhap->count()-2);
    }
}
void fImportAccount::LoadCbbDinhDangNhap(){
    ui->cbbDinhDangNhap->clear();
    for (const QString &item : lstDinhDangNhap)
    {
        ui->cbbDinhDangNhap->addItem(item);
    }
    ui->cbbDinhDangNhap->addItem("Other...");
}

void fImportAccount::on_metroButton1_clicked()
{
    int selectedIndex = ui->cbbDinhDangNhap->currentIndex();
    if (selectedIndex == -1 || selectedIndex == ui->cbbDinhDangNhap->count() - 1)
    {
        MessageBoxHelper::Show("Không thể xóa định dạng này!", 3);
        return;
    }
    QString text = ui->cbbDinhDangNhap->currentText();
    if (MessageBoxHelper::ShowYesNo(QString::fromUtf8("Ba\u0323n co\u0301 muô\u0301n xóa định dạng \"%1\"?").arg(text)))
    {
        lstDinhDangNhap.removeAll(text);
        Utils::writeAllLines(fileDinhDangNhapPath, lstDinhDangNhap);
        LoadCbbDinhDangNhap();
        ui->cbbDinhDangNhap->setCurrentIndex(((selectedIndex != 0 || ui->cbbDinhDangNhap->count() <= 0) ? (selectedIndex - 1) : 0));
    }
}
void fImportAccount::fImportAccount_Load(){
    Common::CreateFileW(fileDinhDangNhapPath);
    lstDinhDangNhap= QList<QString>(Utils::readAllText(fileDinhDangNhapPath).split(QRegularExpression("\r\n|\n"), Qt::SkipEmptyParts));
    if(lstDinhDangNhap.size() ==0){
        lstDinhDangNhap = {
            "Uid|Pass|2FA",
            "Uid|Pass|2FA|Email|Pass Email|Cookie|Token",
            "Uid|Pass|2FA|Email|Cookie|Token",
            "Cookie",
            "Uid|Pass",
            "Uid|Pass|Token|Cookie",
            "Uid|Pass|Token|Cookie|Email|Pass Email",
            "Uid|Pass|Token|Cookie|Email|Pass Email|2FA"
        };
    }
    LoadCbbDinhDangNhap();
    ui->cbbDinhDangNhap->setCurrentIndex(0);
}

