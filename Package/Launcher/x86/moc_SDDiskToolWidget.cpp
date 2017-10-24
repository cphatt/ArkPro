/****************************************************************************
** Meta object code from reading C++ file 'SDDiskToolWidget.h'
**
** Created: Mon Oct 23 15:07:52 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskToolWidget/SDDiskToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDDiskToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDDiskToolWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   18,   17,   17, 0x09,
      72,   18,   17,   17, 0x09,
     103,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SDDiskToolWidget[] = {
    "SDDiskToolWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0"
    "onToolButtonRelease()\0"
};

void SDDiskToolWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SDDiskToolWidget *_t = static_cast<SDDiskToolWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->onToolButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SDDiskToolWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SDDiskToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SDDiskToolWidget,
      qt_meta_data_SDDiskToolWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDDiskToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDDiskToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDDiskToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDDiskToolWidget))
        return static_cast<void*>(const_cast< SDDiskToolWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< SDDiskToolWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< SDDiskToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SDDiskToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
