#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include "SettingFill.h"
#include "BtnCheck.h"
#include "Util.h"

SettingFill::SettingFill(QWidget *parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setSpacing(4);
	layout->setContentsMargins(8, 36, 8, 8);
	layout->addWidget(new BtnCheck("无填充", true, this));
	layout->addWidget(new BtnCheck("纯色填充", false, this));
	layout->addWidget(new BtnCheck("渐变填充", false, this));
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
