#pragma once

#include <QWidget>

class ShapeLayer : public QWidget
{
	Q_OBJECT

public:
	ShapeLayer(QWidget *parent = nullptr);
	~ShapeLayer();
protected:
	void paintEvent(QPaintEvent* event);
private:
	void itemClick();
private:
	bool isChecked{false};
};
