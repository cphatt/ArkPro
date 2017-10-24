/****************************************************************************
** Meta object code from reading C++ file 'AVService.h'
**
** Created: Wed Oct 18 10:36:41 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AVService/AVService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AVService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AVService[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
       3,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
      30,   10,

 // signals: signature, parameters, type, tag, flags
      59,   47,   46,   46, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   79,   46,   46, 0x0a,
     110,   46,   46,   46, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AVService[] = {
    "AVService\0Local.DbusServer.AV\0"
    "D-Bus Interface\0\0type,status\0"
    "onAVStatus(int,int)\0source\0"
    "releaseAudioSource(int)\0onTimeout()\0"
};

void AVService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AVService *_t = static_cast<AVService *>(_o);
        switch (_id) {
        case 0: _t->onAVStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->releaseAudioSource((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AVService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AVService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AVService,
      qt_meta_data_AVService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AVService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AVService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AVService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AVService))
        return static_cast<void*>(const_cast< AVService*>(this));
    return QObject::qt_metacast(_clname);
}

int AVService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AVService::onAVStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
