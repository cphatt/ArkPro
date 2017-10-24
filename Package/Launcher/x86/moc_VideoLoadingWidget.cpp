/****************************************************************************
** Meta object code from reading C++ file 'VideoLoadingWidget.h'
**
** Created: Mon Oct 23 15:07:58 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/VideoWidget/VideoLoadingWidget/VideoLoadingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoLoadingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoLoadingWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_VideoLoadingWidget[] = {
    "VideoLoadingWidget\0\0status\0"
    "onVideoPlayerPlayStatus(int)\0"
};

void VideoLoadingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoLoadingWidget *_t = static_cast<VideoLoadingWidget *>(_o);
        switch (_id) {
        case 0: _t->onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoLoadingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoLoadingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoLoadingWidget,
      qt_meta_data_VideoLoadingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoLoadingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoLoadingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoLoadingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoLoadingWidget))
        return static_cast<void*>(const_cast< VideoLoadingWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< VideoLoadingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoLoadingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
