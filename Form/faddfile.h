#ifndef FADDFILE_H
#define FADDFILE_H

#include <QDialog>

namespace Ui {
class fAddFile;
}

class fAddFile : public QDialog
{
    Q_OBJECT

public:
    explicit fAddFile(QWidget *parent = nullptr);
    ~fAddFile();
    static bool isAdd;
private slots:
    void on_btnAdd_clicked();

    void on_btnCancel_clicked();

private:
    Ui::fAddFile *ui;
};

#endif // FADDFILE_H
