#ifndef FVIEWCHROME_H
#define FVIEWCHROME_H

#include <QWidget>

namespace Ui {
class fViewChrome;
}

class fViewChrome : public QWidget
{
    Q_OBJECT

public:
    explicit fViewChrome(QWidget *parent = nullptr);
    ~fViewChrome();

private:
    Ui::fViewChrome *ui;
};

#endif // FVIEWCHROME_H
