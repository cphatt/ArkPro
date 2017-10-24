/****************************************************************************
** Meta object code from reading C++ file 'BmpButton.h'
**
** Created: Wed Oct 18 10:37:58 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/Common/BmpButton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BmpButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BmpButton[] = {

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
      11,   10,   10,   10, 0x05,
      28,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_BmpButton[] = {
    "BmpButton\0\0bmpButtomPress()\0"
    "bmpButtonRelease()\0"
};

void BmpButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BmpButton *_t = static_cast<BmpButton *>(_o);
        switch (_id) {
        case 0: _t->bmpButtomPress(); break;
        case 1: _t->bmpButtonRelease(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BmpButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BmpButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BmpButton,
      qt_meta_data_BmpButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BmpButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BmpButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BmpButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BmpButton))
        return static_cast<void*>(const_cast< BmpButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int BmpButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void BmpButton::bmpButtomPress()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BmpButton::bmpButtonRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
