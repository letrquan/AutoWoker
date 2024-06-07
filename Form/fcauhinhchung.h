#ifndef FCAUHINHCHUNG_H
#define FCAUHINHCHUNG_H
#include "../MCommon/json_settings.h"
#include <QDialog>

namespace Ui {
class fCauHinhChung;
}

class fCauHinhChung : public QDialog
{
    Q_OBJECT

public:
    explicit fCauHinhChung(JSON_Settings &data,QWidget *parent = nullptr);
    ~fCauHinhChung();

private slots:
    void on_btnCancel_clicked();

private:
    Ui::fCauHinhChung *ui;
    JSON_Settings settings;
    void LoadCbbTocDoGoVanBan();
    void LoadCbbChangeIP();
    void fCauhinhChung_Load();
    void LoadCbbProxy();
};

#endif // FCAUHINHCHUNG_H
