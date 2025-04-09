#pragma once
#include "ShapeBase.h"
#include <QObject>

class ShapeImg  : public ShapeBase
{
	Q_OBJECT

public:
	ShapeImg(const QString& path, QObject *parent);
	~ShapeImg();
	void paint(QPainter* p) override;
	void draw(QPoint& posPress,QPoint& posMove) override;
	void move(QPoint& posPress,QPoint& posMove) override;
	void drawTitle(const QRect& rect, QPainter* p) override;
	QImage img;
private:
	QRect rect;
};
