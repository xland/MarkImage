#pragma once
#include "ShapeBase.h"
#include <QObject>

class ShapeRect  : public ShapeBase
{
	Q_OBJECT

public:
	ShapeRect(QObject *parent);
	~ShapeRect();
	void paint(QPainter* p) override;
	void draw(QPoint& posPress,QPoint& posMove) override;
	void move(QPoint& posPress,QPoint& posMove) override;
private:
	QRect rect;
};
