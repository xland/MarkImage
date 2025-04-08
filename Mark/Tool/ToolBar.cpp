#include <QPainter>
#include <QVBoxLayout>

#include "ToolBar.h"
#include "BtnTool.h"
#include "../Canvas/Canvas.h"

ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
	setFixedWidth(80);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new BtnTool("图像", 0xe87d, 0, this, true));
    layout->addWidget(new BtnTool("矩形", 0xe8e8,1, this));
    layout->addWidget(new BtnTool("圆形", 0xe6bc,2, this));
    layout->addWidget(new BtnTool("多边形", 0xe6af, 3, this));
    layout->addWidget(new BtnTool("星形", 0xe6b3, 4, this));
    layout->addWidget(new BtnTool("箭头", 0xe603, 5, this));
    layout->addWidget(new BtnTool("标号", 0xe776, 6, this));
    layout->addWidget(new BtnTool("画笔", 0xe601, 7, this));
    layout->addWidget(new BtnTool("折线", 0xe80b, 8, this));
    layout->addWidget(new BtnTool("文字", 0xe6ec, 9, this));
    layout->addWidget(new BtnTool("橡皮擦", 0xe6be, 10, this));
    layout->addWidget(new BtnTool("马赛克", 0xe82e, 11, this));
    layout->addStretch();
    setLayout(layout);

}

ToolBar::~ToolBar()
{

}

void ToolBar::btnClick()
{
    auto btn = static_cast<BtnTool*>(sender());
	if (btn->isSelected) return;
	auto layout = this->layout();
    for (int i = 0; i < layout->count(); ++i) {
        auto item =  static_cast<BtnTool*>(layout->itemAt(i)->widget()); // 获取第 i 个项
        if (!item) continue;
		if (item->isSelected) {
			item->isSelected = false;
			item->update();
            break;
		}
    }
    btn->isSelected = true;
    btn->update();
	emit toolChange(btn->type);
}

void ToolBar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(210, 220, 240));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}

void ToolBar::showEvent(QShowEvent* event)
{
}
