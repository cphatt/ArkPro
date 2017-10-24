/****************************************************************************
** Meta object code from reading C++ file 'USBDiskToolWidget.h'
**
** Created: Mon Oct 23 11:18:57 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskToolWidget/USBDiskToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'USBDiskToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_USBDiskToolWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   19,   18,   18, 0x09,
      73,   19,   18,   18, 0x09,
     104,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_USBDiskToolWidget[] = {
    "USBDiskToolWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0"
    "onToolButtonRelease()\0"
};

const QMetaObject USBDiskToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_USBDiskToolWidget,
      qt_meta_data_USBDiskToolWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &USBDiskToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *USBDiskToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *USBDiskToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_USBDiskToolWidget))
        return static_cast<void*>(const_cast< USBDiskToolWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< USBDiskToolWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< USBDiskToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int USBDiskToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
