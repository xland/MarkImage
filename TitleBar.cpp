#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include <QApplication>

#include "Util.h"
#include "TitleBar.h"
#include "MarkImage.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setGeometry(0, 0, parent->width(), 38);
}

TitleBar::~TitleBar()
{
}

void TitleBar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.setBrush(QColor(200, 220, 240));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
    QPixmap logo(":/Res/logo.png");
    p.drawPixmap(QRect(4,4,15,15), logo);

    auto font = Util::getIconFont(14);
    p.setFont(*font);
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(88, 88, 88));
    p.drawText(QRect(width()-40, 4, 40, 30), Qt::AlignCenter, QChar(0xe866));
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        auto win = qobject_cast<MarkImage*>(parent());
        if (win->isMaximized()) {
            posPress = QPoint(400, 19);
        }
        else {
            posPress = QCursor::pos() - win->geometry().topLeft();
        }
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        auto win = (MarkImage*)(parent());
        if (win->isMaximized()) {
            win->setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
            win->setWindowState(Qt::WindowNoState);
            QTimer::singleShot(20, [win, this]() {
                win->setWindowFlags(Qt::FramelessWindowHint);
                win->setFixedSize(800, 600);
                win->move(QCursor::pos() - posPress);
                win->show();
                });
        }
        else {
            win->move(QCursor::pos() - posPress);
        }
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    auto win = (MarkImage*)(parent());
    if (win->isMaximized()) {
        win->setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
        win->setWindowState(Qt::WindowNoState);
        QTimer::singleShot(60, [win]() {
            win->setFixedSize(800, 600);
            win->setWindowFlags(Qt::FramelessWindowHint);
            auto screenRect = win->screen()->geometry();
            int x = (screenRect.width() - win->width()) / 2 + screenRect.x();
            int y = (screenRect.height() - win->height()) / 2 + screenRect.y();
            win->move(x, y);
            win->show();
        });
    }
    else {
        win->showMaximized();
    }
}
