#ifndef FCAUHINHHIENTHI_H
#define FCAUHINHHIENTHI_H

#include <QDialog>

namespace Ui {
class fCauHinhHienThi;
}

class fCauHinhHienThi : public QDialog
{
    Q_OBJECT

public:
    explicit fCauHinhHienThi(QWidget *parent = nullptr);
    ~fCauHinhHienThi();

private slots:
    void on_btnLuu_clicked();

    void on_btnDong_clicked();

private:
    Ui::fCauHinhHienThi *ui;
    void fCauHinhHienThi_Load();
};

#endif // FCAUHINHHIENTHI_H
