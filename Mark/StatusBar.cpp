#include <QPainter>
#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(28);
}

StatusBar::~StatusBar()
{
}

void StatusBar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 238, 238));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}
