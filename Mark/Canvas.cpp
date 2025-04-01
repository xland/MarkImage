#include <QPainter>
#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	img.load("D:\\project\\MarkImage\\Doc\\allen.jpg");
}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(255, 255, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());

    int widgetWidth = width();
    int widgetHeight = height();
    int imgWidth = img.width();
    int imgHeight = img.height();

	if (imgWidth < widgetWidth && imgHeight < widgetHeight) {
		p.drawImage((widgetWidth - imgWidth) / 2, (widgetHeight - imgHeight) / 2, img);
		return;
	}
	float scale = qMin((float)widgetWidth / (float)imgWidth, (float)widgetHeight / (float)imgHeight) * 0.9;
    int scaledWidth = static_cast<int>(imgWidth * scale);
    int scaledHeight = static_cast<int>(imgHeight * scale);
    int x = (widgetWidth - scaledWidth) / 2;
    int y = (widgetHeight - scaledHeight) / 2;
    p.drawImage(x,y, img.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}