#include <QPainter>
#include "BtnColorSelectorList.h"

BtnColorSelectorList::BtnColorSelectorList(QWidget *parent) : QWidget(parent)
{
	//todo
}

BtnColorSelectorList::~BtnColorSelectorList()
{

}

void BtnColorSelectorList::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(QColor(255, 255, 255));
	p.setPen(QColor(88, 88, 88));
	p.drawRoundedRect(rect().right() - 124, 0, width(), height(), 3, 3);
}
