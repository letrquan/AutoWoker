#include "fviewchrome.h"
#include "ui_fviewchrome.h"

fViewChrome::fViewChrome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fViewChrome)
{
    ui->setupUi(this);
}

fViewChrome::~fViewChrome()
{
    delete ui;
}
