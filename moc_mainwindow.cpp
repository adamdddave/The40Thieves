/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 1),
QT_MOC_LITERAL(4, 26, 11),
QT_MOC_LITERAL(5, 38, 5),
QT_MOC_LITERAL(6, 44, 4),
QT_MOC_LITERAL(7, 49, 13),
QT_MOC_LITERAL(8, 63, 6),
QT_MOC_LITERAL(9, 70, 12),
QT_MOC_LITERAL(10, 83, 5),
QT_MOC_LITERAL(11, 89, 7),
QT_MOC_LITERAL(12, 97, 21),
QT_MOC_LITERAL(13, 119, 9),
QT_MOC_LITERAL(14, 129, 16),
QT_MOC_LITERAL(15, 146, 23),
QT_MOC_LITERAL(16, 170, 17),
QT_MOC_LITERAL(17, 188, 5),
QT_MOC_LITERAL(18, 194, 5)
    },
    "MainWindow\0test_signal\0\0i\0UpdatePlots\0"
    "TH2D*\0plot\0UpdateCluster\0TH1F**\0"
    "clusterPlots\0TH2F*\0clusADC\0"
    "on_pushButton_clicked\0test_slot\0"
    "UpdateViewerSlot\0on_pushButton_2_clicked\0"
    "UpdateClusterSlot\0plots\0plot2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       7,    2,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   65,    2, 0x08 /* Private */,
      13,    1,   66,    2, 0x08 /* Private */,
      14,    1,   69,    2, 0x08 /* Private */,
      15,    0,   72,    2, 0x08 /* Private */,
      16,    2,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,   17,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->test_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->UpdatePlots((*reinterpret_cast< TH2D*(*)>(_a[1]))); break;
        case 2: _t->UpdateCluster((*reinterpret_cast< TH1F**(*)>(_a[1])),(*reinterpret_cast< TH2F*(*)>(_a[2]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->test_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->UpdateViewerSlot((*reinterpret_cast< TH2D*(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->UpdateClusterSlot((*reinterpret_cast< TH1F**(*)>(_a[1])),(*reinterpret_cast< TH2F*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::test_signal)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(TH2D * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::UpdatePlots)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(TH1F * * , TH2F * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::UpdateCluster)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::test_signal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::UpdatePlots(TH2D * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::UpdateCluster(TH1F * * _t1, TH2F * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
