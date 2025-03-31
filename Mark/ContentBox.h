#pragma once

#include <QWidget>
#include <QHBoxLayout>

class ToolBar;
class ToolSetting;
class ShapeLayer;
class Canvas;

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
	Canvas* canvas;
	QHBoxLayout* layout;
};
