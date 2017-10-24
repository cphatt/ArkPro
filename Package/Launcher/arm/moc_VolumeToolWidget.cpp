/****************************************************************************
** Meta object code from reading C++ file 'VolumeToolWidget.h'
**
** Created: Mon Oct 23 11:19:15 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolumeToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VolumeToolWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   28,   17,   17, 0x09,
      54,   49,   17,   17, 0x09,
      82,   70,   17,   17, 0x09,
     114,  106,   17,   17, 0x09,
     160,  143,   17,   17, 0x09,
     202,   17,   17,   17, 0x08,
     222,   17,   17,   17, 0x08,
     252,  241,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VolumeToolWidget[] = {
    "VolumeToolWidget\0\0clicked()\0freq\0"
    "onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "type,volume\0onVolumeChange(int,int)\0"
    "min,max\0onVolumeRangeChange(int,int)\0"
    "type,buffer,size\0"
    "onMCUDataRecv(Port::Type,const char*,int)\0"
    "onMinusBtnRelease()\0onPlusBtnRelease()\0"
    "millesimal\0onTickMarksMillesimalEnd(int)\0"
};

const QMetaObject VolumeToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VolumeToolWidget,
      qt_meta_data_VolumeToolWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VolumeToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VolumeToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VolumeToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VolumeToolWidget))
        return static_cast<void*>(const_cast< VolumeToolWidget*>(this));
    if (!strcmp(_clname, "Audio::Interface"))
        return static_cast< Audio::Interface*>(const_cast< VolumeToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VolumeToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: onMCUDataRecv((*reinterpret_cast< const Port::Type(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 6: onMinusBtnRelease(); break;
        case 7: onPlusBtnRelease(); break;
        case 8: onTickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void VolumeToolWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
