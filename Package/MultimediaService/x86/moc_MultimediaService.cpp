/****************************************************************************
** Meta object code from reading C++ file 'MultimediaService.h'
**
** Created: Mon Oct 23 15:03:08 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MultimediaService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultimediaService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultimediaService[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
      50,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // classinfo: key, value
      46,   18,

 // signals: signature, parameters, type, tag, flags
      75,   63,   62,   62, 0x05,
     116,  106,   62,   62, 0x05,
     145,  106,   62,   62, 0x05,
     174,  106,   62,   62, 0x05,
     208,  203,   62,   62, 0x05,
     242,  235,   62,   62, 0x05,
     301,  271,   62,   62, 0x05,
     370,  342,   62,   62, 0x05,
     426,  417,   62,   62, 0x05,
     462,  417,   62,   62, 0x05,
     498,  235,   62,   62, 0x05,
     562,  527,   62,   62, 0x05,
     607,  235,   62,   62, 0x05,
     636,  235,   62,   62, 0x05,
     665,  417,   62,   62, 0x05,
     701,  342,   62,   62, 0x05,
     747,  271,   62,   62, 0x05,

 // slots: signature, parameters, type, tag, flags
     795,  788,   62,   62, 0x0a,
     810,  788,   62,   62, 0x0a,
     831,  824,   62,   62, 0x0a,
     855,   62,   62,   62, 0x0a,
     874,  869,   62,   62, 0x0a,
     904,   62,   62,   62, 0x0a,
     934,   62,   62,   62, 0x0a,
     965,  203,   62,   62, 0x0a,
     993,   62,   62,   62, 0x0a,
    1026,  235,   62,   62, 0x0a,
    1067, 1056,   62,   62, 0x0a,
    1105,   62,   62,   62, 0x0a,
    1144,   62,   62,   62, 0x0a,
    1190, 1179,   62,   62, 0x0a,
    1223,   62,   62,   62, 0x0a,
    1241,  869,   62,   62, 0x0a,
    1274, 1056,   62,   62, 0x0a,
    1312,   62,   62,   62, 0x0a,
    1351,   62,   62,   62, 0x0a,
    1386,   62,   62,   62, 0x0a,
    1411,   62,   62,   62, 0x0a,
    1436,   62,   62,   62, 0x0a,
    1462,   62,   62,   62, 0x0a,
    1495,  235,   62,   62, 0x0a,
    1525,   62,   62,   62, 0x0a,
    1543,  869,   62,   62, 0x0a,
    1576,   62,   62,   62, 0x0a,
    1609,  235,   62,   62, 0x0a,
    1639,  235,   62,   62, 0x0a,
    1697, 1669,   62,   62, 0x0a,
    1751,   62,   62,   62, 0x0a,
    1790,   62,   62,   62, 0x0a,
    1825, 1179,   62,   62, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MultimediaService[] = {
    "MultimediaService\0Local.DbusServer.Multimedia\0"
    "D-Bus Interface\0\0type,status\0"
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
    "action\0usbToggle(int)\0sdToggle(int)\0"
    "source\0releaseAudioSource(int)\0"
    "synchronize()\0type\0deviceWatcherCheckStatus(int)\0"
    "musicPlayerRequestFileNames()\0"
    "musicPlayerSetPlayModeToggle()\0"
    "musicPlayerSetPlayMode(int)\0"
    "musicPlayerSetPlayStatusToggle()\0"
    "musicPlayerSetPlayStatus(int)\0type,index\0"
    "musicPlayerPlayListViewIndex(int,int)\0"
    "musicPlayerPlayPreviousListViewIndex()\0"
    "musicPlayerPlayNextListViewIndex()\0"
    "millesimal\0musicPlayerSeekToMillesimal(int)\0"
    "musicPlayerExit()\0imagePlayerRequestFileNames(int)\0"
    "imagePlayerPlayListViewIndex(int,int)\0"
    "imagePlayerPlayPreviousListViewIndex()\0"
    "imagePlayerPlayNextListViewIndex()\0"
    "imagePlayerRotateImage()\0"
    "imagePlayerZoomInImage()\0"
    "imagePlayerZoomOutImage()\0"
    "imagePlayerSetPlayStatusToggle()\0"
    "imagePlayerSetPlayStatus(int)\0"
    "imagePlayerExit()\0videoPlayerRequestFileNames(int)\0"
    "videoPlayerSetPlayStatusToggle()\0"
    "videoPlayerSetShowStatus(int)\0"
    "videoPlayerSetPlayStatus(int)\0"
    "type,index,x,y,width,height\0"
    "videoPlayerPlayListViewIndex(int,int,int,int,int,int)\0"
    "videoPlayerPlayPreviousListViewIndex()\0"
    "videoPlayerPlayNextListViewIndex()\0"
    "videoPlayerSeekToMillesimal(int)\0"
};

void MultimediaService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultimediaService *_t = static_cast<MultimediaService *>(_o);
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
        case 17: _t->usbToggle((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 18: _t->sdToggle((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 19: _t->releaseAudioSource((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 20: _t->synchronize(); break;
        case 21: _t->deviceWatcherCheckStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 22: _t->musicPlayerRequestFileNames(); break;
        case 23: _t->musicPlayerSetPlayModeToggle(); break;
        case 24: _t->musicPlayerSetPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 25: _t->musicPlayerSetPlayStatusToggle(); break;
        case 26: _t->musicPlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 27: _t->musicPlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 28: _t->musicPlayerPlayPreviousListViewIndex(); break;
        case 29: _t->musicPlayerPlayNextListViewIndex(); break;
        case 30: _t->musicPlayerSeekToMillesimal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 31: _t->musicPlayerExit(); break;
        case 32: _t->imagePlayerRequestFileNames((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 33: _t->imagePlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 34: _t->imagePlayerPlayPreviousListViewIndex(); break;
        case 35: _t->imagePlayerPlayNextListViewIndex(); break;
        case 36: _t->imagePlayerRotateImage(); break;
        case 37: _t->imagePlayerZoomInImage(); break;
        case 38: _t->imagePlayerZoomOutImage(); break;
        case 39: _t->imagePlayerSetPlayStatusToggle(); break;
        case 40: _t->imagePlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 41: _t->imagePlayerExit(); break;
        case 42: _t->videoPlayerRequestFileNames((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 43: _t->videoPlayerSetPlayStatusToggle(); break;
        case 44: _t->videoPlayerSetShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 45: _t->videoPlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 46: _t->videoPlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5])),(*reinterpret_cast< const int(*)>(_a[6]))); break;
        case 47: _t->videoPlayerPlayPreviousListViewIndex(); break;
        case 48: _t->videoPlayerPlayNextListViewIndex(); break;
        case 49: _t->videoPlayerSeekToMillesimal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultimediaService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultimediaService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MultimediaService,
      qt_meta_data_MultimediaService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultimediaService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultimediaService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultimediaService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaService))
        return static_cast<void*>(const_cast< MultimediaService*>(this));
    return QObject::qt_metacast(_clname);
}

int MultimediaService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    }
    return _id;
}

// SIGNAL 0
void MultimediaService::onDeviceWatcherStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultimediaService::onMusicFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultimediaService::onImageFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MultimediaService::onVideoFilePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MultimediaService::onMusicPlayerPlayMode(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MultimediaService::onMusicPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MultimediaService::onMusicPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MultimediaService::onMusicPlayerID3TagChange(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MultimediaService::onMusicPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MultimediaService::onImagePlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MultimediaService::onImagePlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MultimediaService::onImagePlayerChange(const int _t1, const QString & _t2, const int _t3, const int _t4, const int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MultimediaService::onVideoPlayerShowStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MultimediaService::onVideoPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MultimediaService::onVideoPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MultimediaService::onVideoPlayerInformation(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MultimediaService::onVideoPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_END_MOC_NAMESPACE
