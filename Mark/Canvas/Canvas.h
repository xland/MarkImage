#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "../Shape/Shapes.h"
#include "../Shape/ShapeRect.h"
#include "../Shape/ShapeBase.h"

class Canvas : public QWidget
{
	Q_OBJECT

public:
	Canvas(QWidget *parent = nullptr);
	~Canvas();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	void onParentResize(const int w, const int h);
private:
	int x, y, w, h;
	QImage img;
	QPixmap* imgCanvas;
	QPixmap* imgBoard;
	QPoint posPress;
	ShapeBase* shape;
};
