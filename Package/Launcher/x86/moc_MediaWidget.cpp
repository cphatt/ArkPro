/****************************************************************************
** Meta object code from reading C++ file 'MediaWidget.h'
**
** Created: Mon Oct 23 15:08:01 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/MediaWidget/MediaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MediaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   13,   12,   12, 0x09,
      67,   13,   12,   12, 0x09,
     105,   98,   12,   12, 0x09,
     134,   98,   12,   12, 0x09,
     163,   98,   12,   12, 0x09,
     192,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MediaWidget[] = {
    "MediaWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0status\0"
    "onImagePlayerPlayStatus(int)\0"
    "onMusicPlayerPlayStatus(int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onBmpButtonRelease()\0"
};

void MediaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MediaWidget *_t = static_cast<MediaWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onBmpButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MediaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MediaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MediaWidget,
      qt_meta_data_MediaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MediaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MediaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MediaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MediaWidget))
        return static_cast<void*>(const_cast< MediaWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< MediaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MediaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
