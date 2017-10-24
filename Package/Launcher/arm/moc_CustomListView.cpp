/****************************************************************************
** Meta object code from reading C++ file 'CustomListView.h'
**
** Created: Mon Oct 23 11:19:22 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/Common/CustomListView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomListView[] = {

 // content:
       5,       // revision
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

const QMetaObject CustomListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_CustomListView,
      qt_meta_data_CustomListView, 0 }
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
        switch (_id) {
        case 0: onPressIndexChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: onCurrentIndexChange((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: listViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
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
