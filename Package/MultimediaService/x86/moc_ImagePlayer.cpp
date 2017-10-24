/****************************************************************************
** Meta object code from reading C++ file 'ImagePlayer.h'
**
** Created: Mon Oct 23 15:03:10 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/ImagePlayer/ImagePlayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImagePlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImagePlayer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,
      65,   58,   12,   12, 0x05,
     129,   94,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     186,  174,   12,   12, 0x09,
     227,  217,   12,   12, 0x09,
     256,  217,   12,   12, 0x09,
     285,  217,   12,   12, 0x09,
     314,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImagePlayer[] = {
    "ImagePlayer\0\0type,xml\0"
    "onImagePlayerFileNames(int,QString)\0"
    "status\0onImagePlayerPlayStatus(int)\0"
    "type,filePath,index,percent,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "type,status\0onDeviceWatcherStatus(int,int)\0"
    "path,type\0onMusicFilePath(QString,int)\0"
    "onImageFilePath(QString,int)\0"
    "onVideoFilePath(QString,int)\0onTimeout()\0"
};

void ImagePlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImagePlayer *_t = static_cast<ImagePlayer *>(_o);
        switch (_id) {
        case 0: _t->onImagePlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onImagePlayerChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 3: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->onMusicFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: _t->onImageFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->onVideoFilePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->onTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImagePlayer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImagePlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImagePlayer,
      qt_meta_data_ImagePlayer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImagePlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImagePlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImagePlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImagePlayer))
        return static_cast<void*>(const_cast< ImagePlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int ImagePlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ImagePlayer::onImagePlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImagePlayer::onImagePlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImagePlayer::onImagePlayerChange(const int _t1, const QString & _t2, const int _t3, const int _t4, const int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
