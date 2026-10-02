/****************************************************************************
** Meta object code from reading C++ file 'xy_control_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/widgets/xy_control_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xy_control_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XYControlWidget_t {
    QByteArrayData data[15];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XYControlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XYControlWidget_t qt_meta_stringdata_XYControlWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "XYControlWidget"
QT_MOC_LITERAL(1, 16, 11), // "moveRequest"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "dx"
QT_MOC_LITERAL(4, 32, 2), // "dy"
QT_MOC_LITERAL(5, 35, 11), // "homeRequest"
QT_MOC_LITERAL(6, 47, 11), // "stopRequest"
QT_MOC_LITERAL(7, 59, 17), // "parametersChanged"
QT_MOC_LITERAL(8, 77, 11), // "GalvoParams"
QT_MOC_LITERAL(9, 89, 6), // "params"
QT_MOC_LITERAL(10, 96, 18), // "updateFeedbackData"
QT_MOC_LITERAL(11, 115, 1), // "x"
QT_MOC_LITERAL(12, 117, 1), // "y"
QT_MOC_LITERAL(13, 119, 5), // "angle"
QT_MOC_LITERAL(14, 125, 14) // "onParamChanged"

    },
    "XYControlWidget\0moveRequest\0\0dx\0dy\0"
    "homeRequest\0stopRequest\0parametersChanged\0"
    "GalvoParams\0params\0updateFeedbackData\0"
    "x\0y\0angle\0onParamChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XYControlWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    0,   49,    2, 0x06 /* Public */,
       6,    0,   50,    2, 0x06 /* Public */,
       7,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    3,   54,    2, 0x0a /* Public */,
      14,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   13,
    QMetaType::Void,

       0        // eod
};

void XYControlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XYControlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->moveRequest((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->homeRequest(); break;
        case 2: _t->stopRequest(); break;
        case 3: _t->parametersChanged((*reinterpret_cast< const GalvoParams(*)>(_a[1]))); break;
        case 4: _t->updateFeedbackData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->onParamChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GalvoParams >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (XYControlWidget::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XYControlWidget::moveRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (XYControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XYControlWidget::homeRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (XYControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XYControlWidget::stopRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (XYControlWidget::*)(const GalvoParams & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XYControlWidget::parametersChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject XYControlWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_XYControlWidget.data,
    qt_meta_data_XYControlWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XYControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XYControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XYControlWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int XYControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void XYControlWidget::moveRequest(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XYControlWidget::homeRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void XYControlWidget::stopRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void XYControlWidget::parametersChanged(const GalvoParams & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
