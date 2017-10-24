/****************************************************************************
** Meta object code from reading C++ file 'MusicShortCutWidget.h'
**
** Created: Mon Oct 23 15:07:36 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/MusicWidget/MusicShortCutWidget/MusicShortCutWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicShortCutWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicShortCutWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   21,   20,   20, 0x09,
      57,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MusicShortCutWidget[] = {
    "MusicShortCutWidget\0\0status\0"
    "onMusicPlayerPlayStatus(int)\0"
    "onBmpButtonRelease()\0"
};

void MusicShortCutWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MusicShortCutWidget *_t = static_cast<MusicShortCutWidget *>(_o);
        switch (_id) {
        case 0: _t->onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->onBmpButtonRelease(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MusicShortCutWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MusicShortCutWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicShortCutWidget,
      qt_meta_data_MusicShortCutWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicShortCutWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicShortCutWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicShortCutWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicShortCutWidget))
        return static_cast<void*>(const_cast< MusicShortCutWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< MusicShortCutWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicShortCutWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
