/****************************************************************************
** Meta object code from reading C++ file 'ImageLoadingWidget.h'
**
** Created: Mon Oct 23 15:07:59 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/ImageWidget/ImageLoadingWidget/ImageLoadingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageLoadingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageLoadingWidget[] = {

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

static const char qt_meta_stringdata_ImageLoadingWidget[] = {
    "ImageLoadingWidget\0\0status\0"
    "onImagePlayerPlayStatus(int)\0"
};

void ImageLoadingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageLoadingWidget *_t = static_cast<ImageLoadingWidget *>(_o);
        switch (_id) {
        case 0: _t->onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageLoadingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageLoadingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageLoadingWidget,
      qt_meta_data_ImageLoadingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageLoadingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageLoadingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageLoadingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageLoadingWidget))
        return static_cast<void*>(const_cast< ImageLoadingWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< ImageLoadingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageLoadingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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