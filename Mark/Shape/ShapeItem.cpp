#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QVBoxLayout>
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
    p.setPen(Qt::NoPen);
    if (isCheck || isHover){
        p.setBrush(QColor(220, 250, 255));
	}
	else
	{
        p.setBrush(QColor(255, 255, 255));
	}

    auto r = rect().adjusted(10,0,-10,0);

    p.drawRoundedRect(r,4,4);
    p.setBrush(Qt::NoBrush);
    p.setPen(isCheck? QColor(33, 33, 33):QColor(88, 88, 88));

    auto font = Util::getIconFont(13);
    p.setFont(*font);

    r.setLeft(20);
    p.drawText(r, QChar(isCheck?0xe896:0xe894), Qt::AlignLeft | Qt::AlignVCenter);

    r.setLeft(46);
    p.drawText(r, QChar(0xe6af), Qt::AlignLeft | Qt::AlignVCenter);

    font = Util::getTextFont(13);
    p.setFont(*font);
    r.setLeft(62);
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
    if (event->button() == Qt::LeftButton) {      
        dragStartPosition = event->pos();
        isCheck = !isCheck;
        update();
        emit onClick();
    }
}

void ShapeItem::mouseMoveEvent(QMouseEvent* event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-draggablewidget", QByteArray());
    drag->setMimeData(mimeData);
    drag->setPixmap(grab(rect().adjusted(10,0,-10,0)));
    drag->setHotSpot(QPoint(width() / 2, height() / 2));
    drag->exec(Qt::MoveAction);
}