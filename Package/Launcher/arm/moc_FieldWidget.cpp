/****************************************************************************
** Meta object code from reading C++ file 'FieldWidget.h'
**
** Created: Mon Oct 23 11:18:47 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/SettingWidget/FieldWidget/FieldWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FieldWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FieldWidget[] = {

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
      25,   13,   12,   12, 0x09,
      67,   12,   12,   12, 0x08,
      79,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FieldWidget[] = {
    "FieldWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onTimeout()\0onBmpButtonRelease()\0"
};

const QMetaObject FieldWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FieldWidget,
      qt_meta_data_FieldWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FieldWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FieldWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FieldWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FieldWidget))
        return static_cast<void*>(const_cast< FieldWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FieldWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onTimeout(); break;
        case 2: onBmpButtonRelease(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
