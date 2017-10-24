/****************************************************************************
** Meta object code from reading C++ file 'SettingService.h'
**
** Created: Mon Oct 23 11:17:02 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingService/SettingService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingService[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      15,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // classinfo: key, value
      40,   15,

 // signals: signature, parameters, type, tag, flags
      67,   57,   56,   56, 0x05,
     110,  101,   56,   56, 0x05,
     138,  132,   56,   56, 0x05,
     162,  132,   56,   56, 0x05,
     184,  132,   56,   56, 0x05,
     201,   56,   56,   56, 0x05,
     210,   56,   56,   56, 0x05,

 // slots: signature, parameters, type, tag, flags
     220,   56,   56,   56, 0x0a,
     234,  101,   56,   56, 0x0a,
     262,  251,   56,   56, 0x0a,
     285,  251,   56,   56, 0x0a,
     306,  251,   56,   56, 0x0a,
     322,   56,   56,   56, 0x0a,
     329,   56,   56,   56, 0x0a,
     337,   56,   56,   56, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingService[] = {
    "SettingService\0Local.DbusServer.Setting\0"
    "D-Bus Interface\0\0date,time\0"
    "onDateTimeChange(QString,QString)\0"
    "language\0onLanguageChange(int)\0value\0"
    "onBrightnessChange(int)\0onContrastChange(int)\0"
    "onHueChange(int)\0onTest()\0onTest1()\0"
    "synchronize()\0setLanguage(int)\0"
    "type,value\0setBrightness(int,int)\0"
    "setContrast(int,int)\0setHue(int,int)\0"
    "test()\0test1()\0onTimeout()\0"
};

const QMetaObject SettingService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SettingService,
      qt_meta_data_SettingService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingService))
        return static_cast<void*>(const_cast< SettingService*>(this));
    return QObject::qt_metacast(_clname);
}

int SettingService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onDateTimeChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onLanguageChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: onHueChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onTest(); break;
        case 6: onTest1(); break;
        case 7: synchronize(); break;
        case 8: setLanguage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 9: setBrightness((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 10: setContrast((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 11: setHue((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 12: test(); break;
        case 13: test1(); break;
        case 14: onTimeout(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SettingService::onDateTimeChange(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingService::onLanguageChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingService::onBrightnessChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingService::onContrastChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SettingService::onHueChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SettingService::onTest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void SettingService::onTest1()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
