/****************************************************************************
** Meta object code from reading C++ file 'SettingServiceProxy.h'
**
** Created: Mon Oct 23 11:17:03 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingService/SettingServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerSettingInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   33,   32,   32, 0x05,
      63,   33,   32,   32, 0x05,
      95,   85,   32,   32, 0x05,
     129,   33,   32,   32, 0x05,
     155,  146,   32,   32, 0x05,
     177,   32,   32,   32, 0x05,
     186,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
     227,  216,  196,   32, 0x0a,
     250,  216,  196,   32, 0x0a,
     271,  216,  196,   32, 0x0a,
     287,  146,  196,   32, 0x0a,
     304,   32,  196,   32, 0x0a,
     318,   32,  196,   32, 0x0a,
     325,   32,  196,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerSettingInterface[] = {
    "LocalDbusServerSettingInterface\0\0value\0"
    "onBrightnessChange(int)\0onContrastChange(int)\0"
    "date,time\0onDateTimeChange(QString,QString)\0"
    "onHueChange(int)\0language\0"
    "onLanguageChange(int)\0onTest()\0onTest1()\0"
    "QDBusPendingReply<>\0type,value\0"
    "setBrightness(int,int)\0setContrast(int,int)\0"
    "setHue(int,int)\0setLanguage(int)\0"
    "synchronize()\0test()\0test1()\0"
};

const QMetaObject LocalDbusServerSettingInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerSettingInterface,
      qt_meta_data_LocalDbusServerSettingInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerSettingInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerSettingInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerSettingInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerSettingInterface))
        return static_cast<void*>(const_cast< LocalDbusServerSettingInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerSettingInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onBrightnessChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onContrastChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onDateTimeChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onHueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onLanguageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onTest(); break;
        case 6: onTest1(); break;
        case 7: { QDBusPendingReply<> _r = setBrightness((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 8: { QDBusPendingReply<> _r = setContrast((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 9: { QDBusPendingReply<> _r = setHue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 10: { QDBusPendingReply<> _r = setLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 11: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 12: { QDBusPendingReply<> _r = test();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 13: { QDBusPendingReply<> _r = test1();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerSettingInterface::onBrightnessChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerSettingInterface::onContrastChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerSettingInterface::onDateTimeChange(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerSettingInterface::onHueChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalDbusServerSettingInterface::onLanguageChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalDbusServerSettingInterface::onTest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void LocalDbusServerSettingInterface::onTest1()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
