/****************************************************************************
** Meta object code from reading C++ file 'users.h'
**
** Created: Sun Oct 9 15:42:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "users.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'users.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_users[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,    7,    6,    6, 0x08,
      55,    6,    6,    6, 0x08,
      81,    6,    6,    6, 0x08,
     105,    6,    6,    6, 0x08,
     131,    6,    6,    6, 0x08,
     155,    6,    6,    6, 0x08,
     185,  179,    6,    6, 0x08,
     210,    6,    6,    6, 0x08,
     244,    6,    6,    6, 0x08,
     276,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_users[] = {
    "users\0\0currentRow\0"
    "on_listWidget_currentRowChanged(int)\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_buttonBox_accepted()\0on_buttonBox_rejected()\0"
    "event\0closeEvent(QCloseEvent*)\0"
    "on_lineEdit_3_textEdited(QString)\0"
    "on_lineEdit_textEdited(QString)\0"
    "on_lineEdit_2_textEdited(QString)\0"
};

const QMetaObject users::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_users,
      qt_meta_data_users, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &users::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *users::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *users::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_users))
        return static_cast<void*>(const_cast< users*>(this));
    return QDialog::qt_metacast(_clname);
}

int users::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_pushButton_3_clicked(); break;
        case 2: on_pushButton_clicked(); break;
        case 3: on_pushButton_2_clicked(); break;
        case 4: on_buttonBox_accepted(); break;
        case 5: on_buttonBox_rejected(); break;
        case 6: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 7: on_lineEdit_3_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: on_lineEdit_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: on_lineEdit_2_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
