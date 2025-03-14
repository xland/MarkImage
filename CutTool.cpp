#include <Windows.h>
#include <QPainter>
#include <QPainterPath>
#include <QGuiApplication>
#include <QScreen>
#include "CutTool.h"

CutTool::CutTool(ScreenCapture* screenCapture, QWidget* parent) : QWidget(parent), screenCapture{ screenCapture }
{

}

CutTool::~CutTool()
{
	
}

void CutTool::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
}
