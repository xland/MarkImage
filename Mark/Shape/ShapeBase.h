#pragma once

#include <QPainter>
#include <QObject>

class ShapeBase  : public QObject
{
	Q_OBJECT

public:
	ShapeBase(QObject *parent);
	~ShapeBase();
	bool isReady{ false };
	virtual void paint(QPainter* p);
	virtual void draw(const QPoint& posPress,const QPoint& posMove);
};
