/****************************************************************************
** Meta object code from reading C++ file 'Link.h'
**
** Created: Mon Oct 23 11:18:30 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Link/Link.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Link.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Link[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,    6,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   46,    5,    5, 0x08,
      83,   46,    5,    5, 0x08,
     114,    6,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Link[] = {
    "Link\0\0type,status\0onLinkStatusChange(int,int)\0"
    "service\0onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
    "linkStatusChange(int,int)\0"
};

const QMetaObject Link::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Link,
      qt_meta_data_Link, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Link::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Link::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Link::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Link))
        return static_cast<void*>(const_cast< Link*>(this));
    if (!strcmp(_clname, "DbusService::Interface"))
        return static_cast< DbusService::Interface*>(const_cast< Link*>(this));
    return QObject::qt_metacast(_clname);
}

int Link::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onLinkStatusChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: linkStatusChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Link::onLinkStatusChange(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
