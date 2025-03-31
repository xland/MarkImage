#include <QPainter>
#include <Util.h>
#include "BtnNumInputBtn.h"

BtnNumInputBtn::BtnNumInputBtn(const ushort& code, QWidget* parent) : QWidget(parent), code{code}
{
	setFixedSize(22, 22);
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover, true);
}

BtnNumInputBtn::~BtnNumInputBtn()
{

}

void BtnNumInputBtn::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    if (isHover) {
        painter.setBrush(QColor(210, 220, 240));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
        painter.setPen(QColor(80, 80, 80));
	}
	else {
        painter.setBrush(QColor(255, 255, 255));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
        painter.setPen(QColor(130, 130, 130));
	}
    auto font = Util::getIconFont(11);
    painter.setFont(*font);
    painter.drawText(rect(), Qt::AlignCenter, QChar(code));
}

void BtnNumInputBtn::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void BtnNumInputBtn::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void BtnNumInputBtn::mousePressEvent(QMouseEvent* event)
{
    emit click();
}
