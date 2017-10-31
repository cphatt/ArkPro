/****************************************************************************
** Meta object code from reading C++ file 'SDDiskImageListViewWidget.h'
**
** Created: Tue Oct 24 11:31:50 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskImageListViewWidget/SDDiskImageListViewWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDDiskImageListViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDDiskImageListViewWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   27,   26,   26, 0x09,
      81,   27,   26,   26, 0x09,
     119,  112,   26,   26, 0x09,
     157,  148,   26,   26, 0x09,
     199,  193,   26,   26, 0x08,
     231,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SDDiskImageListViewWidget[] = {
    "SDDiskImageListViewWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0status\0"
    "onImagePlayerPlayStatus(int)\0type,xml\0"
    "onImagePlayerFileNames(int,QString)\0"
    "index\0onImageListViewItemRelease(int)\0"
    "onListBtnRelease()\0"
};

const QMetaObject SDDiskImageListViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SDDiskImageListViewWidget,
      qt_meta_data_SDDiskImageListViewWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDDiskImageListViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDDiskImageListViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDDiskImageListViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDDiskImageListViewWidget))
        return static_cast<void*>(const_cast< SDDiskImageListViewWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< SDDiskImageListViewWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< SDDiskImageListViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SDDiskImageListViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: onImagePlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: onImageListViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onListBtnRelease(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
