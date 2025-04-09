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

void ShapeRect::draw(QPoint& posPress, QPoint& posMove)
{
	rect.setCoords(posPress.x(), posPress.y(), posMove.x(), posMove.y());
	rect = rect.normalized();
}

void ShapeRect::move(QPoint& posPress, QPoint& posMove)
{
	QPoint delta = posMove - posPress;
	rect.translate(delta);
	posPress = posMove;
}

void ShapeRect::drawTitle(const QRect& rect, QPainter* p)
{
	QString str = "矩形";
	p->drawText(rect, str, Qt::AlignLeft | Qt::AlignVCenter);
}
