/****************************************************************************
** Meta object code from reading C++ file 'USBDiskMusicListViewWidget.h'
**
** Created: Mon Oct 23 11:18:53 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'USBDiskMusicListViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_USBDiskMusicListViewWidget[] = {

 // content:
       5,       // revision
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
     200,  194,   27,   27, 0x08,
     232,   27,   27,   27, 0x08,
     254,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_USBDiskMusicListViewWidget[] = {
    "USBDiskMusicListViewWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0type,xml\0"
    "onMusicPlayerFileNames(int,QString)\0"
    "status\0onMusicPlayerPlayStatus(int)\0"
    "index\0onMusicListViewItemRelease(int)\0"
    "onToolButtonRelease()\0onTimeOut()\0"
};

const QMetaObject USBDiskMusicListViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_USBDiskMusicListViewWidget,
      qt_meta_data_USBDiskMusicListViewWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &USBDiskMusicListViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *USBDiskMusicListViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *USBDiskMusicListViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_USBDiskMusicListViewWidget))
        return static_cast<void*>(const_cast< USBDiskMusicListViewWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< USBDiskMusicListViewWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< USBDiskMusicListViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int USBDiskMusicListViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onMusicPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: onMusicListViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onToolButtonRelease(); break;
        case 6: onTimeOut(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
