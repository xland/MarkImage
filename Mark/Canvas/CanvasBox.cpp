#include <QPainter>
#include "CanvasBox.h"
#include "Canvas.h"

CanvasBox::CanvasBox(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    
	canvas = new Canvas(this);
}

CanvasBox::~CanvasBox()
{
}

void CanvasBox::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.setBrush(QColor(255, 255, 255));
	p.setPen(Qt::NoPen);
    p.drawRect(rect());
}

void CanvasBox::resizeEvent(QResizeEvent* event)
{
    emit onResize(width(), height());    
}
