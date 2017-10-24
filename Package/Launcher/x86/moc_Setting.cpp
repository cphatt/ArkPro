/****************************************************************************
** Meta object code from reading C++ file 'Setting.h'
**
** Created: Wed Oct 18 10:37:55 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/BusinessLogic/Setting/Setting.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Setting[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,    9,    8,    8, 0x05,
      62,   53,    8,    8, 0x05,
      99,   93,    8,    8, 0x05,
     123,   93,    8,    8, 0x05,
     145,   93,    8,    8, 0x05,
     162,    8,    8,    8, 0x05,
     171,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     181,   53,    8,    8, 0x08,
     211,  203,    8,    8, 0x08,
     240,  203,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Setting[] = {
    "Setting\0\0date,time\0onDateTimeChange(QString,QString)\0"
    "language\0onLanguageTranslateChange(int)\0"
    "value\0onBrightnessChange(int)\0"
    "onContrastChange(int)\0onHueChange(int)\0"
    "onTest()\0onTest1()\0onLanguageChange(int)\0"
    "service\0onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
};

void Setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Setting *_t = static_cast<Setting *>(_o);
        switch (_id) {
        case 0: _t->onDateTimeChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onLanguageTranslateChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->onHueChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onTest(); break;
        case 6: _t->onTest1(); break;
        case 7: _t->onLanguageChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: _t->onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Setting::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Setting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Setting,
      qt_meta_data_Setting, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Setting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Setting))
        return static_cast<void*>(const_cast< Setting*>(this));
    if (!strcmp(_clname, "SettingService::Interface"))
        return static_cast< SettingService::Interface*>(const_cast< Setting*>(this));
    if (!strcmp(_clname, "DbusService::Interface"))
        return static_cast< DbusService::Interface*>(const_cast< Setting*>(this));
    return QObject::qt_metacast(_clname);
}

int Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Setting::onDateTimeChange(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Setting::onLanguageTranslateChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Setting::onBrightnessChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Setting::onContrastChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Setting::onHueChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Setting::onTest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Setting::onTest1()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
