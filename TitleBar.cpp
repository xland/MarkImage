#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QTimer>
#include <QApplication>

#include "Util.h"
#include "TitleBar.h"
#include "MarkImage.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{ 
    //setGeometry(8, 8, parent->width()-16, 38);
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
        posPress = event->globalPosition().toPoint() - win->geometry().topLeft();
        if (win) {
            win->setWindowState(Qt::WindowNoState); // 恢复窗口的普通状态
            win->showNormal(); // 确保窗口显示为普通状态
            win->setMinimumSize(800, 600);
            win->setMaximumSize(800, 600);
        }

        //setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        //win->setFixedSize(800, 600);
        
        //setWindowState(Qt::WindowNoState);
        //win->resize(800, 600);
        //win->adjustSize();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        auto win = (QMainWindow*)(parent());
        if (win->isMaximized()) {
            //win->setWindowState(Qt::WindowNoState);
            //setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
            //win->setFixedSize(800, 600);
            //win->showNormal();
        }
        win->move(event->globalPosition().toPoint() - posPress);
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
}
