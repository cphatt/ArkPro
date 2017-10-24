/****************************************************************************
** Meta object code from reading C++ file 'MirrorLinkWidget.h'
**
** Created: Wed Oct 18 10:38:03 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MirrorLinkWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MirrorLinkWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   18,   17,   17, 0x09,
      72,   18,   17,   17, 0x09,
     105,  100,   17,   17, 0x08,
     145,   17,   17,   17, 0x08,
     163,  100,   17,   17, 0x08,
     185,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MirrorLinkWidget[] = {
    "MirrorLinkWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onLinkStatusChange(int,int)\0type\0"
    "onMessageWidgetChange(MessageBox::Type)\0"
    "onPopBtnRelease()\0onToolBtnRelease(int)\0"
    "onTimeout()\0"
};

void MirrorLinkWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MirrorLinkWidget *_t = static_cast<MirrorLinkWidget *>(_o);
        switch (_id) {
        case 0: _t->ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onLinkStatusChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->onMessageWidgetChange((*reinterpret_cast< const MessageBox::Type(*)>(_a[1]))); break;
        case 3: _t->onPopBtnRelease(); break;
        case 4: _t->onToolBtnRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->onTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MirrorLinkWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MirrorLinkWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MirrorLinkWidget,
      qt_meta_data_MirrorLinkWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MirrorLinkWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MirrorLinkWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MirrorLinkWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MirrorLinkWidget))
        return static_cast<void*>(const_cast< MirrorLinkWidget*>(this));
    if (!strcmp(_clname, "Widget::Interface"))
        return static_cast< Widget::Interface*>(const_cast< MirrorLinkWidget*>(this));
    if (!strcmp(_clname, "Link::Interface"))
        return static_cast< Link::Interface*>(const_cast< MirrorLinkWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MirrorLinkWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
