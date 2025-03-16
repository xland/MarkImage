#include <dwmapi.h>
#include <QPainter>
#include <QMouseEvent>

#include "PinImage.h"

PinImage::PinImage(const QPoint& pos,const QPixmap& pixmap, QWidget* parent) : QMainWindow(parent)
,pixmap{pixmap}
,pos{pos}
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
    auto size = pixmap.size() / devicePixelRatio();
	setGeometry(QRect(pos,size));	

    HWND hwnd = (HWND)winId();
    MARGINS margins = { 1, 1, 1, 1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    const int DWMWA_NCRENDERING_POLICY = 2;
    DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    show();

    cutTool = new CutTool(true);
    auto x = pos.x() + size.width() - cutTool->width();
    auto y = pos.y() + size.height() + 6;
    cutTool->move(x, y);
    cutTool->show();
}

PinImage::~PinImage()
{
	
}

void PinImage::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, pixmap);
}

void PinImage::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        posPress = event->globalPosition().toPoint() - frameGeometry().topLeft();
        cutTool->hide();
    }
}

void PinImage::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - posPress);
    }
}

void PinImage::mouseReleaseEvent(QMouseEvent* event)
{
    auto pos = this->geometry().bottomRight();
    auto x = pos.x() - cutTool->width();
    auto y = pos.y() + 6;
    cutTool->move(x, y);
    cutTool->show();
}
