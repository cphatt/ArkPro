/****************************************************************************
** Meta object code from reading C++ file 'MusicToolWidget.h'
**
** Created: Tue Oct 24 11:31:58 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/UserInterface/MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicToolWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x09,
      56,   49,   16,   16, 0x09,
     115,   85,   16,   16, 0x09,
     184,  156,   16,   16, 0x09,
     242,  231,   16,   16, 0x0a,
     274,  231,   16,   16, 0x0a,
     304,  231,   16,   16, 0x0a,
     338,   16,   16,   16, 0x0a,
     360,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MusicToolWidget[] = {
    "MusicToolWidget\0\0mode\0onMusicPlayerPlayMode(int)\0"
    "status\0onMusicPlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "millesimal\0onTickMarksMillesimalStart(int)\0"
    "onTickMarksMillesimalEnd(int)\0"
    "onTickMarksMillesimalChanged(int)\0"
    "onToolButtonRelease()\0onTimeout()\0"
};

const QMetaObject MusicToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicToolWidget,
      qt_meta_data_MusicToolWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicToolWidget))
        return static_cast<void*>(const_cast< MusicToolWidget*>(this));
    if (!strcmp(_clname, "Multimedia::Interface"))
        return static_cast< Multimedia::Interface*>(const_cast< MusicToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onMusicPlayerPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onMusicPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: onMusicPlayerID3TagChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 4: onTickMarksMillesimalStart((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onTickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: onTickMarksMillesimalChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: onToolButtonRelease(); break;
        case 8: onTimeout(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
