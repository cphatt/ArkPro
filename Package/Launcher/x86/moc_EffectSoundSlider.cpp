/****************************************************************************
** Meta object code from reading C++ file 'EffectSoundSlider.h'
**
** Created: Wed Oct 18 10:38:36 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundSlider/EffectSoundSlider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectSoundSlider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EffectSoundSlider[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      37,   18,   18,   18, 0x05,
      65,   54,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_EffectSoundSlider[] = {
    "EffectSoundSlider\0\0minusBtnRelease()\0"
    "plusBtnRelease()\0millesimal\0"
    "tickMarksMillesimalEnd(int)\0"
};

void EffectSoundSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EffectSoundSlider *_t = static_cast<EffectSoundSlider *>(_o);
        switch (_id) {
        case 0: _t->minusBtnRelease(); break;
        case 1: _t->plusBtnRelease(); break;
        case 2: _t->tickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EffectSoundSlider::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EffectSoundSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EffectSoundSlider,
      qt_meta_data_EffectSoundSlider, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectSoundSlider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectSoundSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectSoundSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectSoundSlider))
        return static_cast<void*>(const_cast< EffectSoundSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int EffectSoundSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EffectSoundSlider::minusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void EffectSoundSlider::plusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EffectSoundSlider::tickMarksMillesimalEnd(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
