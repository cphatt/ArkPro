/****************************************************************************
** Meta object code from reading C++ file 'PixmapWidget.h'
**
** Created: Mon Oct 23 11:19:06 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PixmapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PixmapWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      26,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PixmapWidget[] = {
    "PixmapWidget\0\0stopTimer()\0startTimer()\0"
};

const QMetaObject PixmapWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PixmapWidget,
      qt_meta_data_PixmapWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PixmapWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PixmapWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PixmapWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PixmapWidget))
        return static_cast<void*>(const_cast< PixmapWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PixmapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stopTimer(); break;
        case 1: startTimer(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PixmapWidget::stopTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PixmapWidget::startTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
