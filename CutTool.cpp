#include <Windows.h>
#include <QPainter>
#include <QPainterPath>
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <QToolTip>

#include "ScreenCapture.h"
#include "Util.h"
#include "CutTool.h"

CutTool::CutTool(bool disablePin, QWidget* parent) : QWidget(parent), disablePin{ disablePin }
{
	if (disablePin) {
		setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	}
	setMouseTracking(true);
	setFixedSize(156, 32);
	setAutoFillBackground(false);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setCursor(Qt::PointingHandCursor);
}

CutTool::~CutTool()
{
	
}

void CutTool::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(QColor(255, 255, 255));
	p.setPen(QPen(QBrush(QColor(22, 118, 255)), 1));
	p.drawRoundedRect(rect().adjusted(1,1,-1,-1), 2, 2);
	auto font = Util::getIconFont(14);
	QList<QChar> arr({ QChar(0xe606),QChar(0xe866), QChar(0xe87f), QChar(0xe6a3), QChar(0xe642) });
	for (size_t i = 0; i < 5; i++)
	{
		QRect r(3+30*i, 1, 30, 30);
		QColor textColor(38, 56, 38);
		if (i == hoverIndex ) {
			if (!(i == 3 && disablePin)) {
				p.setBrush(QColor(228, 238, 255));
				p.setPen(Qt::NoPen);
				p.drawRoundedRect(r.adjusted(2, 4, -2, -4), 4, 4);
				textColor.setRgb(9, 88, 217);
			}
		}
		p.setFont(*font);
		p.setBrush(Qt::NoBrush);
		p.setPen((i == 3 && disablePin) ? QColor(188, 188, 188) : textColor);
		p.drawText(r, Qt::AlignCenter, arr[i]);
	}
}

void CutTool::mousePressEvent(QMouseEvent* event)
{
	if (hoverIndex == 0) {
		emit onClose();
	}
	else if (hoverIndex == 1) {
		emit onSaveFile();
	}
	else if (hoverIndex == 2) {
		emit onSaveClipboard();
	}
	else if (hoverIndex == 3) {
		if (disablePin) return;
		emit onPinImg();
	}
	else if (hoverIndex == 4) {
		emit onEditImg();
	}
}

void CutTool::mouseMoveEvent(QMouseEvent* event)
{
	auto pos = event->pos();
	if (pos.y() > 2 && pos.y() < height() - 2) {
		for (size_t i = 0; i < 5; i++)
		{
			auto xPos{ 3 + 30 * i };
			if (pos.x() > xPos && pos.x() < xPos + 30) {
				if (i != hoverIndex) {
					hoverIndex = i;
					showToolTip();
					update();
					break;
				}				
				break;
			}
		}
	}
}

void CutTool::leaveEvent(QEvent* event)
{
	if (hoverIndex >= 0) {
		hoverIndex = -1;
		update();
	}
	
}


void CutTool::showToolTip()
{
	if (hoverIndex == 0) {
		QToolTip::showText(QCursor::pos(), "退出截图(Esc)", this);
	}
	else if (hoverIndex == 1) {
		QToolTip::showText(QCursor::pos(), "保存文件(Ctrl+S)", this);
	}
	else if (hoverIndex == 2) {
		QToolTip::showText(QCursor::pos(), "存入剪切板(Ctrl+C)", this);
	}
	else if (hoverIndex == 3) {
		if (disablePin) return;
		QToolTip::showText(QCursor::pos(), "钉住截图(Ctrl+P)", this);
	}
	else if (hoverIndex == 4) {
		QToolTip::showText(QCursor::pos(), "编辑截图(Ctrl+E)", this);
	}
}
