#include <Windows.h>
#include <QPainter>
#include <QPainterPath>
#include <QGuiApplication>
#include <QScreen>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "ScreenCapture.h"
#include "Util.h"
#include "CutTool.h"

CutTool::CutTool(QWidget* parent) : QWidget(parent)
{
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
		if (i == hoverIndex) {
			p.setBrush(QColor(228, 238, 255));
			p.setPen(Qt::NoPen);
			p.drawRoundedRect(r.adjusted(2,4,-2,-4), 4, 4);
			textColor.setRgb(9, 88, 217);
		}
		p.setFont(*font);
		p.setBrush(Qt::NoBrush);
		p.setPen(textColor);
		p.drawText(r, Qt::AlignCenter, arr[i]);
	}
}

void CutTool::mousePressEvent(QMouseEvent* event)
{
	if (hoverIndex == 0) {
		qApp->quit();
	}
	else if (hoverIndex == 1) {
		saveFile();
	}
	else if (hoverIndex == 2) {
		saveClipboard();
	}
	else if (hoverIndex == 3) {

	}
	else if (hoverIndex == 4) {

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

void CutTool::saveFile()
{
	QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	auto filePath = QDir::cleanPath(desktopPath + QDir::separator() + "Img" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + ".png");
	filePath = QFileDialog::getSaveFileName(window(), tr("保存文件"), filePath, "MarkImage (*.png)");
	if (filePath.isEmpty())
	{
		return;
	}
	auto win = (ScreenCapture*)window();
	auto dpr = win->devicePixelRatio();
	QRect rr(win->rectMask.topLeft() * dpr, win->rectMask.size() * dpr);
	win->pixScreen.copy(rr).save(filePath);
	qApp->quit();
}

void CutTool::saveClipboard()
{
	auto win = (ScreenCapture*)window();
	auto dpr = win->devicePixelRatio();
	QRect rr(win->rectMask.topLeft() * dpr, win->rectMask.size() * dpr);
	auto tempImg = win->pixScreen.copy(rr).toImage();
	auto width = tempImg.width();
	auto height = tempImg.height();
	HDC screenDC = GetDC(nullptr);
	HDC memoryDC = CreateCompatibleDC(screenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(screenDC, width, height);
	DeleteObject(SelectObject(memoryDC, hBitmap));
	BITMAPINFO bitmapInfo = { 0 };
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = width;
	bitmapInfo.bmiHeader.biHeight = -height;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	//pixmap.addr() 像素数据的地址
	SetDIBitsToDevice(memoryDC, 0, 0, width, height, 0, 0, 0, height, tempImg.bits(), &bitmapInfo, DIB_RGB_COLORS);
	if (!OpenClipboard(nullptr)) {
		QMessageBox::warning(this, "Error", "Failed to open clipboard when save to clipboard.", QMessageBox::StandardButton::Ok);
		return;
	}
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard();
	ReleaseDC(nullptr, screenDC);
	DeleteDC(memoryDC);
	DeleteObject(hBitmap);
	qApp->quit();
}
