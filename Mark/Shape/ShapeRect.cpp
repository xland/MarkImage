#include "ShapeRect.h"

ShapeRect::ShapeRect(QObject *parent) : ShapeBase(parent)
{

}

ShapeRect::~ShapeRect()
{

}

void ShapeRect::paint(QPainter* p)
{
	p->setPen(QPen(QBrush(QColor(255, 0, 0)), 2));
	p->setBrush(Qt::NoBrush);
	p->drawRect(rect);
}

void ShapeRect::draw(const QPoint& posPress, const QPoint& posMove)
{
	rect.setCoords(posPress.x(), posPress.y(), posMove.x(), posMove.y());
	rect = rect.normalized();
}
