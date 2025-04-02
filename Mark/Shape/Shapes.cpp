#include <QApplication>
#include "ShapeBase.h"
#include "Shapes.h"

Shapes* _shapes;

Shapes::Shapes(QObject *parent) : QObject(parent)
{
}

Shapes::~Shapes()
{
    qDeleteAll(shapes);
    shapes.clear();
}

Shapes* Shapes::get()
{
    if (!_shapes) {
        _shapes = new Shapes(qApp);
    }
    return _shapes;
}

void Shapes::add(ShapeBase* shape)
{
    shapes.append(shape);
}

void Shapes::removeNotReady()
{
    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (!shapes[i]->isReady) {
            delete shapes.takeAt(i);
        }
    }
}
