#include <QPainter>

#include "Util.h"
#include "BtnTool.h"
#include "ToolBar.h"


BtnTool::BtnTool(const QString& text, const uint& code, int type, QWidget* parent, bool isSelected) : QWidget(parent),
	text{ text }, code{ code }, type{type}, isSelected{ isSelected }
{
	setFixedSize(80, 60);
	connect(this, &BtnTool::click, (ToolBar*)parent, &ToolBar::btnClick);
}

BtnTool::~BtnTool()
{

}

void BtnTool::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	if (isSelected) {
		painter.setBrush(QColor(238, 242, 255));
		painter.setPen(Qt::NoPen);
		painter.drawRect(rect());
		painter.setPen(QColor(50, 130, 240));
	}
	else if (isHover) {
		painter.setPen(QColor(50, 130, 240));
	}
	else {
		painter.setPen(QColor(88, 88, 88));
	}
	auto font = Util::getIconFont(16);
	painter.setFont(*font);
	painter.drawText(rect().adjusted(0,0,0,-18), Qt::AlignCenter, QChar(code));

	font = Util::getTextFont(12);
	painter.setFont(*font);
	painter.drawText(rect().adjusted(0, 20, 0, 0), Qt::AlignCenter, text);
}

void BtnTool::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void BtnTool::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void BtnTool::mousePressEvent(QMouseEvent* event)
{
    emit click();
}
