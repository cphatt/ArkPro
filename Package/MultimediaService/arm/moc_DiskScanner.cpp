/****************************************************************************
** Meta object code from reading C++ file 'DiskScanner.h'
**
** Created: Mon Oct 23 11:17:11 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/DeviceWatcher/DiskScanner/DiskScanner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiskScanner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DiskScanner[] = {

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
      13,   12,   12,   12, 0x05,
      33,   22,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   12,   12,   12, 0x08,
      66,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DiskScanner[] = {
    "DiskScanner\0\0finish()\0path,index\0"
    "filePath(QString,int)\0onFinish()\0"
    "onTimeout()\0"
};

const QMetaObject DiskScanner::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DiskScanner,
      qt_meta_data_DiskScanner, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DiskScanner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DiskScanner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DiskScanner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DiskScanner))
        return static_cast<void*>(const_cast< DiskScanner*>(this));
    return QObject::qt_metacast(_clname);
}

int DiskScanner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finish(); break;
        case 1: filePath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onFinish(); break;
        case 3: onTimeout(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DiskScanner::finish()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DiskScanner::filePath(const QString & _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
