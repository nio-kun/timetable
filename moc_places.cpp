/****************************************************************************
** Meta object code from reading C++ file 'places.h'
**
** Created: Thu Oct 6 21:09:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "places.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'places.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_places[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      43,   32,    7,    7, 0x08,
      80,    7,    7,    7, 0x08,
     106,    7,    7,    7, 0x08,
     119,  115,    7,    7, 0x08,
     156,  153,    7,    7, 0x08,
     186,    7,    7,    7, 0x08,
     218,    7,    7,    7, 0x08,
     242,    7,    7,    7, 0x08,
     272,  266,    7,    7, 0x08,
     297,    7,    7,    7, 0x08,
     323,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_places[] = {
    "places\0\0on_pushButton_clicked()\0"
    "currentRow\0on_listWidget_currentRowChanged(int)\0"
    "on_pushButton_2_clicked()\0reject()\0"
    "str\0on_lineEdit_3_textEdited(QString)\0"
    "st\0on_checkBox_stateChanged(int)\0"
    "on_lineEdit_3_editingFinished()\0"
    "on_buttonBox_accepted()\0on_buttonBox_rejected()\0"
    "event\0closeEvent(QCloseEvent*)\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
};

const QMetaObject places::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_places,
      qt_meta_data_places, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &places::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *places::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *places::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_places))
        return static_cast<void*>(const_cast< places*>(this));
    return QDialog::qt_metacast(_clname);
}

int places::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_clicked(); break;
        case 1: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_pushButton_2_clicked(); break;
        case 3: reject(); break;
        case 4: on_lineEdit_3_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_lineEdit_3_editingFinished(); break;
        case 7: on_buttonBox_accepted(); break;
        case 8: on_buttonBox_rejected(); break;
        case 9: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 10: on_pushButton_3_clicked(); break;
        case 11: on_pushButton_4_clicked(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
