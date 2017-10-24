/****************************************************************************
** Meta object code from reading C++ file 'MultimediaServiceProxy.h'
**
** Created: Mon Oct 23 15:03:13 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MultimediaServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultimediaServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerMultimediaInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: signature, parameters, type, tag, flags
      48,   36,   35,   35, 0x05,
      89,   79,   35,   35, 0x05,
     151,  118,   35,   35, 0x05,
     205,  196,   35,   35, 0x05,
     248,  241,   35,   35, 0x05,
     277,   79,   35,   35, 0x05,
     336,  306,   35,   35, 0x05,
     377,  196,   35,   35, 0x05,
     441,  413,   35,   35, 0x05,
     493,  488,   35,   35, 0x05,
     520,  241,   35,   35, 0x05,
     549,   79,   35,   35, 0x05,
     578,  306,   35,   35, 0x05,
     619,  196,   35,   35, 0x05,
     655,  413,   35,   35, 0x05,
     701,  241,   35,   35, 0x05,
     730,  241,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
     784,  779,  759,   35, 0x0a,
     814,   35,  759,   35, 0x0a,
     843,  832,  759,   35, 0x0a,
     881,   35,  759,   35, 0x0a,
     916,   35,  759,   35, 0x0a,
     955,  779,  759,   35, 0x0a,
     988,   35,  759,   35, 0x0a,
    1013,  241,  759,   35, 0x0a,
    1043,   35,  759,   35, 0x0a,
    1076,   35,  759,   35, 0x0a,
    1101,   35,  759,   35, 0x0a,
    1127,   35,  759,   35, 0x0a,
    1145,  832,  759,   35, 0x0a,
    1183,   35,  759,   35, 0x0a,
    1218,   35,  759,   35, 0x0a,
    1257,   35,  759,   35, 0x0a,
    1298, 1287,  759,   35, 0x0a,
    1331,  488,  759,   35, 0x0a,
    1359,   35,  759,   35, 0x0a,
    1390,  241,  759,   35, 0x0a,
    1420,   35,  759,   35, 0x0a,
    1460, 1453,  759,   35, 0x0a,
    1484,   35,  759,   35, 0x0a,
    1526, 1498,  759,   35, 0x0a,
    1580,   35,  759,   35, 0x0a,
    1615,   35,  759,   35, 0x0a,
    1654,  779,  759,   35, 0x0a,
    1687, 1287,  759,   35, 0x0a,
    1720,  241,  759,   35, 0x0a,
    1750,   35,  759,   35, 0x0a,
    1783,  241,  759,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerMultimediaInterface[] = {
    "LocalDbusServerMultimediaInterface\0\0"
    "type,status\0onDeviceWatcherStatus(int,int)\0"
    "path,type\0onImageFilePath(QString,int)\0"
    "type,filePath,index,scale,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "type,xml\0onImagePlayerFileNames(int,QString)\0"
    "status\0onImagePlayerPlayStatus(int)\0"
    "onMusicFilePath(QString,int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "onMusicPlayerFileNames(int,QString)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "mode\0onMusicPlayerPlayMode(int)\0"
    "onMusicPlayerPlayStatus(int)\0"
    "onVideoFilePath(QString,int)\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onVideoPlayerShowStatus(int)\0"
    "QDBusPendingReply<>\0type\0"
    "deviceWatcherCheckStatus(int)\0"
    "imagePlayerExit()\0type,index\0"
    "imagePlayerPlayListViewIndex(int,int)\0"
    "imagePlayerPlayNextListViewIndex()\0"
    "imagePlayerPlayPreviousListViewIndex()\0"
    "imagePlayerRequestFileNames(int)\0"
    "imagePlayerRotateImage()\0"
    "imagePlayerSetPlayStatus(int)\0"
    "imagePlayerSetPlayStatusToggle()\0"
    "imagePlayerZoomInImage()\0"
    "imagePlayerZoomOutImage()\0musicPlayerExit()\0"
    "musicPlayerPlayListViewIndex(int,int)\0"
    "musicPlayerPlayNextListViewIndex()\0"
    "musicPlayerPlayPreviousListViewIndex()\0"
    "musicPlayerRequestFileNames()\0millesimal\0"
    "musicPlayerSeekToMillesimal(int)\0"
    "musicPlayerSetPlayMode(int)\0"
    "musicPlayerSetPlayModeToggle()\0"
    "musicPlayerSetPlayStatus(int)\0"
    "musicPlayerSetPlayStatusToggle()\0"
    "source\0releaseAudioSource(int)\0"
    "synchronize()\0type,index,x,y,width,height\0"
    "videoPlayerPlayListViewIndex(int,int,int,int,int,int)\0"
    "videoPlayerPlayNextListViewIndex()\0"
    "videoPlayerPlayPreviousListViewIndex()\0"
    "videoPlayerRequestFileNames(int)\0"
    "videoPlayerSeekToMillesimal(int)\0"
    "videoPlayerSetPlayStatus(int)\0"
    "videoPlayerSetPlayStatusToggle()\0"
    "videoPlayerSetShowStatus(int)\0"
};

void LocalDbusServerMultimediaInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LocalDbusServerMultimediaInterface *_t = static_cast<LocalDbusServerMultimediaInterface *>(_o);
        switch (_id) {
        case 0: _t->onDeviceWatcherStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onImageFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->onImagePlayerChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->onImagePlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onImagePlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onMusicFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->onMusicPlayerElapsedInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->onMusicPlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->onMusicPlayerID3TagChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->onMusicPlayerPlayMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onMusicPlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onVideoFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->onVideoPlayerElapsedInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->onVideoPlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->onVideoPlayerInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 15: _t->onVideoPlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onVideoPlayerShowStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: { QDBusPendingReply<> _r = _t->deviceWatcherCheckStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 18: { QDBusPendingReply<> _r = _t->imagePlayerExit();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 19: { QDBusPendingReply<> _r = _t->imagePlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 20: { QDBusPendingReply<> _r = _t->imagePlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 21: { QDBusPendingReply<> _r = _t->imagePlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 22: { QDBusPendingReply<> _r = _t->imagePlayerRequestFileNames((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 23: { QDBusPendingReply<> _r = _t->imagePlayerRotateImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 24: { QDBusPendingReply<> _r = _t->imagePlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 25: { QDBusPendingReply<> _r = _t->imagePlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 26: { QDBusPendingReply<> _r = _t->imagePlayerZoomInImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 27: { QDBusPendingReply<> _r = _t->imagePlayerZoomOutImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 28: { QDBusPendingReply<> _r = _t->musicPlayerExit();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 29: { QDBusPendingReply<> _r = _t->musicPlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 30: { QDBusPendingReply<> _r = _t->musicPlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 31: { QDBusPendingReply<> _r = _t->musicPlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 32: { QDBusPendingReply<> _r = _t->musicPlayerRequestFileNames();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 33: { QDBusPendingReply<> _r = _t->musicPlayerSeekToMillesimal((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 34: { QDBusPendingReply<> _r = _t->musicPlayerSetPlayMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 35: { QDBusPendingReply<> _r = _t->musicPlayerSetPlayModeToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 36: { QDBusPendingReply<> _r = _t->musicPlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 37: { QDBusPendingReply<> _r = _t->musicPlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 38: { QDBusPendingReply<> _r = _t->releaseAudioSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 39: { QDBusPendingReply<> _r = _t->synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 40: { QDBusPendingReply<> _r = _t->videoPlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 41: { QDBusPendingReply<> _r = _t->videoPlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 42: { QDBusPendingReply<> _r = _t->videoPlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 43: { QDBusPendingReply<> _r = _t->videoPlayerRequestFileNames((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 44: { QDBusPendingReply<> _r = _t->videoPlayerSeekToMillesimal((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 45: { QDBusPendingReply<> _r = _t->videoPlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 46: { QDBusPendingReply<> _r = _t->videoPlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 47: { QDBusPendingReply<> _r = _t->videoPlayerSetShowStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LocalDbusServerMultimediaInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LocalDbusServerMultimediaInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerMultimediaInterface,
      qt_meta_data_LocalDbusServerMultimediaInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerMultimediaInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerMultimediaInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerMultimediaInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerMultimediaInterface))
        return static_cast<void*>(const_cast< LocalDbusServerMultimediaInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerMultimediaInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerMultimediaInterface::onDeviceWatcherStatus(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerMultimediaInterface::onImageFilePath(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerMultimediaInterface::onImagePlayerChange(int _t1, const QString & _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerMultimediaInterface::onImagePlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalDbusServerMultimediaInterface::onImagePlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalDbusServerMultimediaInterface::onMusicFilePath(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LocalDbusServerMultimediaInterface::onMusicPlayerElapsedInformation(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LocalDbusServerMultimediaInterface::onMusicPlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LocalDbusServerMultimediaInterface::onMusicPlayerID3TagChange(int _t1, int _t2, const QString & _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void LocalDbusServerMultimediaInterface::onMusicPlayerPlayMode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void LocalDbusServerMultimediaInterface::onMusicPlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void LocalDbusServerMultimediaInterface::onVideoFilePath(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void LocalDbusServerMultimediaInterface::onVideoPlayerElapsedInformation(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void LocalDbusServerMultimediaInterface::onVideoPlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void LocalDbusServerMultimediaInterface::onVideoPlayerInformation(const int _t1, const int _t2, const QString & _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void LocalDbusServerMultimediaInterface::onVideoPlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void LocalDbusServerMultimediaInterface::onVideoPlayerShowStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_END_MOC_NAMESPACE
