/****************************************************************************
** Meta object code from reading C++ file 'ScrollBar.h'
**
** Created: Wed Oct 18 10:38:00 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/Common/ScrollBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScrollBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScrollBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   40,   10,   10, 0x0a,
      79,   72,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScrollBar[] = {
    "ScrollBar\0\0persent\0scrollPersent(float)\0"
    "percent\0setScrollPercent(float)\0height\0"
    "setItemHeight(int)\0"
};

void ScrollBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScrollBar *_t = static_cast<ScrollBar *>(_o);
        switch (_id) {
        case 0: _t->scrollPersent((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 1: _t->setScrollPercent((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 2: _t->setItemHeight((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScrollBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScrollBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScrollBar,
      qt_meta_data_ScrollBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScrollBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScrollBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScrollBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScrollBar))
        return static_cast<void*>(const_cast< ScrollBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScrollBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ScrollBar::scrollPersent(const float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
