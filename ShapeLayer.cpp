#include <QPainter>
#include "ShapeLayer.h"

ShapeLayer::ShapeLayer(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(200);
}

ShapeLayer::~ShapeLayer()
{
	
}

void ShapeLayer::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}
