/****************************************************************************
** Meta object code from reading C++ file 'FMToolWidget.h'
**
** Created: Wed Oct 18 10:38:38 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/FMWidget/FMToolWidget/FMToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FMToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FMToolWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x09,
      40,   35,   13,   13, 0x09,
      68,   56,   13,   13, 0x09,
     100,   92,   13,   13, 0x09,
     129,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FMToolWidget[] = {
    "FMToolWidget\0\0freq\0onFMChange(int)\0"
    "open\0onFMIsOpen(int)\0type,volume\0"
    "onVolumeChange(int,int)\0min,max\0"
    "onVolumeRangeChange(int,int)\0"
    "onToolButtonRelease()\0"
};

void FMToolWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FMToolWidget *_t = static_cast<FMToolWidget *>(_o);
        switch (_id) {
        case 0: _t->onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onToolButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FMToolWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FMToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FMToolWidget,
      qt_meta_data_FMToolWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FMToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FMToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FMToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FMToolWidget))
        return static_cast<void*>(const_cast< FMToolWidget*>(this));
    if (!strcmp(_clname, "Audio::Interface"))
        return static_cast< Audio::Interface*>(const_cast< FMToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FMToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
