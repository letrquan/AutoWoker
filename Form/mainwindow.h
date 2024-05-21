#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QHostInfo>
#include <QCryptographicHash>
#include <QMenu>
#include <QStandardItemModel>
#include <QSqlQuery>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString token;
    QString name;
    QString phone;
    QString maxdevice;
public:
    explicit MainWindow(QString tokemem,QString namemem,QString phoneMem, QString maxDeviceMem,QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow remote;
    static void xoaProxy();
    static QString getIPServer(const QString& address);
    static QString md5Encode(const QString &input);
    static QString Getdocs(QString uri);
    static QString checkUpdate(QString namesoft);
    QString GetInfoAccount(int indexRow);
private:
    Ui::MainWindow *ui;
    QList<QThread*> lstThread;
    QList<QString> lstMailDomainAw;
    QMenu menu;
    void ChangeLanguage();
    bool isExcute_CbbThuMuc_SelectedIndexChanged = true;
    bool isExcute_CbbTinhTrang_SelectedIndexChanged = true;
    int indexCbbTinhTrangOld = -1;
    void LoadcbbSearch();
    void LoadCbbThuMuc(int selectedIndex = -1);
    void LoadCbbTinhTrang(const QList<QString>& lstIdFile = QList<QString>());
    void OnLoaded();
    int indexCbbThuMucOld = -1;
    QList<QString> GetIdFile();
    void LoadAccountFromFile(QList<QString> lstIdFile =QList<QString>(), QString info = "");
    void LoadDtgvAccFromDatatable(QVariantList *tableAccount);
    void CountCheckedAccount(int count = -1);
    void CountTotalAccount();
    void SetRowColor(int indexRow = -1);
    void LoadConfigManHinh();
    void setColumnVisibility(const QString& headerLabel, bool isVisible);
    void AddUI();
protected:
    void changeEvent(QEvent *event) override;
private slots:
    void on_btnLoadAcc_clicked();
    void on_pushButton_4_clicked();
    void on_button9_clicked();
    void on_cbbThuMuc_currentIndexChanged(int index);
    void on_cbbTinhTrang_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
