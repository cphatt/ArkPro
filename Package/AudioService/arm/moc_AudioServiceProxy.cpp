/****************************************************************************
** Meta object code from reading C++ file 'AudioServiceProxy.h'
**
** Created: Mon Oct 23 11:16:59 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AudioService/AudioServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerAudioManagerInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   38,   37,   37, 0x05,
      64,   59,   37,   37, 0x05,
      92,   80,   37,   37, 0x05,
     124,  116,   37,   37, 0x05,

 // slots: signature, parameters, type, tag, flags
     173,   37,  153,   37, 0x0a,
     197,   37,  153,   37, 0x0a,
     215,   37,  153,   37, 0x0a,
     239,   59,  153,   37, 0x0a,
     258,   38,  153,   37, 0x0a,
     289,  282,  153,   37, 0x0a,
     311,   37,  153,   37, 0x0a,
     326,   37,  153,   37, 0x0a,
     339,   37,  153,   37, 0x0a,
     357,  282,  153,   37, 0x0a,
     372,   37,  153,   37, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerAudioManagerInterface[] = {
    "LocalDbusServerAudioManagerInterface\0"
    "\0freq\0onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "type,volume\0onVolumeChange(int,int)\0"
    "min,max\0onVolumeRangeChange(int,int)\0"
    "QDBusPendingReply<>\0requestDecreaseVolume()\0"
    "requestFMToggle()\0requestIncreaseVolume()\0"
    "requestOpenFM(int)\0requestSetFreqency(int)\0"
    "volume\0requestSetVolume(int)\0"
    "requestStart()\0requestget()\0"
    "requsetIsOpenFM()\0requstset(int)\0"
    "synchronize()\0"
};

const QMetaObject LocalDbusServerAudioManagerInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerAudioManagerInterface,
      qt_meta_data_LocalDbusServerAudioManagerInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerAudioManagerInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerAudioManagerInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerAudioManagerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerAudioManagerInterface))
        return static_cast<void*>(const_cast< LocalDbusServerAudioManagerInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerAudioManagerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: { QDBusPendingReply<> _r = requestDecreaseVolume();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 5: { QDBusPendingReply<> _r = requestFMToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 6: { QDBusPendingReply<> _r = requestIncreaseVolume();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 7: { QDBusPendingReply<> _r = requestOpenFM((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 8: { QDBusPendingReply<> _r = requestSetFreqency((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 9: { QDBusPendingReply<> _r = requestSetVolume((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 10: { QDBusPendingReply<> _r = requestStart();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 11: { QDBusPendingReply<> _r = requestget();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 12: { QDBusPendingReply<> _r = requsetIsOpenFM();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 13: { QDBusPendingReply<> _r = requstset((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 14: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerAudioManagerInterface::onFMChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerAudioManagerInterface::onFMIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerAudioManagerInterface::onVolumeChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerAudioManagerInterface::onVolumeRangeChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
