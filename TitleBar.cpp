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
    setFixedHeight(34);
    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    initSysBtns();
    setLayout(layout);
}

TitleBar::~TitleBar()
{
}

void TitleBar::initSysBtns()
{
    btnMin = new BtnSys(0xe6e8, false, this);
    connect(btnMin, &BtnSys::click, [this]() {
        window()->showMinimized();
        });
    btnMax = new BtnSys(0xe6ea, false, this);
    connect(btnMax, &BtnSys::click, [this]() {
        if (btnMax->code == 0xe6e5) {
            btnMax->code = 0xe6ea;
            window()->showMaximized();
        }
        else {
            btnMax->code = 0xe6e5;
            window()->showNormal();
        }
        });
    btnClose = new BtnSys(0xe6e7, true, this);
    connect(btnClose, &BtnSys::click, [this]() {
        window()->close();
        });
    layout->addStretch();
    layout->addWidget(btnMin);
    layout->addWidget(btnMax);
    layout->addWidget(btnClose);
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
}

