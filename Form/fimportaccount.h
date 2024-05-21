#ifndef FIMPORTACCOUNT_H
#define FIMPORTACCOUNT_H

#include "qcombobox.h"
#include <QWidget>
#include "../Utils/Utils.h"
namespace Ui {
class fImportAccount;
}

class fImportAccount : public QWidget
{
    Q_OBJECT

public:
    explicit fImportAccount(QString idFile,QWidget *parent = nullptr);
    ~fImportAccount();
    bool isAddAccount;
    int idFileAdded = -1;
    bool isAddFile;
    QString format="";
private slots:
    void on_btnCancel_clicked();
    void on_btnAdd_clicked();
    void on_txbAccount_textChanged();
    void on_cbbDinhDangNhap_currentIndexChanged(int index);
    void on_pushButton_3_clicked();
    void on_cbbDinhDang1_currentIndexChanged(int index);
    void on_button2_clicked();
    void on_button3_clicked();
    void on_addFileAccount_clicked();
    void on_metroButton1_clicked();

private:
    Ui::fImportAccount *ui;
    int indexOld;
    QList<QString>* lstAccount;
    QList<QComboBox*> lstCbbDinhDang;
    QList<QThread*> lstThread;
    QList<QString> lstDinhDangNhap = *new QList<QString>();
    void Load_cbbThuMuc();
    void ResetDinhDang();
    void LoadDinhDang();
    void SaveDinhDang();
    QString fileDinhDangNhapPath = Utils::getPathToCurrentFolder() + "\\settings\\inputformat.txt";
    void LoadCbbDinhDangNhap();
    void fImportAccount_Load();
};

#endif // FIMPORTACCOUNT_H
