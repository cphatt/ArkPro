/****************************************************************************
** Meta object code from reading C++ file 'VideoPlayer.h'
**
** Created: Mon Oct 23 11:17:14 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/VideoPlayer/VideoPlayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoPlayer[] = {

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
      20,   13,   12,   12, 0x05,
      49,   13,   12,   12, 0x05,
      87,   78,   12,   12, 0x05,
     140,  123,   12,   12, 0x05,
     208,  178,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     261,  249,   12,   12, 0x09,
     302,  292,   12,   12, 0x09,
     331,  292,   12,   12, 0x09,
     360,  292,   12,   12, 0x09,
     389,   12,   12,   12, 0x08,
     401,   12,   12,   12, 0x08,
     433,  413,   12,   12, 0x08,
     476,  470,   12,   12, 0x08,
     514,  508,   12,   12, 0x08,
     553,   12,   12,   12, 0x08,
     581,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoPlayer[] = {
    "VideoPlayer\0\0status\0onVideoPlayerShowStatus(int)\0"
    "onVideoPlayerPlayStatus(int)\0type,xml\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "fileName,endTime\0onVideoPlayerInformation(QString,int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
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

const QMetaObject VideoPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VideoPlayer,
      qt_meta_data_VideoPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayer))
        return static_cast<void*>(const_cast< VideoPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int VideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onVideoPlayerShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onVideoPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onVideoPlayerInformation((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: onVideoPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
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
void VideoPlayer::onVideoPlayerShowStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoPlayer::onVideoPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoPlayer::onVideoPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VideoPlayer::onVideoPlayerInformation(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VideoPlayer::onVideoPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
