#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QFile>
#include <QRegularExpression>
#include <QFileInfo>
#include <QEvent>
#include <QKeyEvent>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void saveLogin();
    void getLogin();
private slots:
    void on_LoginButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::LoginWindow *ui;
    void Loadx();
    void loadSettings();
// protected:
//     bool eventFilter(QObject *obj, QEvent *event) override {
//         if (event->type() == QEvent::KeyPress) {
//             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//             if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
//                 // Simulate the button click
//                 on_LoginButton_clicked();
//                 return true;  // Indicate that the event was handled
//             }
//         }
//         // Pass the event on to the parent class
//         return QWidget::eventFilter(obj, event);
//     }
};

#endif // LOGINWINDOW_H
