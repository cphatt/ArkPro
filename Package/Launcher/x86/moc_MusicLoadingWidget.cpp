/****************************************************************************
** Meta object code from reading C++ file 'MusicLoadingWidget.h'
**
** Created: Mon Oct 23 15:07:57 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/MusicWidget/MusicLoadingWidget/MusicLoadingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicLoadingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicLoadingWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MusicLoadingWidget[] = {
    "MusicLoadingWidget\0\0status\0"
    "onMusicPlayerPlayStatus(int)\0"
};

void MusicLoadingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MusicLoadingWidget *_t = static_cast<MusicLoadingWidget *>(_o);
        switch (_id) {
        case 0: _t->onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MusicLoadingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MusicLoadingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicLoadingWidget,
      qt_meta_data_MusicLoadingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicLoadingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicLoadingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicLoadingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicLoadingWidget))
        return static_cast<void*>(const_cast< MusicLoadingWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< MusicLoadingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicLoadingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
