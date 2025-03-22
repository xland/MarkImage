#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

#include "BtnCheck.h"
#include "BtnNumInput.h"
#include "Util.h"
#include "SettingPosSize.h"

SettingPosSize::SettingPosSize(QWidget *parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setSpacing(4);
	layout->setContentsMargins(8, 36, 8, 8);
	layout->addWidget(new BtnNumInput("水平位置", 30, this));
	layout->addWidget(new BtnCheck("垂直位置", false, this));
	layout->addWidget(new BtnCheck("高度", false, this));
	layout->addWidget(new BtnCheck("宽度", false, this));
	layout->addWidget(new BtnCheck("旋转角度", false, this));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

SettingPosSize::~SettingPosSize()
{
	
}

void SettingPosSize::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(Qt::NoBrush);
	p.setPen(QColor(160, 160, 160));
	auto r = rect().adjusted(6, 10, -6, 0);

	auto font = Util::getIconFont(13);
	p.setFont(*font);
	p.drawText(r, Qt::AlignRight | Qt::AlignTop, QChar(0xe708));  //e70f

	font = Util::getTextFont(13);
	p.setFont(*font);
	p.drawText(r, Qt::AlignLeft | Qt::AlignTop, "位置大小");
}
