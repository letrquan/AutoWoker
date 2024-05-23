#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSettings>
#include <QHostInfo>
#include <QCryptographicHash>
#include <QMenu>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QWidgetAction>
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
private:
    bool isStop;
    Ui::MainWindow *ui;
    QList<QThread*> lstThread;
    QList<QString> lstMailDomainAw;
    QMenu menu;
    void ChangeLanguage();
    void DisableSort();
    void CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282);
    void CheckDangCheckpoint(int row);
    void CheckMyWall(int row, QString tokenTg);
    void CheckMyToken(int row);
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
private slots:
    void showContextMenu(const QPoint &pos) {
        // Create the context menu
        QMenu contextMenu(this);

        // Create main actions with icons
        QAction *actionSelect = new QAction(QIcon(":/icons/select.png"), "Chọn", this);
        QAction *actionDeselect = new QAction("Bỏ chọn tất cả", this);
        QAction *actionHideList = new QAction("Ẩn khỏi danh sách", this);
        QAction *actionInputProxy = new QAction("Nhập Proxy", this);
        QAction *actionInputUserAgent = new QAction("Nhập Useragent", this);
        QAction *actionCopy = new QAction("Copy", this);
        QAction *actionOpenProgram = new QAction("Mở trình duyệt", this);
        QAction *actionDeleteAccount = new QAction("Xóa tài khoản", this);

        // Connect actions to slots
        // connect(actionSelect, &QAction::triggered, this, &MainWindow::onActionSelect);
        // connect(actionDeselect, &QAction::triggered, this, &MainWindow::onActionDeselect);
        // connect(actionHideList, &QAction::triggered, this, &MainWindow::onActionHideList);
        // connect(actionInputProxy, &QAction::triggered, this, &MainWindow::onActionInputProxy);
        // connect(actionInputUserAgent, &QAction::triggered, this, &MainWindow::onActionInputUserAgent);
        // connect(actionCopy, &QAction::triggered, this, &MainWindow::onActionCopy);
        // connect(actionOpenProgram, &QAction::triggered, this, &MainWindow::onActionOpenProgram);
        // connect(actionDeleteAccount, &QAction::triggered, this, &MainWindow::onActionDeleteAccount);

        // Create a submenu for "Chọn"
        QMenu *subMenuSelect = new QMenu("Chọn", this);

        QAction *subActionAll = new QAction("Tất cả", this);
        QAction *subActionBlackList = new QAction("Bôi đen", this);
        QAction *subActionCondition = new QAction("Tình trạng", this);
        QAction *subActionStatus = new QAction("Trạng thái", this);
        QAction *subActionSelectByUID = new QAction("Chọn danh sách theo UID", this);

        // connect(subActionAll, &QAction::triggered, this, &MainWindow::onSubActionAll);
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

        // Add the submenu to the main action
        actionSelect->setMenu(subMenuSelect);

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
        contextMenu.addSeparator();
        contextMenu.addAction(widgetActionNote);

        // Show the context menu at the cursor position
        contextMenu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
    }
    void on_btnLoadAcc_clicked();
    void on_pushButton_4_clicked();
    void on_button9_clicked();
    void on_cbbThuMuc_currentIndexChanged(int index);
    void on_cbbTinhTrang_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
