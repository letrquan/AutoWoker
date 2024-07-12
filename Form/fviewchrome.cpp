#include "fviewchrome.h"

#include "ui_fviewchrome.h"

fViewChrome::fViewChrome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fViewChrome)
{
    ui->setupUi(this);
    setMinimumSize(800, 600);
}

fViewChrome::~fViewChrome()
{
    delete ui;
}



void fViewChrome::addChromeIntoPanel(HWND mainWindowHandle, int indexDevice, int width, int height, int x, int y)
{
    QWidget *containerWidget = ui->scrollAreaWidgetContents->findChild<QWidget*>(QString("dv%1").arg(indexDevice));
    if (containerWidget) {
        // Set the Chrome window as a child of our container
        SetParent(mainWindowHandle, (HWND)containerWidget->winId());

        // Remove window styles from the Chrome window
        LONG style = GetWindowLong(mainWindowHandle, GWL_STYLE);
        style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        SetWindowLong(mainWindowHandle, GWL_STYLE, style);

        // Move and resize the Chrome window
        MoveWindow(mainWindowHandle, x, y, width, height, TRUE);

        // Show the Chrome window
        ShowWindow(mainWindowHandle, SW_SHOW);
    }
    updateTitle();
}

void fViewChrome::removePanelDevice(int indexDevice)
{
    QWidget *containerWidget = ui->scrollAreaWidgetContents->findChild<QWidget*>(QString("dv%1").arg(indexDevice));
    if (containerWidget) {
        // Enumerate child windows and set their parent back to desktop
        EnumChildWindows((HWND)containerWidget->winId(), EnumChildProc, 0);
        delete containerWidget;
    }
    updateTitle();
}

BOOL CALLBACK fViewChrome::EnumChildProc(HWND hwnd, LPARAM lParam)
{
    SetParent(hwnd, GetDesktopWindow());
    return TRUE;
}

void fViewChrome::addPanelDevice(int indexDevice, int width, int height)
{
    QWidget *containerWidget = new QWidget(ui->scrollAreaWidgetContents);
    containerWidget->setObjectName(QString("dv%1").arg(indexDevice));
    containerWidget->setFixedSize(width, height);
    containerWidget->setStyleSheet("background-color: white; border: 1px solid black;");

    ui->scrollLayout->addWidget(containerWidget);

    // Wait for the widget to be added
    for (int i = 0; i < 10; ++i) {
        if (ui->scrollAreaWidgetContents->findChild<QWidget*>(QString("dv%1").arg(indexDevice))) {
            break;
        }
        QThread::msleep(1000);
    }
}

void fViewChrome::updateTitle()
{
    int countChrome = ui->scrollLayout->count();
    setWindowTitle(QString("Qt Chrome Viewer (%1)").arg(countChrome));
}
