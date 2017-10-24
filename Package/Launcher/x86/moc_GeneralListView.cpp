/****************************************************************************
** Meta object code from reading C++ file 'GeneralListView.h'
**
** Created: Wed Oct 18 10:38:34 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralListView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeneralListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralListView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   17,   16,   16, 0x09,
      70,   61,   16,   16, 0x09,
     107,  101,   16,   16, 0x09,
     131,  101,   16,   16, 0x09,
     153,  101,   16,   16, 0x09,
     175,  170,   16,   16, 0x09,
     196,  191,   16,   16, 0x09,
     224,  212,   16,   16, 0x09,
     256,  248,   16,   16, 0x09,
     285,   16,   16,   16, 0x08,
     305,   16,   16,   16, 0x08,
     335,  324,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GeneralListView[] = {
    "GeneralListView\0\0date,time\0"
    "onDateTimeChange(QString,QString)\0"
    "language\0onLanguageTranslateChange(int)\0"
    "value\0onBrightnessChange(int)\0"
    "onContrastChange(int)\0onHueChange(int)\0"
    "freq\0onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "type,volume\0onVolumeChange(int,int)\0"
    "min,max\0onVolumeRangeChange(int,int)\0"
    "onMinusBtnRelease()\0onPlusBtnRelease()\0"
    "millesimal\0onTickMarksMillesimalEnd(int)\0"
};

void GeneralListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneralListView *_t = static_cast<GeneralListView *>(_o);
        switch (_id) {
        case 0: _t->onDateTimeChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onLanguageTranslateChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->onHueChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->onMinusBtnRelease(); break;
        case 10: _t->onPlusBtnRelease(); break;
        case 11: _t->onTickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GeneralListView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneralListView::staticMetaObject = {
    { &CustomListView::staticMetaObject, qt_meta_stringdata_GeneralListView,
      qt_meta_data_GeneralListView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralListView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralListView))
        return static_cast<void*>(const_cast< GeneralListView*>(this));
    if (!strcmp(_clname, "Setting::Interface"))
        return static_cast< Setting::Interface*>(const_cast< GeneralListView*>(this));
    if (!strcmp(_clname, "Audio::Interface"))
        return static_cast< Audio::Interface*>(const_cast< GeneralListView*>(this));
    return CustomListView::qt_metacast(_clname);
}

int GeneralListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
