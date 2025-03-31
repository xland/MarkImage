#include "ContentBox.h"

#include "Canvas.h"
#include "./Tool/ToolBar.h"
#include "./Setting/ToolSetting.h"
#include "./Shape/ShapeLayer.h"

ContentBox::ContentBox(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar = new ToolBar(this);
	toolSetting = new ToolSetting(this);
    shapeLayer = new ShapeLayer(this);
    canvas = new Canvas(this);
    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(toolBar);
    layout->addWidget(toolSetting);
    layout->addWidget(canvas);
    layout->addWidget(shapeLayer);
    setLayout(layout);
}

ContentBox::~ContentBox()
{

}
