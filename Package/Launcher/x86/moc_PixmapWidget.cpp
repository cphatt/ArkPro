/****************************************************************************
** Meta object code from reading C++ file 'PixmapWidget.h'
**
** Created: Wed Oct 18 10:38:30 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PixmapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PixmapWidget[] = {

 // content:
       6,       // revision
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

void PixmapWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PixmapWidget *_t = static_cast<PixmapWidget *>(_o);
        switch (_id) {
        case 0: _t->stopTimer(); break;
        case 1: _t->startTimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PixmapWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PixmapWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PixmapWidget,
      qt_meta_data_PixmapWidget, &staticMetaObjectExtraData }
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
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
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
