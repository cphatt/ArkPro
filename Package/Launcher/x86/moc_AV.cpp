/****************************************************************************
** Meta object code from reading C++ file 'AV.h'
**
** Created: Wed Oct 18 10:38:34 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/AV/AV.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AV.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AV[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,    4,    3,    3, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   36,    3,    3, 0x0a,
      80,   75,    3,    3, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AV[] = {
    "AV\0\0type,status\0onAVStatus(int,int)\0"
    "type,width,height\0startAV(int,int,int)\0"
    "type\0stopAV(int)\0"
};

void AV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AV *_t = static_cast<AV *>(_o);
        switch (_id) {
        case 0: _t->onAVStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->startAV((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 2: _t->stopAV((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AV::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AV::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AV,
      qt_meta_data_AV, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AV::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AV::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AV))
        return static_cast<void*>(const_cast< AV*>(this));
    if (!strcmp(_clname, "AVService::Interface"))
        return static_cast< AVService::Interface*>(const_cast< AV*>(this));
    return QObject::qt_metacast(_clname);
}

int AV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AV::onAVStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE