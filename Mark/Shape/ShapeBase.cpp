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

void ShapeBase::draw(QPoint& posPress,QPoint& posMove)
{
}

void ShapeBase::move(QPoint& posPress,QPoint& posMove)
{
}

void ShapeBase::drawTitle(const QRect& rect, QPainter* p)
{
}
