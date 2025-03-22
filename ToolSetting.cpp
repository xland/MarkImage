#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

#include "Util.h"
#include "ToolSetting.h"
#include "SettingBorder.h"
#include "SettingFill.h"
#include "SettingPosSize.h"

ToolSetting::ToolSetting(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFixedWidth(220);
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->addWidget(new SettingFill(this));
    layout->addWidget(new SettingBorder(this));
    layout->addWidget(new SettingPosSize(this));
    layout->addStretch();
    setLayout(layout);
}

ToolSetting::~ToolSetting()
{
}

void ToolSetting::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}