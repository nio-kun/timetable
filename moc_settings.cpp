/****************************************************************************
** Meta object code from reading C++ file 'settings.h'
**
** Created: Thu Oct 13 01:32:52 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settings[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      36,    9,    9,    9, 0x08,
      60,    9,    9,    9, 0x08,
      86,    9,    9,    9, 0x08,
     112,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_settings[] = {
    "settings\0\0on_pushButton_2_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_lineEdit_3_lostFocus()\0"
    "on_lineEdit_4_lostFocus()\0"
    "on_pushButton_3_clicked()\0"
};

const QMetaObject settings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settings,
      qt_meta_data_settings, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &settings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *settings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settings))
        return static_cast<void*>(const_cast< settings*>(this));
    return QDialog::qt_metacast(_clname);
}

int settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_2_clicked(); break;
        case 1: on_pushButton_clicked(); break;
        case 2: on_lineEdit_3_lostFocus(); break;
        case 3: on_lineEdit_4_lostFocus(); break;
        case 4: on_pushButton_3_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
