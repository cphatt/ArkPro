/****************************************************************************
** Meta object code from reading C++ file 'AudioService.h'
**
** Created: Wed Oct 18 10:36:24 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AudioService/AudioService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioService[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
      14,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
      43,   13,

 // signals: signature, parameters, type, tag, flags
      65,   60,   59,   59, 0x05,
      86,   81,   59,   59, 0x05,
     109,  102,   59,   59, 0x05,
     137,  129,   59,   59, 0x05,

 // slots: signature, parameters, type, tag, flags
     212,  171,  166,   59, 0x0a,
     275,  268,   59,   59, 0x0a,
     299,   59,   59,   59, 0x0a,
     313,   59,   59,   59, 0x0a,
     337,   59,   59,   59, 0x0a,
     361,   59,   59,   59, 0x0a,
     379,   81,   59,   59, 0x0a,
     398,   59,   59,   59, 0x0a,
     416,  102,   59,   59, 0x0a,
     438,   60,   59,   59, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AudioService[] = {
    "AudioService\0Local.DbusServer.AudioManager\0"
    "D-Bus Interface\0\0freq\0onFMChange(int)\0"
    "open\0onFMIsOpen(int)\0volume\0"
    "onVolumeChange(int)\0min,max\0"
    "onVolumeRangeChange(int,int)\0bool\0"
    "source,destination,path,interface,method\0"
    "requestAudioSource(int,QString,QString,QString,QString)\0"
    "source\0releaseAudioSource(int)\0"
    "synchronize()\0requestIncreaseVolume()\0"
    "requestDecreaseVolume()\0requsetIsOpenFM()\0"
    "requestOpenFM(int)\0requestFMToggle()\0"
    "requestSetVolume(int)\0requestSetFreqency(int)\0"
};

void AudioService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AudioService *_t = static_cast<AudioService *>(_o);
        switch (_id) {
        case 0: _t->onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onVolumeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: { bool _r = _t->requestAudioSource((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->releaseAudioSource((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->synchronize(); break;
        case 7: _t->requestIncreaseVolume(); break;
        case 8: _t->requestDecreaseVolume(); break;
        case 9: _t->requsetIsOpenFM(); break;
        case 10: _t->requestOpenFM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->requestFMToggle(); break;
        case 12: _t->requestSetVolume((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->requestSetFreqency((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AudioService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AudioService,
      qt_meta_data_AudioService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioService))
        return static_cast<void*>(const_cast< AudioService*>(this));
    return QObject::qt_metacast(_clname);
}

int AudioService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void AudioService::onFMChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AudioService::onFMIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AudioService::onVolumeChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AudioService::onVolumeRangeChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
