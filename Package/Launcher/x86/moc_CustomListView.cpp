/****************************************************************************
** Meta object code from reading C++ file 'CustomListView.h'
**
** Created: Wed Oct 18 10:38:46 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/Common/CustomListView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomListView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x05,
      55,   16,   15,   15, 0x05,
      89,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CustomListView[] = {
    "CustomListView\0\0index\0"
    "onPressIndexChanged(QModelIndex)\0"
    "onCurrentIndexChange(QModelIndex)\0"
    "listViewItemRelease(int)\0"
};

void CustomListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomListView *_t = static_cast<CustomListView *>(_o);
        switch (_id) {
        case 0: _t->onPressIndexChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onCurrentIndexChange((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->listViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CustomListView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_CustomListView,
      qt_meta_data_CustomListView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomListView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomListView))
        return static_cast<void*>(const_cast< CustomListView*>(this));
    return QListView::qt_metacast(_clname);
}

int CustomListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
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
void CustomListView::onPressIndexChanged(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CustomListView::onCurrentIndexChange(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CustomListView::listViewItemRelease(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
