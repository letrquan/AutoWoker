#ifndef AUTOCONTROL_H
#define AUTOCONTROL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPoint>
#include <QRect>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include <QWindow>
#include <QGuiApplication>
#include <QScreen>
#include <QCursor>
#include <minwindef.h>

class AutoControl : public QObject {
    Q_OBJECT

public:
    explicit AutoControl(QObject *parent = nullptr);

    static HWND findWindow(const QString &className, const QString &windowName = QString());
    static bool isWindowVisible(HWND hwnd);
    static QRect getWindowRect(HWND hwnd);
    static QPoint getGlobalPoint(HWND hwnd, const QPoint &point = QPoint(0, 0));
    static void mouseClick(const QPoint &point, Qt::MouseButton button = Qt::LeftButton);
    static void sendText(HWND hwnd, const QString &text);

private:
    static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
    static QString getWindowText(HWND hwnd);
    static QString getClassName(HWND hwnd);
    static LPARAM MakeLParamFromXY(int x, int y);
};

#endif // AUTOCONTROL_H
