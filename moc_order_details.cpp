/****************************************************************************
** Meta object code from reading C++ file 'order_details.h'
**
** Created: Thu Oct 13 16:46:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "order_details.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'order_details.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_order_details[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      56,   44,   39,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_order_details[] = {
    "order_details\0\0on_buttonBox_accepted()\0"
    "bool\0tme,rsplace\0isEmpty(QDateTime,int)\0"
};

const QMetaObject order_details::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_order_details,
      qt_meta_data_order_details, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &order_details::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *order_details::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *order_details::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_order_details))
        return static_cast<void*>(const_cast< order_details*>(this));
    return QDialog::qt_metacast(_clname);
}

int order_details::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_accepted(); break;
        case 1: { bool _r = isEmpty((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
