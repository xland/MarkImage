#pragma once

#include <QWidget>

class ShapeBase;
class LayerItem : public QWidget
{
	Q_OBJECT

public:
	LayerItem(ShapeBase* shape,QWidget *parent = nullptr);
	~LayerItem();
signals:
	void onClick();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
public:
	bool isCheck{ false };
	int index;
	ShapeBase* shape{ nullptr };
private:
	bool isHover{ false };
	QPoint dragStartPosition;
};
