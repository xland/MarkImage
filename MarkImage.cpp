#include <Windows.h>
#include <dwmapi.h>
#include <QTimer>
#include <QVBoxLayout>

#include "MarkImage.h"
#include "TitleBar.h"

MarkImage::MarkImage(QPixmap* pixmap, QWidget* parent) : QMainWindow(parent), pixmap{pixmap}
{
	setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);     
    titleBar = new TitleBar(this);
    showMaximized();
}

MarkImage::~MarkImage()
{
    delete pixmap;
}

void MarkImage::resizeEvent(QResizeEvent* event)
{
    auto w = width();
    if (isMaximized()) {
        titleBar->setFixedSize(w, 38);
        titleBar->move(0, 0);
    }
    else {
        titleBar->setFixedSize(w - 16, 38);
        titleBar->move(padding, padding);
    }
    QMainWindow::resizeEvent(event);
}

void MarkImage::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (!isMaximized()) {
        drawShadow(p);
    }
    else {
        p.setBrush(QColor(255, 255, 255));
        p.setPen(Qt::NoPen);
        p.drawRect(rect());
    }
}

void MarkImage::mousePressEvent(QMouseEvent* event)
{

}

void MarkImage::mouseMoveEvent(QMouseEvent* event)
{

}

void MarkImage::mouseReleaseEvent(QMouseEvent* event)
{

}

//bool MarkImage::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
//{
//    MSG* msg = static_cast<MSG*>(message);
//    if (msg->message == WM_LBUTTONDOWN) {
//        qDebug() << "Left mouse button clicked in QWidget!";
//        *result = 0;
//        return true;
//    }
//    return QWidget::nativeEvent(eventType, message, result);
//}

void MarkImage::drawShadow(QPainter& p)
{
    p.setPen(Qt::NoPen);
    QColor c(88, 88, 88, 88);
    {
        QRadialGradient gradient(QPointF(padding, padding), padding);
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(0, 0, padding, padding);
    }
    {
        QLinearGradient gradient(0, 0, 0, padding);
        gradient.setColorAt(0.0, Qt::transparent);
        gradient.setColorAt(1.0, c);
        p.setBrush(gradient);
        p.drawRect(padding, 0, width() - padding * 2, padding);
    }
    {
        QRadialGradient gradient(QPointF(width() - padding, padding), padding);
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(width() - padding, 0, padding, padding);
    }
    {
        QLinearGradient gradient(width() - padding, 0, width(), 0);
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(width() - padding, padding, padding, height() - 2 * padding);
    }
    {
        QRadialGradient gradient(QPointF(width() - padding, height() - padding), padding);
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(width() - padding, height() - padding, padding, padding);
    }
    {
        QLinearGradient gradient(padding, height() - padding, padding, height());
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(padding, height() - padding, width() - 2 * padding, padding);
    }
    {
        QRadialGradient gradient(QPointF(padding, height() - padding), padding);
        gradient.setColorAt(0.0, c);
        gradient.setColorAt(1.0, Qt::transparent);
        p.setBrush(gradient);
        p.drawRect(0, height() - padding, padding, padding);
    }
    {
        QLinearGradient gradient(0, 0, padding, 0);
        gradient.setColorAt(0.0, Qt::transparent);
        gradient.setColorAt(1.0, c);
        p.setBrush(gradient);
        p.drawRect(0, padding, padding, height() - 2 * padding);
    }
    p.setBrush(QColor(255, 255, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect().adjusted(padding, padding, -padding, -padding));
}
