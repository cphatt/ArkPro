/****************************************************************************
** Meta object code from reading C++ file 'DateTimeWidget.h'
**
** Created: Wed Oct 18 10:38:53 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DateTimeWidget/DateTimeWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DateTimeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DateTimeWidget[] = {

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
      16,   15,   15,   15, 0x09,
      43,   31,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DateTimeWidget[] = {
    "DateTimeWidget\0\0OkBtnRelease()\0"
    "type,status\0ontWidgetTypeChange(Widget::Type,QString)\0"
};

void DateTimeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DateTimeWidget *_t = static_cast<DateTimeWidget *>(_o);
        switch (_id) {
        case 0: _t->OkBtnRelease(); break;
        case 1: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DateTimeWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DateTimeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DateTimeWidget,
      qt_meta_data_DateTimeWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DateTimeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DateTimeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DateTimeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateTimeWidget))
        return static_cast<void*>(const_cast< DateTimeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DateTimeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
