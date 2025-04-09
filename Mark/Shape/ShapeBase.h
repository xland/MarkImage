#pragma once

#include <QPainter>
#include <QObject>

class ShapeBase  : public QObject
{
	Q_OBJECT

public:
	ShapeBase(QObject *parent);
	~ShapeBase();
	virtual void paint(QPainter* p);
	virtual void draw(QPoint& posPress,QPoint& posMove);
	virtual void move(QPoint& posPress,QPoint& posMove);
	virtual void drawTitle(const QRect& rect, QPainter* p);
	bool isChecked{ false };
	QString shapeTypeName;
};
