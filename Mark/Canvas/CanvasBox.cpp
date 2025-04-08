#include <QPainter>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include "CanvasBox.h"
#include "Canvas.h"

CanvasBox::CanvasBox(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    
	canvas = new Canvas(this);

    QGraphicsDropShadowEffect* shadowFrameLogin = new QGraphicsDropShadowEffect(this);
    shadowFrameLogin->setOffset(0, 0);
    shadowFrameLogin->setColor(QColor(0,0,0,80));
    shadowFrameLogin->setBlurRadius(26);
    canvas->setGraphicsEffect(shadowFrameLogin);
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

void CanvasBox::mousePressEvent(QMouseEvent* event)
{
    QMouseEvent childEvent(event->type(),
        canvas->mapFromParent(event->pos()),
		event->globalPosition(),
        event->button(),
        event->buttons(),
        event->modifiers());
    QApplication::sendEvent(canvas, &childEvent);
}

void CanvasBox::mouseMoveEvent(QMouseEvent* event)
{
    QMouseEvent childEvent(event->type(),
        canvas->mapFromParent(event->pos()),
        event->globalPosition(),
        event->button(),
        event->buttons(),
        event->modifiers());
    QApplication::sendEvent(canvas, &childEvent);
}

void CanvasBox::mouseReleaseEvent(QMouseEvent* event)
{
    QMouseEvent childEvent(event->type(),
        canvas->mapFromParent(event->pos()),
        event->globalPosition(),
        event->button(),
        event->buttons(),
        event->modifiers());
    QApplication::sendEvent(canvas, &childEvent);
}
