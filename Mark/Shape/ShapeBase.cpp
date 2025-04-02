#include "ShapeBase.h"

ShapeBase::ShapeBase(QObject *parent) : QObject(parent)
{

}

ShapeBase::~ShapeBase()
{

}

void ShapeBase::paint(QPainter* p)
{
}

void ShapeBase::draw(const QPoint& posPress, const QPoint& posMove)
{
}
