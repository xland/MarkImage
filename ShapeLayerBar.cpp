#include <QPainter>
#include "Util.h"
#include "ShapeLayerBar.h"

ShapeLayerBar::ShapeLayerBar(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(36);
	setCursor(Qt::CursorShape::PointingHandCursor);
}

ShapeLayerBar::~ShapeLayerBar()
{

}
void ShapeLayerBar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
	p.setPen(Qt::NoPen);
    p.setBrush(QColor(210, 220, 240));
    QRect header = rect();
    p.drawRect(header);

    p.setPen(QPen(QColor(50, 130, 240), 0.5));
    p.drawLine(0, 36, width(), 36);


    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(50, 130, 240));
    auto font = Util::getIconFont(12);
    p.setFont(*font);
    header.setLeft(10);
    p.drawText(header, QChar(isChecked ? 0xe896 : 0xe894), Qt::AlignLeft | Qt::AlignVCenter);

    font = Util::getTextFont(12);
    p.setFont(*font);
    header.setLeft(28);
    p.drawText(header, "已绘元素：0", Qt::AlignLeft | Qt::AlignVCenter);
}