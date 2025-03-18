#include <QPainter>

#include "BtnSys.h"

BtnSys::BtnSys(const QChar& iconCode, bool isClose, QWidget* parent) : QWidget(parent), 
iconCode{ iconCode }, 
isClose{isClose}
{
    setFixedSize(40, 34);
    setMouseTracking(true);
}

BtnSys::~BtnSys()
{

}

void BtnSys::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    if (isHover) {
        painter.setBrush(isClose? QColor(230, 18, 36) :QColor(248, 248, 255));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }
    auto font = Util::getIconFont(12);
    painter.setFont(*font);
    if (isClose) {
        painter.setPen(isHover ? QColor(255, 255, 255): QColor(88, 88, 88));
    }
    else {
        painter.setPen(isHover ? QColor(0, 0, 0) : QColor(88, 88, 88));
    }
    
    painter.drawText(rect(), Qt::AlignCenter, iconCode);
}

void BtnSys::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void BtnSys::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void BtnSys::mousePressEvent(QMouseEvent* event)
{
    emit click();
}
