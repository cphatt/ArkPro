/****************************************************************************
** Meta object code from reading C++ file 'MusicPlayer.h'
**
** Created: Mon Oct 23 11:17:13 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MusicPlayer/MusicPlayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       5,       // revision
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
     175,  152,   12,   12, 0x05,
     227,  218,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     275,  263,   12,   12, 0x09,
     316,  306,   12,   12, 0x09,
     345,  306,   12,   12, 0x09,
     374,  306,   12,   12, 0x09,
     403,   12,   12,   12, 0x08,
     415,   12,   12,   12, 0x08,
     447,  427,   12,   12, 0x08,
     490,  484,   12,   12, 0x08,
     528,  522,   12,   12, 0x08,
     567,   12,   12,   12, 0x08,
     595,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MusicPlayer[] = {
    "MusicPlayer\0\0mode\0onMusicPlayerPlayMode(int)\0"
    "status\0onMusicPlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,QString,int)\0"
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

const QMetaObject MusicPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MusicPlayer,
      qt_meta_data_MusicPlayer, 0 }
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
        switch (_id) {
        case 0: onMusicPlayerPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onMusicPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: onMusicPlayerID3TagChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 4: onMusicPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: onMusicFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: onImageFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: onVideoFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 9: onTimeout(); break;
        case 10: onStarted(); break;
        case 11: onFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 12: onError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 13: onStateChanged((*reinterpret_cast< QProcess::ProcessState(*)>(_a[1]))); break;
        case 14: onReadyReadStandardOutput(); break;
        case 15: onReadyReadStandardError(); break;
        default: ;
        }
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
void MusicPlayer::onMusicPlayerID3TagChange(const int _t1, const QString & _t2, const int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MusicPlayer::onMusicPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
