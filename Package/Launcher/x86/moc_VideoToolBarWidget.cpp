/****************************************************************************
** Meta object code from reading C++ file 'VideoToolBarWidget.h'
**
** Created: Mon Oct 23 15:07:39 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/VideoWidget/VideoToolBarWidget/VideoToolBarWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoToolBarWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoToolBarWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x09,
      81,   74,   19,   19, 0x09,
     110,   74,   19,   19, 0x09,
     167,  139,   19,   19, 0x09,
     243,  213,   19,   19, 0x09,
     284,   19,   19,   19, 0x08,
     317,  306,   19,   19, 0x08,
     349,  306,   19,   19, 0x08,
     379,  306,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoToolBarWidget[] = {
    "VideoToolBarWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "status\0onVideoPlayerShowStatus(int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "type,index,fileName,endTime\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "onToolButtonRelease()\0millesimal\0"
    "onTickMarksMillesimalStart(int)\0"
    "onTickMarksMillesimalEnd(int)\0"
    "onTickMarksMillesimalChange(int)\0"
};

void VideoToolBarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoToolBarWidget *_t = static_cast<VideoToolBarWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onVideoPlayerShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onVideoPlayerInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 4: _t->onVideoPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: _t->onToolButtonRelease(); break;
        case 6: _t->onTickMarksMillesimalStart((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->onTickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: _t->onTickMarksMillesimalChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoToolBarWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoToolBarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoToolBarWidget,
      qt_meta_data_VideoToolBarWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoToolBarWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoToolBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoToolBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoToolBarWidget))
        return static_cast<void*>(const_cast< VideoToolBarWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< VideoToolBarWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< VideoToolBarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoToolBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
