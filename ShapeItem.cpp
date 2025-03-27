#include <QPainter>

#include "Util.h"
#include "ShapeItem.h"

ShapeItem::ShapeItem(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(38);
    setMouseTracking(true);
    setCursor(Qt::CursorShape::PointingHandCursor);
}

ShapeItem::~ShapeItem()
{
}

void ShapeItem::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);



    if (isCheck || isHover) 
    {
        p.setPen(QColor(50, 130, 240));
    } 
    else
    {
        p.setPen(Qt::NoPen);
    }
    p.setBrush(QColor(255, 255, 255));
    p.drawRoundedRect(rect(), 3, 3);
    p.setBrush(Qt::NoBrush);
    p.setPen(isCheck? QColor(50, 130, 240):QColor(88, 88, 88));

    auto font = Util::getIconFont(13);
    p.setFont(*font);

	auto r = rect();
    r.setLeft(10);
    p.drawText(r, QChar(isCheck?0xe896:0xe894), Qt::AlignLeft | Qt::AlignVCenter);

    r.setLeft(36);
    p.drawText(r, QChar(0xe6af), Qt::AlignLeft | Qt::AlignVCenter);

    font = Util::getTextFont(13);
    p.setFont(*font);
    r.setLeft(52);
    p.drawText(r, "多边形：边框：3,填充：无", Qt::AlignLeft | Qt::AlignVCenter);
}

void ShapeItem::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void ShapeItem::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void ShapeItem::mousePressEvent(QMouseEvent* event)
{
    isCheck = !isCheck;
    update();
}
