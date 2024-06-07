#ifndef FDANHSACHKICHBAN_OLD_H
#define FDANHSACHKICHBAN_OLD_H

#include <QDialog>

namespace Ui {
class fDanhSachKichBan_Old;
}

class fDanhSachKichBan_Old : public QDialog
{
    Q_OBJECT

public:
    explicit fDanhSachKichBan_Old(QString kichBan,QWidget *parent = nullptr);
    ~fDanhSachKichBan_Old();
private slots:
    void showContextMenuHanhDong(const QPoint &pos);
    void showContextMenuKichBan(const QPoint &pos);
    void on_dtgvKichBan_cellClicked(int row, int column);

    void on_button5_clicked();

    void on_button4_clicked();

private:
    Ui::fDanhSachKichBan_Old *ui;
    QString kichBan ="";
    void LoadKichBan(QString kichBan = "");
    void LoadHanhDong();
};

#endif // FDANHSACHKICHBAN_OLD_H
