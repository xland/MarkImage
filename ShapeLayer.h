#pragma once

#include <QWidget>
#include "ShapeLayerBar.h"

class ShapeLayer : public QWidget
{
	Q_OBJECT

public:
	ShapeLayer(QWidget *parent = nullptr);
	~ShapeLayer();
protected:
	void paintEvent(QPaintEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
private:
	void itemClick();
	void barClick();
private:
	ShapeLayerBar* shapeLayerBar;
};
