/****************************************************************************
** Meta object code from reading C++ file 'CarlifeLinkProxy.h'
**
** Created: Wed Oct 18 10:38:50 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Link/CarlifeLinkProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CarlifeLinkProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerAndroidCarlifeInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      52,   40,   39,   39, 0x05,

 // slots: signature, parameters, type, tag, flags
     100,   39,   80,   39, 0x0a,
     120,  115,   80,   39, 0x0a,
     141,   40,   80,   39, 0x0a,
     203,  168,   80,   39, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerAndroidCarlifeInterface[] = {
    "LocalDbusServerAndroidCarlifeInterface\0"
    "\0type,status\0onLinkStatusChange(int,int)\0"
    "QDBusPendingReply<>\0onExitSignal()\0"
    "type\0requestKeyValue(int)\0"
    "requestLinkStatus(int,int)\0"
    "deviceType,touchType,touchPointXml\0"
    "requestTouchStatus(int,int,QString)\0"
};

void LocalDbusServerAndroidCarlifeInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LocalDbusServerAndroidCarlifeInterface *_t = static_cast<LocalDbusServerAndroidCarlifeInterface *>(_o);
        switch (_id) {
        case 0: _t->onLinkStatusChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: { QDBusPendingReply<> _r = _t->onExitSignal();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 2: { QDBusPendingReply<> _r = _t->requestKeyValue((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 3: { QDBusPendingReply<> _r = _t->requestLinkStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 4: { QDBusPendingReply<> _r = _t->requestTouchStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LocalDbusServerAndroidCarlifeInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LocalDbusServerAndroidCarlifeInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerAndroidCarlifeInterface,
      qt_meta_data_LocalDbusServerAndroidCarlifeInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerAndroidCarlifeInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerAndroidCarlifeInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerAndroidCarlifeInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerAndroidCarlifeInterface))
        return static_cast<void*>(const_cast< LocalDbusServerAndroidCarlifeInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerAndroidCarlifeInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerAndroidCarlifeInterface::onLinkStatusChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
