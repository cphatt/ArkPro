/****************************************************************************
** Meta object code from reading C++ file 'VideoShortCutWidget.h'
**
** Created: Tue Oct 24 11:31:55 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/VideoWidget/VideoShortCutWidget/VideoShortCutWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoShortCutWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoShortCutWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   21,   20,   20, 0x09,
      57,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoShortCutWidget[] = {
    "VideoShortCutWidget\0\0status\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onBmpButtonRelease()\0"
};

const QMetaObject VideoShortCutWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoShortCutWidget,
      qt_meta_data_VideoShortCutWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoShortCutWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoShortCutWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoShortCutWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoShortCutWidget))
        return static_cast<void*>(const_cast< VideoShortCutWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< VideoShortCutWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoShortCutWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onBmpButtonRelease(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
