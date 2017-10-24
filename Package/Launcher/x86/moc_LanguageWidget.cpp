/****************************************************************************
** Meta object code from reading C++ file 'LanguageWidget.h'
**
** Created: Wed Oct 18 10:38:14 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/SettingWidget/LanguageWidget/LanguageWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LanguageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LanguageWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   16,   15,   15, 0x09,
      80,   70,   15,   15, 0x09,
     123,  114,   15,   15, 0x09,
     160,  154,   15,   15, 0x09,
     184,  154,   15,   15, 0x09,
     206,  154,   15,   15, 0x09,
     234,  223,   15,   15, 0x09,
     280,  258,   15,   15, 0x09,
     312,   15,   15,   15, 0x09,
     321,   15,   15,   15, 0x09,
     331,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LanguageWidget[] = {
    "LanguageWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "date,time\0onDateTimeChange(QString,QString)\0"
    "language\0onLanguageTranslateChange(int)\0"
    "value\0onBrightnessChange(int)\0"
    "onContrastChange(int)\0onHueChange(int)\0"
    "type,value\0onVolumeChange(int,int)\0"
    "type,hight,middle,low\0"
    "onEffectChange(int,int,int,int)\0"
    "onTest()\0onTest1()\0onToolButtonRelease()\0"
};

void LanguageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LanguageWidget *_t = static_cast<LanguageWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onDateTimeChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->onLanguageTranslateChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onHueChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->onVolumeChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->onEffectChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 8: _t->onTest(); break;
        case 9: _t->onTest1(); break;
        case 10: _t->onToolButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LanguageWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LanguageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LanguageWidget,
      qt_meta_data_LanguageWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LanguageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LanguageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LanguageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LanguageWidget))
        return static_cast<void*>(const_cast< LanguageWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< LanguageWidget*>(this));
    if (!strcmp(_clname, "Setting::Interface"))
        return static_cast< Setting::Interface*>(const_cast< LanguageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LanguageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
