#pragma once

#include <QWidget>
#include <QHBoxLayout>

class ToolBar;
class SettingBase;
class ShapeLayer;
class CanvasBox;

class ContentBox : public QWidget
{
	Q_OBJECT

public:
	ContentBox(QWidget *parent = nullptr);
	~ContentBox();

private:
	void toolChange(int toolType);
	ToolBar* toolBar;
	SettingBase* setting;
	ShapeLayer* shapeLayer;
	CanvasBox* canvasBox;
};
