/****************************************************************************
** Meta object code from reading C++ file 'fcauhinhtuongtac.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Form/fcauhinhtuongtac.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fcauhinhtuongtac.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSfCauhinhtuongtacENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSfCauhinhtuongtacENDCLASS = QtMocHelpers::stringData(
    "fCauhinhtuongtac",
    "on_ckbCapNhatThongTin_stateChanged",
    "",
    "arg1",
    "on_checkBox_9_clicked",
    "on_ckbGioiHanThoiGianChayTaiKhoan_stateChanged",
    "on_ckbGioiHanThoiGianChayKichBan_stateChanged",
    "on_ckbGetToken_stateChanged",
    "on_ckbGroup_clicked",
    "on_btnAdd_clicked",
    "on_btnQuanlyKichBan_clicked",
    "on_btnCancel_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSfCauhinhtuongtacENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x08,    1 /* Private */,
       4,    0,   71,    2, 0x08,    3 /* Private */,
       5,    1,   72,    2, 0x08,    4 /* Private */,
       6,    1,   75,    2, 0x08,    6 /* Private */,
       7,    1,   78,    2, 0x08,    8 /* Private */,
       8,    0,   81,    2, 0x08,   10 /* Private */,
       9,    0,   82,    2, 0x08,   11 /* Private */,
      10,    0,   83,    2, 0x08,   12 /* Private */,
      11,    0,   84,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject fCauhinhtuongtac::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSfCauhinhtuongtacENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSfCauhinhtuongtacENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSfCauhinhtuongtacENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<fCauhinhtuongtac, std::true_type>,
        // method 'on_ckbCapNhatThongTin_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_checkBox_9_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ckbGioiHanThoiGianChayTaiKhoan_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ckbGioiHanThoiGianChayKichBan_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ckbGetToken_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ckbGroup_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnAdd_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnQuanlyKichBan_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnCancel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void fCauhinhtuongtac::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<fCauhinhtuongtac *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_ckbCapNhatThongTin_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->on_checkBox_9_clicked(); break;
        case 2: _t->on_ckbGioiHanThoiGianChayTaiKhoan_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_ckbGioiHanThoiGianChayKichBan_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->on_ckbGetToken_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_ckbGroup_clicked(); break;
        case 6: _t->on_btnAdd_clicked(); break;
        case 7: _t->on_btnQuanlyKichBan_clicked(); break;
        case 8: _t->on_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *fCauhinhtuongtac::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fCauhinhtuongtac::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSfCauhinhtuongtacENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int fCauhinhtuongtac::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
