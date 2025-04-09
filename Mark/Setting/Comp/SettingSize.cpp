#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

#include "../Ctrl/BtnCheck.h"
#include "../Ctrl/BtnNumInput.h"
#include "Util.h"
#include "SettingSize.h"

SettingSize::SettingSize(QWidget *parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setSpacing(10);
	layout->setContentsMargins(8, 38, 8, 8);
	layout->addWidget(new BtnNumInput("高度", 30, this));
	layout->addWidget(new BtnNumInput("宽度", 30, this));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

SettingSize::~SettingSize()
{
	
}

void SettingSize::paintEvent(QPaintEvent* event)
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
	p.drawText(r, Qt::AlignLeft | Qt::AlignTop, "大小");
}
