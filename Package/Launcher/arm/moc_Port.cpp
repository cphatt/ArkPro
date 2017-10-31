/****************************************************************************
** Meta object code from reading C++ file 'Port.h'
**
** Created: Tue Oct 24 11:32:04 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Port/Port.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Port.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Port[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,    6,    5,    5, 0x05,
      70,   65,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   65,    5,    5, 0x09,
     133,  121,    5,    5, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Port[] = {
    "Port\0\0type,buffer,size\0"
    "onMCUDataRecv(Port::Type,const char*,int)\0"
    "data\0read_port_data(QByteArray)\0"
    "handlerData(QByteArray)\0type,status\0"
    "onDeviceWatcherStatus(int,int)\0"
};

const QMetaObject Port::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Port,
      qt_meta_data_Port, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Port::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Port::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Port::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Port))
        return static_cast<void*>(const_cast< Port*>(this));
    return QObject::qt_metacast(_clname);
}

int Port::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onMCUDataRecv((*reinterpret_cast< const Port::Type(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 1: read_port_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: handlerData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Port::onMCUDataRecv(const Port::Type _t1, const char * _t2, const int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Port::read_port_data(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
