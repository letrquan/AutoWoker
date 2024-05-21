#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string account;
std::string password;

void MainWindow::on_pushButton_clicked()
{
    account = ui->lineEdit_Account->text().toStdString();
    password = ui->lineEdit_Password->text().toStdString();
}

