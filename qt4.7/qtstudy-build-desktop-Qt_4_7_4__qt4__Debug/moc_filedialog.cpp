/****************************************************************************
** Meta object code from reading C++ file 'filedialog.h'
**
** Created: Wed Aug 10 14:13:24 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qtstudy/filedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FileDialog[] = {
    "FileDialog\0\0onClose()\0"
};

const QMetaObject FileDialog::staticMetaObject = {
    { &QFileDialog::staticMetaObject, qt_meta_stringdata_FileDialog,
      qt_meta_data_FileDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileDialog))
        return static_cast<void*>(const_cast< FileDialog*>(this));
    return QFileDialog::qt_metacast(_clname);
}

int FileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFileDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onClose(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
