#include "ContentBox.h"

#include "./Canvas/CanvasBox.h"
#include "./Tool/ToolBar.h"
#include "./Setting/SettingImg.h"
#include "./Setting/SettingRect.h"
#include "./Shape/ShapeLayer.h"

ContentBox::ContentBox(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar = new ToolBar(this);
	setting = new SettingImg(this);
    shapeLayer = new ShapeLayer(this);
    canvasBox = new CanvasBox(this);
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(toolBar);

    layout->addWidget(setting);

    layout->addWidget(canvasBox);
    layout->addWidget(shapeLayer);
    setLayout(layout);

	connect(toolBar, &ToolBar::toolChange, this, &ContentBox::toolChange);
}

ContentBox::~ContentBox()
{

}

void ContentBox::toolChange(int toolType)
{
	auto lay = (QHBoxLayout*)this->layout();
    lay->removeWidget(setting);
	if (setting) {
		delete setting;
		setting = nullptr;
	}
	if (toolType == 0) {
		setting = new SettingImg(this);
	}
	else if (toolType == 1) {
		setting = new SettingRect(this);
	}
	/*else if (toolType == 2) {
		setting = new SettingCircle(this);
	}
	else if (toolType == 3) {
		setting = new SettingPolygon(this);
	}
	else if (toolType == 4) {
		setting = new SettingStar(this);
	}
	else if (toolType == 5) {
		setting = new SettingArrow(this);
	}
	else if (toolType == 6) {
		setting = new SettingText(this);
	}
	else if (toolType == 7) {
		setting = new SettingPen(this);
	}
	else if (toolType == 8) {
		setting = new SettingLine(this);
	}
	else if (toolType == 9) {
		setting = new SettingText(this);
	}
	else if (toolType == 10) {
		setting = new SettingEraser(this);
	}
	else if (toolType == 11) {
		setting = new SettingMosaic(this);
	}*/
	else {
		return;
	}
	lay->insertWidget(1, setting);
}
