/****************************************************************************
** Meta object code from reading C++ file 'StatusChromeAccount.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../maxcare/Enum/StatusChromeAccount.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StatusChromeAccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSStatusChromeAccountENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSStatusChromeAccountENDCLASS = QtMocHelpers::stringData(
    "StatusChromeAccount",
    "Status",
    "Empty",
    "ChromeClosed",
    "LoginWithUserPass",
    "LoginWithSelectAccount",
    "Checkpoint",
    "Logined",
    "NoInternet",
    "Blocked",
    "Noveri"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStatusChromeAccountENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    9,   19,

 // enum data: key, value
       2, uint(StatusChromeAccount::Empty),
       3, uint(StatusChromeAccount::ChromeClosed),
       4, uint(StatusChromeAccount::LoginWithUserPass),
       5, uint(StatusChromeAccount::LoginWithSelectAccount),
       6, uint(StatusChromeAccount::Checkpoint),
       7, uint(StatusChromeAccount::Logined),
       8, uint(StatusChromeAccount::NoInternet),
       9, uint(StatusChromeAccount::Blocked),
      10, uint(StatusChromeAccount::Noveri),

       0        // eod
};

Q_CONSTINIT const QMetaObject StatusChromeAccount::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSStatusChromeAccountENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStatusChromeAccountENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStatusChromeAccountENDCLASS_t,
        // enum 'Status'
        QtPrivate::TypeAndForceComplete<StatusChromeAccount::Status, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StatusChromeAccount, std::true_type>
    >,
    nullptr
} };

void StatusChromeAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *StatusChromeAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatusChromeAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStatusChromeAccountENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StatusChromeAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
