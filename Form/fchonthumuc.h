#ifndef FCHONTHUMUC_H
#define FCHONTHUMUC_H

#include <QDialog>

namespace Ui {
class fChonThuMuc;
}

class fChonThuMuc : public QDialog
{
    Q_OBJECT

public:
    explicit fChonThuMuc(bool isFromBin=false,QWidget *parent = nullptr);
    ~fChonThuMuc();
    static QList<QString> lstChooseIdFiles;
    static QList<QString> lstChooseIdFilesFromBin;
    static bool isAdd;
private slots:
    void on_button5_clicked();

    void on_btnAdd_clicked();

    void on_btnCancel_clicked();

    void on_dtgvAcc_cellChanged(int row, int column);

    void on_dtgvAcc_cellDoubleClicked(int row, int column);

    void on_dtgvAcc_cellClicked(int row, int column);

    void on_checkBox1_clicked(bool checked);

    void on_button4_clicked();

private:
    Ui::fChonThuMuc *ui;
    bool isFromBin;
    void fChonThuMuc_Load();
    void LoadListFiles(const QList<QString> &lstIdFile);
    int CountSelectRow();
    void UpdateSelectCountRecord();
    void UpdateTotalCountRecord();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // FCHONTHUMUC_H
