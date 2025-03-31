#include <dwmapi.h>
#include <QPainter>
#include <QMouseEvent>

#include "Util.h"
#include "PinImage.h"
#include "./Mark/MarkImage.h"

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

    connect(cutTool, &CutTool::onSaveFile, this, &PinImage::saveFile);
    connect(cutTool, &CutTool::onSaveClipboard, this, &PinImage::saveClipboard);
    connect(cutTool, &CutTool::onClose, this, &PinImage::closeBtnClick);
    connect(cutTool, &CutTool::onEditImg, this, &PinImage::editImage);
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

void PinImage::saveFile()
{
    auto filePath = Util::getSaveFilePath();
    if (filePath.isEmpty())
    {
        return;
    }
    auto dpr = devicePixelRatio();
    pixmap.save(filePath);
    closeBtnClick();
}

void PinImage::saveClipboard()
{
    Util::saveImgToClipboard(pixmap.toImage());
    closeBtnClick();
}

void PinImage::closeBtnClick()
{
    close();
    deleteLater();
    cutTool->close();
    cutTool->deleteLater();
}

void PinImage::editImage()
{
    auto pix = new QPixmap(pixmap);
    new MarkImage(pix);
    closeBtnClick();
}
