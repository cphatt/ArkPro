/****************************************************************************
** Meta object code from reading C++ file 'CarplayLinkProxy.h'
**
** Created: Mon Oct 23 11:18:31 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Link/CarplayLinkProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CarplayLinkProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerCarplayInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      45,   33,   32,   32, 0x05,
     102,   73,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
     163,   33,  143,   32, 0x0a,
     225,  190,  143,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerCarplayInterface[] = {
    "LocalDbusServerCarplayInterface\0\0"
    "type,status\0onLinkStatusChange(int,int)\0"
    "type,x_src,y_src,x_dst,y_dst\0"
    "onTouchStatusChange(int,int,int,int,int)\0"
    "QDBusPendingReply<>\0requestLinkStatus(int,int)\0"
    "deviceType,touchType,touchPointXml\0"
    "requestTouchStatus(int,int,QString)\0"
};

const QMetaObject LocalDbusServerCarplayInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerCarplayInterface,
      qt_meta_data_LocalDbusServerCarplayInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerCarplayInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerCarplayInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerCarplayInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerCarplayInterface))
        return static_cast<void*>(const_cast< LocalDbusServerCarplayInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerCarplayInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onLinkStatusChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: onTouchStatusChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: { QDBusPendingReply<> _r = requestLinkStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 3: { QDBusPendingReply<> _r = requestTouchStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerCarplayInterface::onLinkStatusChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerCarplayInterface::onTouchStatusChange(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
