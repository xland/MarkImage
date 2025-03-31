#pragma once

#include <QWidget>

class ShapeLayerBar : public QWidget
{
	Q_OBJECT
public:
	ShapeLayerBar(QWidget *parent = nullptr);
	~ShapeLayerBar();
signals:
	void onClick();
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event) override;
public:
	bool isChecked{ false };
private:

};
