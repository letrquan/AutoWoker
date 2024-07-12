#ifndef FVIEWCHROME_H
#define FVIEWCHROME_H
#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QWindow>
#include <QDebug>
#include <QThread>

#include <Windows.h>
namespace Ui {
class fViewChrome;
}

class fViewChrome : public QMainWindow
{
    Q_OBJECT

public:
    fViewChrome(QWidget *parent = nullptr);
    ~fViewChrome();
    void addChromeIntoPanel(HWND mainWindowHandle, int indexDevice, int width, int height, int x = -10, int y = -30);
    void removePanelDevice(int indexDevice);
    void addPanelDevice(int indexDevice, int width, int height);

private:
    Ui::fViewChrome *ui;
    void updateTitle();
    static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
};

#endif // FVIEWCHROME_H
