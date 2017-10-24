/****************************************************************************
** Meta object code from reading C++ file 'MusicPlayer.h'
**
** Created: Mon Oct 23 15:03:11 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MusicPlayer/MusicPlayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      52,   45,   12,   12, 0x05,
     111,   81,   12,   12, 0x05,
     180,  152,   12,   12, 0x05,
     236,  227,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     284,  272,   12,   12, 0x09,
     325,  315,   12,   12, 0x09,
     354,  315,   12,   12, 0x09,
     383,  315,   12,   12, 0x09,
     412,   12,   12,   12, 0x08,
     424,   12,   12,   12, 0x08,
     456,  436,   12,   12, 0x08,
     499,  493,   12,   12, 0x08,
     537,  531,   12,   12, 0x08,
     576,   12,   12,   12, 0x08,
     604,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MusicPlayer[] = {
    "MusicPlayer\0\0mode\0onMusicPlayerPlayMode(int)\0"
    "status\0onMusicPlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "type,xml\0onMusicPlayerFileNames(int,QString)\0"
    "type,status\0onDeviceWatcherStatus(int,int)\0"
    "path,type\0onMusicFilePath(QString,int)\0"
    "onImageFilePath(QString,int)\0"
    "onVideoFilePath(QString,int)\0onTimeout()\0"
    "onStarted()\0exitCode,exitStatus\0"
    "onFinished(int,QProcess::ExitStatus)\0"
    "error\0onError(QProcess::ProcessError)\0"
    "state\0onStateChanged(QProcess::ProcessState)\0"
    "onReadyReadStandardOutput()\0"
    "onReadyReadStandardError()\0"
};

void MusicPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MusicPlayer *_t = static_cast<MusicPlayer *>(_o);
        switch (_id) {
        case 0: _t->onMusicPlayerPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onMusicPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->onMusicPlayerID3TagChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 4: _t->onMusicPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->onMusicFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->onImageFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: _t->onVideoFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 9: _t->onTimeout(); break;
        case 10: _t->onStarted(); break;
        case 11: _t->onFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 12: _t->onError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 13: _t->onStateChanged((*reinterpret_cast< QProcess::ProcessState(*)>(_a[1]))); break;
        case 14: _t->onReadyReadStandardOutput(); break;
        case 15: _t->onReadyReadStandardError(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MusicPlayer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MusicPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MusicPlayer,
      qt_meta_data_MusicPlayer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer))
        return static_cast<void*>(const_cast< MusicPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MusicPlayer::onMusicPlayerPlayMode(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicPlayer::onMusicPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MusicPlayer::onMusicPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicPlayer::onMusicPlayerID3TagChange(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MusicPlayer::onMusicPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
