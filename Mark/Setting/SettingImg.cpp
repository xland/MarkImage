#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

#include "../Tool/ToolBar.h"
#include "Util.h"
#include "SettingImg.h"

SettingImg::SettingImg(QWidget *parent) : SettingBase(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFixedWidth(220);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(6, 6, 6, 6);

    layout->addStretch();
    setLayout(layout);
}

SettingImg::~SettingImg()
{
}

void SettingImg::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}
