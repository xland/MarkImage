#pragma once

#include <QWidget>

class ShapeLayerBar : public QWidget
{
	Q_OBJECT
public:
	ShapeLayerBar(QWidget *parent = nullptr);
	~ShapeLayerBar();
protected:
	void paintEvent(QPaintEvent* event);
public:
	bool isChecked{ false };
private:

};
