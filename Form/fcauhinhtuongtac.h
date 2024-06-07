#ifndef FCAUHINHTUONGTAC_H
#define FCAUHINHTUONGTAC_H

#include <QDialog>

namespace Ui {
class fCauhinhtuongtac;
}

class fCauhinhtuongtac : public QDialog
{
    Q_OBJECT

public:
    explicit fCauhinhtuongtac(QWidget *parent = nullptr);
    ~fCauhinhtuongtac();


private slots:
    void on_ckbCapNhatThongTin_stateChanged(int arg1);

    void on_checkBox_9_clicked();

    void on_ckbGioiHanThoiGianChayTaiKhoan_stateChanged(int arg1);

    void on_ckbGioiHanThoiGianChayKichBan_stateChanged(int arg1);

    void on_ckbGetToken_stateChanged(int arg1);

    void on_ckbGroup_clicked();

    void on_btnAdd_clicked();

    void on_btnQuanlyKichBan_clicked();

    void on_btnCancel_clicked();

private:
    QString string_0 ="";
    Ui::fCauhinhtuongtac *ui;
    void fCauhinhtuongtac_Load();
    void LoadcbbKichBan();
    void LoadSettings();
    void CheckedChangedFull();
};

#endif // FCAUHINHTUONGTAC_H
