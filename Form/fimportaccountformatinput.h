#ifndef FIMPORTACCOUNTFORMATINPUT_H
#define FIMPORTACCOUNTFORMATINPUT_H

#include <QDialog>

namespace Ui {
class fImportAccountFormatInput;
}

class fImportAccountFormatInput : public QDialog
{
    Q_OBJECT

public:
    explicit fImportAccountFormatInput(QWidget *parent = nullptr);
    ~fImportAccountFormatInput();
    QString format="";

private slots:
    void on_btnAdd_clicked();

    void on_btnCancel_clicked();

private:
    Ui::fImportAccountFormatInput *ui;
};

#endif // FIMPORTACCOUNTFORMATINPUT_H
