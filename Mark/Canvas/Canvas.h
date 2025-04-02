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
	void changeState(const int& state);
	/// <summary>
	/// 0 初始状态
	/// 1 准备绘图
	/// 2 绘图中
	/// 3 准备改变位置
	/// 4 位置改变中
	/// </summary>
	int state{ 1 };
	int type{ 0 };
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
