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
    p.setBrush(QColor(200, 220, 240));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
    QPixmap logo(":/Res/logo.png");
    logo = logo.scaled(30 * window()->devicePixelRatio(), 30 * window()->devicePixelRatio(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p.drawPixmap(QRect(8, 6, 26, 26), logo);
    auto code = window()->isMaximized() ? QChar(0xe6ea) :QChar(0xe6e5);
    QList<QChar> arr({ QChar(0xe6e7), code, QChar(0xe6e8) });
    auto font = Util::getIconFont(14);
    p.setFont(*font);
    for (size_t i = 0; i < 3; i++)
    {
        QRect rect(width() - 40 * (i + 1), 0, 40, height());
        if (hoverIndex == i) {
            p.setBrush(i == 0 ? QColor(230, 18, 36) : QColor(248, 248, 255));
            p.setPen(Qt::NoPen);
            p.drawRect(rect);
            p.setBrush(Qt::NoBrush);
            p.setPen(i == 0 ? QColor(255, 255, 255) : QColor(0, 0, 0));
        }
        else {
            p.setBrush(Qt::NoBrush);
            p.setPen(QColor(88, 88, 88));
        }
        p.drawText(rect, Qt::AlignCenter, arr[i]);
    }
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        auto win = qobject_cast<MarkImage*>(parent());
        if (hoverIndex == 0) {
            window()->close();
        }
        else if (hoverIndex == 1) {
            mouseDoubleClickEvent(nullptr);
        }
        else if (hoverIndex == 2) {
            auto state = win->windowState();
            window()->showMinimized();
        }
        else {
            if (win->isMaximized()) {
                posPress = QPoint(win->normalW / 2, height() / 2);
            }
            else {
                posPress = QCursor::pos() - win->geometry().topLeft();
            }
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
                win->setFixedSize(win->normalW, win->normalH);
                win->move(QCursor::pos() - posPress);
                win->show();
                });
        }
        else {
            win->move(QCursor::pos() - posPress);
        }
    }
    else {
        auto pos = event->pos();
        auto x = width() - pos.x();
        if (pos.y() > height()) return;
        if (x<40) {
            if (hoverIndex != 0) {
                hoverIndex = 0;
                update();
            }
        }
        else if (x<80) {
            if (hoverIndex != 1) {
                hoverIndex = 1;
                update();
            }
        }
        else if (x < 120) {
            if (hoverIndex != 2) {
                hoverIndex = 2;
                update();
            }
        }
        else {
            if (hoverIndex != -1) {
                hoverIndex = -1;
                update();
            }
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
        QTimer::singleShot(20, [win]() {
            win->setFixedSize(win->normalW, win->normalH);
            win->setWindowFlags(Qt::FramelessWindowHint);
            auto screenRect = win->screen()->geometry();
            int x = (screenRect.width() - win->width()) / 2 + screenRect.x();
            int y = (screenRect.height() - win->height()) / 2 + screenRect.y();
            win->move(x, y);
            win->show();
        });
    }
    else {
        win->setWindowState(Qt::WindowMaximized);
        win->showMaximized();
    }
}

void TitleBar::leaveEvent(QEvent* event)
{
    if (hoverIndex != -1) {
        hoverIndex = -1;
        update();
    }
}
