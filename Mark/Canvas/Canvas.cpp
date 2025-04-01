#include <QPainter>
#include "Canvas.h"
#include "CanvasBox.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{  
	auto cb = (CanvasBox*)parent;
	connect(cb, &CanvasBox::onResize, this, &Canvas::onParentResize);
    img.load("D:\\project\\MarkImage\\Doc\\allen.jpg");
    imgCanvas = new QPixmap(img.width(), img.height());
    imgCanvas->fill(Qt::transparent);
    imgBoard = new QPixmap(img.width(), img.height());
    imgBoard->fill(Qt::transparent);
}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.setRenderHint(QPainter::VerticalSubpixelPositioning, true);
    p.setRenderHint(QPainter::LosslessImageRendering, true);
    p.setRenderHint(QPainter::NonCosmeticBrushPatterns, true);
    p.drawImage(0,0, img);
    p.drawPixmap(0, 0, *imgBoard);
    p.drawPixmap(0, 0, *imgCanvas);
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		posPress = event->pos();
	}
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		rect1.setCoords(posPress.x(), posPress.y(), event->pos().x(), event->pos().y());
		rect1 = rect1.normalized();
		auto box = (CanvasBox*)parent();
        imgCanvas->fill(Qt::transparent);
        QPainter p(imgCanvas);
        p.setRenderHint(QPainter::Antialiasing, true);
		p.setPen(QPen(QBrush(QColor(255, 0, 0)), 2));
		p.setBrush(Qt::NoBrush);
		p.drawRect(rect1);
		update();
	}
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    imgCanvas->fill(Qt::transparent);
    auto box = (CanvasBox*)parent();
    QPainter p(imgBoard);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(QBrush(QColor(255, 0, 0)), 2));
    p.setBrush(Qt::NoBrush);
    p.drawRect(rect1);
    update();
}

void Canvas::onParentResize(const int widgetWidth, const int widgetHeight)
{
    int imgWidth = img.width();
    int imgHeight = img.height();

    if (imgWidth < widgetWidth && imgHeight < widgetHeight) {
        //todo 100%
        x = (widgetWidth - imgWidth) / 2;
        y = (widgetHeight - imgHeight) / 2;
        w = imgWidth;
        h = imgHeight;
        img.setDevicePixelRatio(1.f);
        imgCanvas->setDevicePixelRatio(1.f);
        imgBoard->setDevicePixelRatio(1.f);
    }
    else
    {
        float scale = qMin((float)widgetWidth / (float)imgWidth, (float)widgetHeight / (float)imgHeight) * 0.9;
        int scaledWidth = static_cast<int>(imgWidth * scale);
        int scaledHeight = static_cast<int>(imgHeight * scale);
        x = (widgetWidth - scaledWidth) / 2;
        y = (widgetHeight - scaledHeight) / 2;
        w = scaledWidth;
        h = scaledHeight;
        //todo 拖动改变图像位置
        auto dpr = 1.f / scale;
        img.setDevicePixelRatio(dpr);
        imgCanvas->setDevicePixelRatio(dpr);
        imgBoard->setDevicePixelRatio(dpr);
    }
    setGeometry(x, y, w, h);
}
