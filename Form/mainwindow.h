#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCheckBox>
#include "qfuturewatcher.h"
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
#include <QThreadPool>
#include "../Table/customtablemodel.h"
#include "../MCommon/json_settings.h"
#include "../MCommon/ProxyTool.h"
#include "../MCommon/tinsoftproxy.h"
#include "../MCommon/xproxyproxy.h"
#include "../MCommon/tmproxy.h"
#include "../MCommon/proxyv6net.h"
#include "../MCommon/shoplike.h"
#include "../MCommon/minproxy.h"
#include "../MCommon/obcdcom.h"
#include "../MCommon/chrome.h"
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
    QString GetCellAccount(int indexRow, QString column);
    int CountChooseRowInDatagridview();
    QList<QString> GetListKeyTinsoft();
    QString GetStatusAccount(int indexRow);
    QString TurnOn2FA(QString password, QString token, QString proxy, int typeProxy);
private:
    void ExcuteUnlock282(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy);
    void GetProxy(int indexRow, bool &isStop, QString &proxy, int &typeProxy, QString &statusProxy, QString &ip, TinsoftProxy* tinsoft, XproxyProxy* xproxy, TMProxy* tmproxy, ProxyV6Net* proxyWeb, ShopLike* shopLike, MinProxy* minProxy, ObcProxy* obcProxy);
    void ExcuteOneThread(int indexRow, int indexPos, QString idKichBan, JSON_Settings settings);
    void ReadResultSpam();
    QMap<QString,QStringList> dicUidNhom;
    QMap<QString,QStringList> dicUidNhom2;
    QMap<QString,QStringList> dicUidCaNhan;
    QMap<QString,QStringList> dicUidCaNhan2;
    QMap<QString,QStringList> dicUidBaivietProfile;
    QString LoginFacebook(Chrome *chrome, int typeLogin, const QString &typeWeb, const QString &uid, const QString &email, QString &pass, QString &fa2, const QString &cookie, int tocDoGoVanBan, bool isDontSaveBrowser, int type2Fa, bool isLoginVia = false);
    QMap<QString,QStringList> dicUidSpamBaiViet;
    QMap<QString,QStringList> dicUidSpamBaiVietv2;
    QMap<QString,QStringList> dicSpamBaiVietIdPostOld;
    QMap<QString,QStringList> dicCommentSpamBaiViet;
    QMap<QString,QStringList> dicCommentSpamBaiVietv2;
    QMap<QString,QStringList> dicUidTinNhanProfile;
    QMap<QString,QStringList> dicKetBanUidNew;
    QMap<QString,QStringList> dicBuffLikeComment_Comment;
    QMap<QString,QStringList> dicBuffLikeComment_CommentGoc;
    QMap<QString,QStringList> dicDangStatus_NoiDung;
    QMap<QString,QStringList> dicDangStatus_NoiDungGoc;
    QMap<QString,QStringList> dicDangStatusV2_NoiDung;
    QMap<QString,QStringList> dicDangStatusV2_NoiDungGoc;
    QMap<QString,QStringList> dicDangBai_NoiDung;
    QMap<QString,QStringList> dicDangBai_NoiDungGoc;

    QMap<QString,QStringList> dicUidPhanHoiComment;

    QMap<QString,QStringList> dicIdBaiViet;

    QMap<QString,QStringList> dicIdBaiVietClone;

    QMap<QString,QStringList> dicIdPageBuff;

    QMap<QString,QStringList> dicHDShareBaiTut_txtLinkChiaSe;

    QMap<QString,QStringList> dicHDLinkToInstagram_txtBio;

    QMap<QString,QStringList> dicHDLinkToInstagram_txtBioGoc;

    QMap<QString,QStringList> dicHDReviewPage_txtUid;

    QMap<QString,QStringList> dic_HDNhanTinBanBe_txtTinNhan;

    QMap<QString,QStringList> dic_HDNhanTinBanBe_txtTinNhan_Goc;

    QMap<QString,QStringList> dic_HDDangBai_lstNhomTuNhap;

    QMap<QString,QStringList> dic_HDDangBai_txtIdPost;

    QMap<QString,QStringList> dic_HDTuongTacLivestream_txtComment;

    QMap<QString,QStringList> dic_HDAddMail_lstHotmail;

    QMap<QString,QStringList> dic_HDUpAvatar_lstImage;

    QMap<QString,QStringList> dic_HDUpCover_lstImage;

    QMap<QString,QStringList> dicImagePathOld;

    QMap<QString,QStringList> dicImagePathToRun;

    QMap<QString,QStringList> dicCommentPathOld;

    QMap<QString,QStringList> dicCommentPathToRun;
    QMap<QString,QMap<QString,int>> dic_BuffLikeComment_LimitPerLink;
    QMap<QString,QStringList> dic_HDPhanHoiBinhLuan_Comment;

    QMap<QString,QStringList> GetDictionaryIntoHanhDong(QString idKichBan, QString tenTuongTac, QString field = "txtUid");
    void RandomThuTuTaiKhoan(int soLuot = 1);
    void DeleteCacheProfile(int row);
    int checkDelayChrome;
    bool isCountCheckAccountWhenChayTuongTac;
    QMap<QString,QStringList> dic_GroupPosted;
    QMap<QString,QStringList> dic_GroupShared;
    void OpenFormViewChrome();
    QList<ObcDcom*> listObcDcom;
    QList<ProxyTool*> lstProxyTool;
    bool isStop;
    Ui::MainWindow *ui;
    QList<QFuture<void>*> lstThread;
    QList<QString> lstMailDomainAw;
    QMenu menu;
    QMutex mutex;
    CustomTableModel *cusModel;
    QMap<QString,QString> *statusSQL;
    QMap<QString,QString> *infoSQL;
    void ChangeLanguage();
    bool IsChooseRow();
    void DisableSort();
    void Execute(const JSON_Settings &settings = JSON_Settings());
    void CheckDangCheckPoint(int indexRow, QString statusProxy, QString cookie, QString proxy, int typeProxy,  bool &isCheckpoint282);
    void CheckDangCheckpoint(int row);
    void CheckNameVN(int row);
    void CheckMyWall(int row, QString tokenTg);
    void CheckMyToken(int row);
    QList<ProxyTool *> GetListProxy(int maxThread);
    void CheckInfoUid(int row, bool useProxy);
    bool CheckIsUidFacebook(QString uid);
    void CheckAccountMail(int row);
    void CheckMyCookie(int row);
    void cControl(QString dt);
    void EnableSort();
    void checkAccounts(const std::function<void(int)>& task);
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
    void LoadConfigManHinh();
    void setColumnVisibility(const QString& headerLabel, bool isVisible);
    void AddUI();
    int QuenMatKhau(QString mail, QString proxy, int typeProxy);
    void ScreenCaptureError(Chrome* chrome, const QString& uid, int type);
protected:
    void changeEvent(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == ui->tableView && event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
                QModelIndexList selectedRows = selectionModel->selectedRows();
                for (const QModelIndex &index : selectedRows) {
                    int row = index.row();
                    auto i =ui->tableView->model()->index(row,0);
                    if (i.data(Qt::CheckStateRole).toBool()) {
                        ui->tableView->model()->setData(i,Qt::Unchecked,Qt::CheckStateRole);
                    }else{
                        ui->tableView->model()->setData(i,Qt::Checked,Qt::CheckStateRole);
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
    void onActionCopy();
    void checkCookie();
    void SetInfoAccount(int indexRow, QString value);
    void SetCellAccount(int indexRow, QString column, QVariant value, bool isAllowEmptyValue = true);
    void SetStatusAccount(int indexRow, QString value, int timeWait = -1);
    void SetRowColor(int indexRow = -1);
    void SetRowColor(int indexRow, int typeColor);
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_btnInteract_clicked();
    bool CheckDangCheckpointNew(Chrome *chrome, int indexRow, QString statusAction, bool isUnlock956 = false, int typeWebUnlock956 = 0);
signals:
    void updateStatusAccount(int row, QString status, int timeWait = -1);
    void updateInfoAccount(int row, QString info);
    void updateRowColor2(int indexRow, int typeColor);
    void updateRowColor(int indexRow = -1);
    void updateCellAccount(int indexRow, QString column, QVariant value, bool isAllowEmptyValue = true);
};

#endif // MAINWINDOW_H
