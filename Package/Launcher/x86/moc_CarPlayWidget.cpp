/****************************************************************************
** Meta object code from reading C++ file 'CarPlayWidget.h'
**
** Created: Wed Oct 18 10:38:53 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/CarPlayWidget/CarPlayWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CarPlayWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CarPlayWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   15,   14,   14, 0x09,
      69,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CarPlayWidget[] = {
    "CarPlayWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onToolButtonRelease()\0"
};

void CarPlayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CarPlayWidget *_t = static_cast<CarPlayWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onToolButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CarPlayWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CarPlayWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CarPlayWidget,
      qt_meta_data_CarPlayWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CarPlayWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CarPlayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CarPlayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CarPlayWidget))
        return static_cast<void*>(const_cast< CarPlayWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< CarPlayWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CarPlayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
