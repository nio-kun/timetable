/****************************************************************************
** Meta object code from reading C++ file 'services.h'
**
** Created: Thu Oct 6 21:09:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "services.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'services.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_services[] = {

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
      10,    9,    9,    9, 0x08,
      34,    9,    9,    9, 0x08,
      64,   58,    9,    9, 0x08,
      89,    9,    9,    9, 0x08,
     113,    9,    9,    9, 0x08,
     148,  143,    9,    9, 0x08,
     191,  180,    9,    9, 0x08,
     228,    9,    9,    9, 0x08,
     254,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_services[] = {
    "services\0\0on_buttonBox_accepted()\0"
    "on_buttonBox_rejected()\0event\0"
    "closeEvent(QCloseEvent*)\0"
    "on_pushButton_clicked()\0"
    "on_lineEdit_editingFinished()\0arg1\0"
    "on_lineEdit_textEdited(QString)\0"
    "currentRow\0on_listWidget_currentRowChanged(int)\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
};

const QMetaObject services::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_services,
      qt_meta_data_services, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &services::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *services::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *services::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_services))
        return static_cast<void*>(const_cast< services*>(this));
    return QDialog::qt_metacast(_clname);
}

int services::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_accepted(); break;
        case 1: on_buttonBox_rejected(); break;
        case 2: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: on_pushButton_clicked(); break;
        case 4: on_lineEdit_editingFinished(); break;
        case 5: on_lineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_pushButton_2_clicked(); break;
        case 8: on_pushButton_3_clicked(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
