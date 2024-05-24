#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include "qmutex.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSettings>
#include <QHostInfo>
#include <QCryptographicHash>
#include <QMenu>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QWidgetAction>
#include <QKeyEvent>
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
    void SetStatusAccount(int indexRow, QString value, int timeWait = -1);
    QString GetCellAccount(int indexRow, QString column);
    void SetInfoAccount(int indexRow, QString value);
    void SetCellAccount(int indexRow, QString column, QVariant value, bool isAllowEmptyValue = true);
private:
    bool isStop;
    Ui::MainWindow *ui;
    QList<QThread*> lstThread;
    QList<QString> lstMailDomainAw;
    QMenu menu;
    QMutex mutex;
    void ChangeLanguage();
    void DisableSort();
    void CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282);
    void CheckDangCheckpoint(int row);
    void CheckNameVN(int row);
    void CheckMyWall(int row, QString tokenTg);
    void CheckMyToken(int row);
    void CheckInfoUid(int row, bool useProxy);
    bool CheckIsUidFacebook(QString uid);
    void CheckAccountMail(int row);
    void CheckMyCookie(int row);
    void cControl(QString dt);
    void EnableSort();
    void KiemTraTaiKhoan(int type, bool useProxy = false);
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
    void SetRowColor(int indexRow, int typeColor);
    void LoadConfigManHinh();
    void setColumnVisibility(const QString& headerLabel, bool isVisible);
    void AddUI();
protected:
    void changeEvent(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == ui->tableWidget && event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
                QModelIndexList selectedRows = selectionModel->selectedRows();
                for (const QModelIndex &index : selectedRows) {
                    int row = index.row();
                    auto *item = ui->tableWidget->item(row, 0);
                    if (item->checkState() == Qt::Checked) {
                        item->setCheckState(Qt::Unchecked);
                    }else{
                        item->setCheckState(Qt::Checked);
                    }
                }
                return true;
            }
        }
        return QMainWindow::eventFilter(obj, event);
    }
private slots:
    void showContextMenu(const QPoint &pos);
    void on_btnLoadAcc_clicked();
    void on_pushButton_4_clicked();
    void on_button9_clicked();
    void onSubActionAll();
    void onActionDeselect();
    void checkWall();
    void on_cbbThuMuc_currentIndexChanged(int index);
    void on_cbbTinhTrang_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
