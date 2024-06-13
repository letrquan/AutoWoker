#include "autocontrol.h"
#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPoint>
#include <QRect>
#include <QCoreApplication>
#include <windows.h>
AutoControl::AutoControl(QObject *parent) : QObject(parent) {}

HWND AutoControl::findWindow(const QString &className, const QString &windowName) {
    return FindWindow(className.toStdWString().c_str(), windowName.toStdWString().c_str());
}

bool AutoControl::isWindowVisible(HWND hwnd) {
    return IsWindowVisible(hwnd);
}

QRect AutoControl::getWindowRect(HWND hwnd) {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        return QRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
    }
    return QRect();
}

QPoint AutoControl::getGlobalPoint(HWND hwnd, const QPoint &point) {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        return QPoint(rect.left + point.x(), rect.top + point.y());
    }
    return QPoint();
}

void AutoControl::mouseClick(const QPoint &point, Qt::MouseButton button) {
    QCursor::setPos(point);
    INPUT inputs[2] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = (button == Qt::LeftButton) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = (button == Qt::LeftButton) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(2, inputs, sizeof(INPUT));
}

void AutoControl::sendText(HWND hwnd, const QString &text) {
    for (auto c : text.toStdWString()) {
        PostMessage(hwnd, WM_CHAR, c, 0);
    }
}

BOOL CALLBACK AutoControl::EnumChildProc(HWND hwnd, LPARAM lParam) {
    QList<HWND> *handles = reinterpret_cast<QList<HWND> *>(lParam);
    handles->append(hwnd);
    return TRUE;
}

QString AutoControl::getWindowText(HWND hwnd) {
    wchar_t buffer[256];
    GetWindowText(hwnd, buffer, sizeof(buffer));
    return QString::fromWCharArray(buffer);
}

QString AutoControl::getClassName(HWND hwnd) {
    wchar_t buffer[256];
    GetClassName(hwnd, buffer, sizeof(buffer));
    return QString::fromWCharArray(buffer);
}

LPARAM AutoControl::MakeLParamFromXY(int x, int y) {
    return MAKELPARAM(x, y);
}
