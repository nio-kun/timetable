/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Oct 9 15:42:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      82,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     130,   11,   11,   11, 0x08,
     160,  154,   11,   11, 0x08,
     197,   11,   11,   11, 0x08,
     212,   11,   11,   11, 0x08,
     236,  226,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     278,   11,   11,   11, 0x08,
     290,   11,   11,   11, 0x08,
     304,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_action_2_triggered()\0"
    "on_action_triggered()\0on_action_3_triggered()\0"
    "on_action_4_triggered()\0on_action_5_triggered()\0"
    "on_action_6_triggered()\0index\0"
    "on_ttable_doubleClicked(QModelIndex)\0"
    "MakeToolbars()\0ClearTTable()\0DaysCount\0"
    "SetDays(int)\0onPrev()\0onNext()\0"
    "onOneDay()\0onTwoDays()\0onThreeDays()\0"
    "onWeek()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_action_2_triggered(); break;
        case 1: on_action_triggered(); break;
        case 2: on_action_3_triggered(); break;
        case 3: on_action_4_triggered(); break;
        case 4: on_action_5_triggered(); break;
        case 5: on_action_6_triggered(); break;
        case 6: on_ttable_doubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: MakeToolbars(); break;
        case 8: ClearTTable(); break;
        case 9: SetDays((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: onPrev(); break;
        case 11: onNext(); break;
        case 12: onOneDay(); break;
        case 13: onTwoDays(); break;
        case 14: onThreeDays(); break;
        case 15: onWeek(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
