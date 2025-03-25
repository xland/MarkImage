#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include "SettingFill.h"
#include "Util.h"

SettingFill::SettingFill(QWidget *parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setSpacing(4);
	layout->setContentsMargins(8, 36, 8, 8);
	checkNoFill = new BtnCheck("无填充", true, this);
	checkPureColor = new BtnCheck("纯色填充", false, this);
	checkGradientColor = new BtnCheck("渐变填充", false, this);
	colorSelector = new BtnColorSelector(this);

	connect(checkNoFill, &BtnCheck::onClick, this, &SettingFill::onCheckChange);
	connect(checkPureColor, &BtnCheck::onClick, this, &SettingFill::onCheckChange);
	connect(checkGradientColor, &BtnCheck::onClick, this, &SettingFill::onCheckChange);

	layout->addWidget(checkNoFill);
	layout->addWidget(checkPureColor);
	layout->addWidget(checkGradientColor);
	layout->addWidget(colorSelector);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

SettingFill::~SettingFill()
{

}

void SettingFill::paintEvent(QPaintEvent* event)
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
	p.drawText(r, Qt::AlignLeft | Qt::AlignTop, "填充属性");
}

void SettingFill::onCheckChange()
{
	auto btn = (BtnCheck*)sender();
	if (btn->isChecked) {
		return;
	}
	btn->isChecked = true;
	if (btn == checkNoFill) {
		checkPureColor->isChecked = false;
		checkGradientColor->isChecked = false;
		colorSelector->hide();
	}
	else if (btn == checkPureColor) {
		checkNoFill->isChecked = false;
		checkGradientColor->isChecked = false;
		colorSelector->show();
	}
	else if (btn == checkGradientColor)
	{
		checkPureColor->isChecked = false;
		checkNoFill->isChecked = false;
		colorSelector->hide();
	}
	update();
}
