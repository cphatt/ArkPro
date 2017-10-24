/****************************************************************************
** Meta object code from reading C++ file 'MessageBox.h'
**
** Created: Mon Oct 23 11:18:33 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/Common/MessageBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessageBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MessageBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,
      55,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MessageBox[] = {
    "MessageBox\0\0type\0messageWidgetChange(MessageBox::Type)\0"
    "messageShowTimeout()\0onTimeOut()\0"
};

const QMetaObject MessageBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MessageBox,
      qt_meta_data_MessageBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MessageBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MessageBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MessageBox))
        return static_cast<void*>(const_cast< MessageBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int MessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: messageWidgetChange((*reinterpret_cast< const MessageBox::Type(*)>(_a[1]))); break;
        case 1: messageShowTimeout(); break;
        case 2: onTimeOut(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MessageBox::messageWidgetChange(const MessageBox::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MessageBox::messageShowTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
