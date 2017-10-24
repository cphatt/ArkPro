/****************************************************************************
** Meta object code from reading C++ file 'MirrorToolWidget.h'
**
** Created: Wed Oct 18 10:38:46 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorToolWidget/MirrorToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MirrorToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MirrorToolWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MirrorToolWidget[] = {
    "MirrorToolWidget\0\0type\0toolBtnRelease(int)\0"
    "onToolBtnRelease()\0"
};

void MirrorToolWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MirrorToolWidget *_t = static_cast<MirrorToolWidget *>(_o);
        switch (_id) {
        case 0: _t->toolBtnRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->onToolBtnRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MirrorToolWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MirrorToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MirrorToolWidget,
      qt_meta_data_MirrorToolWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MirrorToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MirrorToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MirrorToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MirrorToolWidget))
        return static_cast<void*>(const_cast< MirrorToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MirrorToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MirrorToolWidget::toolBtnRelease(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
