#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QVBoxLayout>
#include <QDateTime>
#include <QPainterPath>

#include "Util.h"
#include "LayerItem.h"
#include "../Shape/ShapeBase.h"

LayerItem::LayerItem(ShapeBase* shape, QWidget *parent) : QWidget(parent),shape{shape}
{
	setFixedHeight(38);
    setMouseTracking(true);
    setCursor(Qt::CursorShape::PointingHandCursor);
}

LayerItem::~LayerItem()
{
}

void LayerItem::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    QPen pen(isCheck?QColor(50, 130, 240): QColor(180, 180, 180), 1);
    p.setPen(pen);
    if (isCheck || isHover){
        p.setBrush(QColor(220, 250, 255));
	}
	else
	{
        p.setBrush(QColor(255, 255, 255));
	}
    p.drawRect(rect());
    
    p.setBrush(Qt::NoBrush);
    p.setPen(isCheck? QColor(13, 13, 13):QColor(88, 88, 88));
    auto font = Util::getIconFont(13);
    p.setFont(*font);
    auto r = rect();
    //r.setLeft(20);
    //p.drawText(r, QChar(isCheck?0xe896:0xe894), Qt::AlignLeft | Qt::AlignVCenter);
    r.setLeft(10);
    p.drawText(r, QChar(0xe6af), Qt::AlignLeft | Qt::AlignVCenter);
    font = Util::getTextFont(13);
    p.setFont(*font);
    r.setLeft(30);
	shape->drawTitle(r, &p);
}

void LayerItem::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void LayerItem::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void LayerItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {      
        dragStartPosition = event->pos();
    }
}

void LayerItem::mouseMoveEvent(QMouseEvent* event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-draggablewidget", QByteArray());
    drag->setMimeData(mimeData);
    drag->setPixmap(grab(rect()));
    drag->setHotSpot(QPoint(width() / 2, height() / 2));
    drag->exec(Qt::MoveAction);
}

void LayerItem::mouseReleaseEvent(QMouseEvent* event)
{
    if (dragStartPosition != event->pos()) return;
    isCheck = !isCheck;
    update();
    emit onClick();
}
