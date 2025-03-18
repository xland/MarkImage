#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include <QApplication>
#include <QHBoxLayout>

#include "Util.h"
#include "TitleBar.h"
#include "MarkImage.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(34);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    btnMin = new BtnSys(QChar(0xe6e8),false,this);
    connect(btnMin, &BtnSys::click, [this]() {
        window()->showMinimized();
        });
    btnMax = new BtnSys(QChar(0xe6ea), false,this);
    connect(btnMax, &BtnSys::click, [this]() {
        window()->showMaximized();
        });
    btnClose = new BtnSys(QChar(0xe6e7), true,this);
    connect(btnClose, &BtnSys::click, [this]() {
        window()->close();
        });
    layout->addStretch();
    layout->addWidget(btnMin);
    layout->addWidget(btnMax);
    layout->addWidget(btnClose);
    setLayout(layout);
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
    logo.setDevicePixelRatio(window()->devicePixelRatio());
    p.drawPixmap(QRect(8, 4, 26, 26), logo);
    //auto code = window()->isMaximized() ? QChar(0xe6ea) :QChar(0xe6e5);
    //QList<QChar> arr({ QChar(0xe6e7), code, QChar(0xe6e8) });
    //auto font = Util::getIconFont(14);
    //p.setFont(*font);
    //for (size_t i = 0; i < 3; i++)
    //{
    //    QRect rect(width() - 40 * (i + 1), 0, 40, height());
    //    if (hoverIndex == i) {
    //        p.setBrush(i == 0 ? QColor(230, 18, 36) : QColor(248, 248, 255));
    //        p.setPen(Qt::NoPen);
    //        p.drawRect(rect);
    //        p.setBrush(Qt::NoBrush);
    //        p.setPen(i == 0 ? QColor(255, 255, 255) : QColor(0, 0, 0));
    //    }
    //    else {
    //        p.setBrush(Qt::NoBrush);
    //        p.setPen(QColor(88, 88, 88));
    //    }
    //    p.drawText(rect, Qt::AlignCenter, arr[i]);
    //}
}

