#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include "SettingBorder.h"
#include "Util.h"

SettingBorder::SettingBorder(QWidget *parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setSpacing(4);
	layout->setContentsMargins(8, 36, 8, 8);
	checkNoBorder = new BtnCheck("无边框", true, this);
	checkSolidBorder = new BtnCheck("实线边框", false, this);
	checkdotBorder = new BtnCheck("虚线边框", false, this);

	connect(checkNoBorder, &BtnCheck::onClick, this, &SettingBorder::onCheckChange);
	connect(checkSolidBorder, &BtnCheck::onClick, this, &SettingBorder::onCheckChange);
	connect(checkdotBorder, &BtnCheck::onClick, this, &SettingBorder::onCheckChange);

	layout->addWidget(checkNoBorder);
	layout->addWidget(checkSolidBorder);
	layout->addWidget(checkdotBorder);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

SettingBorder::~SettingBorder()
{
	
}

void SettingBorder::paintEvent(QPaintEvent* event)
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
	p.drawText(r, Qt::AlignLeft|Qt::AlignTop, "边框属性");
}

void SettingBorder::adjustHeight()
{
	int totalHeight = 40;
	for (auto child : children()) {
		if (auto w = qobject_cast<QWidget*>(child)) {
			totalHeight += w->sizeHint().height()+6;
		}
	}
	setFixedHeight(totalHeight);
}

void SettingBorder::onCheckChange()
{
	auto btn = (BtnCheck*)sender();
	if (btn->isChecked) {
		return;
	}
	btn->isChecked = true;
	if (btn == checkNoBorder) {
		checkSolidBorder->isChecked = false;
		checkdotBorder->isChecked = false;
	}
	else if (btn == checkSolidBorder) {
		checkNoBorder->isChecked = false;
		checkdotBorder->isChecked = false;
	}
	else if (btn == checkdotBorder)
	{
		checkNoBorder->isChecked = false;
		checkSolidBorder->isChecked = false;
	}
	update();
}
