#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>
#include "BtnColorSelector.h"
#include "Util.h"

BtnColorSelector::BtnColorSelector(const QString& text, QWidget* parent) : QWidget(parent),
color(Qt::red),text{text}
{
	setFixedHeight(22);
	auto layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	auto label = new QLabel(text, this);
	label->setStyleSheet(R"(QLabel{color:#888888;font-size:13px})");
	layout->addWidget(label);
	setVisible(false);
}

BtnColorSelector::~BtnColorSelector()
{

}

void BtnColorSelector::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(QColor(255, 255, 255));
	p.setPen(Qt::NoPen);
	QRect rr(rect().right() - 124, 0, 124, height());
	p.drawRect(rr);

	p.setBrush(color);
	rr.adjust(3, 3, -3, -3);
	p.drawRoundedRect(rr,3,3);

	//auto font = Util::getIconFont(12);
	//p.setFont(*font);
	//p.setBrush(Qt::NoBrush);
	//p.setPen(QColor(130, 130, 130));
	//QRect rr2(rect().right() - 22, 0, 22, height());
	//p.drawText(rr2, Qt::AlignCenter, QChar(0xe70f));  //QChar(0xe708)

}

void BtnColorSelector::mousePressEvent(QMouseEvent* event)
{
	auto p = event->pos();
	if (p.x() < rect().right() - 124) {
		return;
	}
	color = QColorDialog::getColor(Qt::white, window(), "选择颜色",QColorDialog::ColorDialogOption::ShowAlphaChannel);
	update();
}
