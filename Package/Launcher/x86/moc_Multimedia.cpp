/****************************************************************************
** Meta object code from reading C++ file 'Multimedia.h'
**
** Created: Mon Oct 23 15:07:55 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Multimedia/Multimedia.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Multimedia.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Multimedia[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x05,
      65,   55,   11,   11, 0x05,
      94,   55,   11,   11, 0x05,
     123,   55,   11,   11, 0x05,
     157,  152,   11,   11, 0x05,
     191,  184,   11,   11, 0x05,
     250,  220,   11,   11, 0x05,
     319,  291,   11,   11, 0x05,
     375,  366,   11,   11, 0x05,
     411,  366,   11,   11, 0x05,
     447,  184,   11,   11, 0x05,
     511,  476,   11,   11, 0x05,
     556,  184,   11,   11, 0x05,
     585,  184,   11,   11, 0x05,
     614,  366,   11,   11, 0x05,
     650,  291,   11,   11, 0x05,
     696,  220,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     745,  737,   11,   11, 0x08,
     774,  737,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Multimedia[] = {
    "Multimedia\0\0type,status\0"
    "onDeviceWatcherStatus(int,int)\0path,type\0"
    "onMusicFilePath(QString,int)\0"
    "onImageFilePath(QString,int)\0"
    "onVideoFilePath(QString,int)\0mode\0"
    "onMusicPlayerPlayMode(int)\0status\0"
    "onMusicPlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "type,xml\0onMusicPlayerFileNames(int,QString)\0"
    "onImagePlayerFileNames(int,QString)\0"
    "onImagePlayerPlayStatus(int)\0"
    "type,filePath,index,percent,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "onVideoPlayerShowStatus(int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "service\0onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
};

void Multimedia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Multimedia *_t = static_cast<Multimedia *>(_o);
        switch (_id) {
        case 0: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->onMusicFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->onImageFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->onVideoFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->onMusicPlayerPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->onMusicPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->onMusicPlayerID3TagChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 8: _t->onMusicPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->onImagePlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: _t->onImagePlayerChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 12: _t->onVideoPlayerShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: _t->onVideoPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->onVideoPlayerInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 16: _t->onVideoPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 17: _t->onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Multimedia::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Multimedia::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Multimedia,
      qt_meta_data_Multimedia, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Multimedia::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Multimedia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Multimedia::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Multimedia))
        return static_cast<void*>(const_cast< Multimedia*>(this));
    if (!strcmp(_clname, "MultimediaService::Interface"))
        return static_cast< MultimediaService::Interface*>(const_cast< Multimedia*>(this));
    if (!strcmp(_clname, "DbusService::Interface"))
        return static_cast< DbusService::Interface*>(const_cast< Multimedia*>(this));
    return QObject::qt_metacast(_clname);
}

int Multimedia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Multimedia::onDeviceWatcherStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Multimedia::onMusicFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Multimedia::onImageFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Multimedia::onVideoFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Multimedia::onMusicPlayerPlayMode(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Multimedia::onMusicPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Multimedia::onMusicPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Multimedia::onMusicPlayerID3TagChange(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Multimedia::onMusicPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Multimedia::onImagePlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Multimedia::onImagePlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Multimedia::onImagePlayerChange(const int _t1, const QString & _t2, const int _t3, const int _t4, const int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Multimedia::onVideoPlayerShowStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Multimedia::onVideoPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Multimedia::onVideoPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Multimedia::onVideoPlayerInformation(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Multimedia::onVideoPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_END_MOC_NAMESPACE
