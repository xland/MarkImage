#include <QPainter>
#include <QApplication>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include "CanvasBox.h"
#include "Canvas.h"

CanvasBox::CanvasBox(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvas = new Canvas(this);
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setBlurRadius(26);
    canvas->setGraphicsEffect(shadow);
    canvas->show();
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
    if (event->oldSize().isValid()) {
        auto w = width();
        auto h = height();
        auto w1 = canvas->width();
        auto h1 = canvas->height();
        auto x = (w - w1) / 2;
        auto y = (h - h1) / 2;
        canvas->move(x, y);
    }
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

void CanvasBox::showEvent(QShowEvent* event)
{
 //   ((QWidget*)parent())->layout()->update();
 //   adjustSize();
 //   canvas = new Canvas(this);
 //   auto w = width();
 //   auto h = height();
 //   auto w1 = canvas->width();
	//auto h1 = canvas->height();
 //   auto x = (w - w1) / 2;
 //   auto y = (h - h1) / 2;
 //   canvas->move(x, y);
    
}
