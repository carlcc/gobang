/****************************************************************************
** Meta object code from reading C++ file 'gamegrid.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamegrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamegrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      21,    9,    9,    9, 0x0a,
      33,    9,    9,    9, 0x0a,
      46,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameGrid[] = {
    "GameGrid\0\0stopGame()\0startGame()\0"
    "startGame2()\0undo()\0"
};

void GameGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameGrid *_t = static_cast<GameGrid *>(_o);
        switch (_id) {
        case 0: _t->stopGame(); break;
        case 1: _t->startGame(); break;
        case 2: _t->startGame2(); break;
        case 3: _t->undo(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GameGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameGrid::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameGrid,
      qt_meta_data_GameGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameGrid))
        return static_cast<void*>(const_cast< GameGrid*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
