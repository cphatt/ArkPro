/****************************************************************************
** Meta object code from reading C++ file 'USBDiskImageListViewWidget.h'
**
** Created: Mon Oct 23 15:07:43 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskImageListViewWidget/USBDiskImageListViewWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'USBDiskImageListViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_USBDiskImageListViewWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   28,   27,   27, 0x09,
      82,   28,   27,   27, 0x09,
     122,  113,   27,   27, 0x09,
     165,  158,   27,   27, 0x09,
     229,  194,   27,   27, 0x09,
     280,  274,   27,   27, 0x08,
     312,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_USBDiskImageListViewWidget[] = {
    "USBDiskImageListViewWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0type,xml\0"
    "onImagePlayerFileNames(int,QString)\0"
    "status\0onImagePlayerPlayStatus(int)\0"
    "type,filePath,index,percent,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "index\0onImageListViewItemRelease(int)\0"
    "onListBtnRelease()\0"
};

void USBDiskImageListViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        USBDiskImageListViewWidget *_t = static_cast<USBDiskImageListViewWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->onImagePlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->onImagePlayerChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 5: _t->onImageListViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->onListBtnRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData USBDiskImageListViewWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject USBDiskImageListViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_USBDiskImageListViewWidget,
      qt_meta_data_USBDiskImageListViewWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &USBDiskImageListViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *USBDiskImageListViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *USBDiskImageListViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_USBDiskImageListViewWidget))
        return static_cast<void*>(const_cast< USBDiskImageListViewWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< USBDiskImageListViewWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< USBDiskImageListViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int USBDiskImageListViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
