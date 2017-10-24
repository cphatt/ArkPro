/****************************************************************************
** Meta object code from reading C++ file 'HomeWidget.h'
**
** Created: Mon Oct 23 11:18:36 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/HomeWidget/HomeWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HomeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HomeWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x09,
      66,   12,   11,   11, 0x09,
      97,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HomeWidget[] = {
    "HomeWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0"
    "onBmpButtonRelease()\0onTimeout()\0"
};

const QMetaObject HomeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HomeWidget,
      qt_meta_data_HomeWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HomeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HomeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HomeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HomeWidget))
        return static_cast<void*>(const_cast< HomeWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< HomeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HomeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onBmpButtonRelease(); break;
        case 3: onTimeout(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
