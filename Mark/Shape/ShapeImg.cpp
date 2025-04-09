#include "ShapeImg.h"

ShapeImg::ShapeImg(const QString& path, QObject *parent) : ShapeBase(parent)
{
	img.load(path);	
	shapeTypeName = "图像";
}

ShapeImg::~ShapeImg()
{

}

void ShapeImg::paint(QPainter* p)
{
	p->setPen(QPen(QBrush(QColor(255, 0, 0)), 2));
	p->setBrush(Qt::NoBrush);
	p->drawRect(rect);
}

void ShapeImg::draw(QPoint& posPress, QPoint& posMove)
{
	rect.setCoords(posPress.x(), posPress.y(), posMove.x(), posMove.y());
	rect = rect.normalized();
}

void ShapeImg::move(QPoint& posPress, QPoint& posMove)
{
	QPoint delta = posMove - posPress;
	rect.translate(delta);
	posPress = posMove;
}

void ShapeImg::drawTitle(const QRect& rect, QPainter* p)
{
	QString str = "图像";
	p->drawText(rect, str, Qt::AlignLeft | Qt::AlignVCenter);
}
