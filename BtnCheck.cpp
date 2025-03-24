#include <QPainter>
#include <QMouseEvent>
#include "BtnCheck.h"
#include "Util.h"

BtnCheck::BtnCheck(const QString& text, bool isChecked, QWidget *parent) : QWidget(parent)
, text{ text }, isChecked{ isChecked }
{
	setFixedHeight(22);
}

BtnCheck::~BtnCheck()
{
}

void BtnCheck::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(Qt::NoBrush);
	if (isChecked) {
		p.setPen(QColor(50, 130, 240));
	}
	else {
		p.setPen(QColor(120, 120, 120));
	}	
	auto font = Util::getTextFont(13);
	p.setFont(*font);
	p.drawText(rect().adjusted(26, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);  //e70f

	font = Util::getIconFont(13);
	p.setFont(*font);
	p.drawText(rect().adjusted(6, 0, 0, 0), 
		Qt::AlignLeft | Qt::AlignVCenter, 
		isChecked?QChar(0xe6c7): QChar(0xe6c6));
}

void BtnCheck::enterEvent(QEnterEvent* event)
{
}

void BtnCheck::leaveEvent(QEvent* event)
{
}

void BtnCheck::mousePressEvent(QMouseEvent* event)
{
}
