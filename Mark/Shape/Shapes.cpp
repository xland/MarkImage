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

void Shapes::move(QPoint& posPress, QPoint& posMove)
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        if (shapes[i]->isChecked) {
            shapes[i]->move(posPress, posMove);
        }
    }
}
