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


private:
    Ui::fCauhinhtuongtac *ui;
    void LoadcbbKichBan();
};

#endif // FCAUHINHTUONGTAC_H
