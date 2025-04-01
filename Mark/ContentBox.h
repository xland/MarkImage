#pragma once

#include <QWidget>
#include <QHBoxLayout>

class ToolBar;
class ToolSetting;
class ShapeLayer;
class CanvasBox;

class ContentBox : public QWidget
{
	Q_OBJECT

public:
	ContentBox(QWidget *parent = nullptr);
	~ContentBox();

private:
	ToolBar* toolBar;
	ToolSetting* toolSetting;
	ShapeLayer* shapeLayer;
	CanvasBox* canvasBox;
	QHBoxLayout* layout;
};
