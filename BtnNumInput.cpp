#include <QPainter>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "Util.h"
#include "BtnNumInput.h"

BtnNumInput::BtnNumInput(const QString& text, int val, QWidget* parent) : QWidget(parent), 
val{val}
{
	setFixedHeight(26);
	auto layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(new QLabel(text,this));
	//layout->addWidget(new QPushButton(text, this));
	layout->addWidget(new QLineEdit(this));
	setLayout(layout);
}

BtnNumInput::~BtnNumInput()
{

}

void BtnNumInput::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setBrush(Qt::NoBrush);
	p.setPen(QColor(120, 120, 120));
	auto r = rect().adjusted(6, 0, 0, 0);

	//auto font = Util::getIconFont(13);
	//p.setFont(*font);
	//p.drawText(r, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xe708));  //e70f

	//auto font = Util::getTextFont(13);
	//p.setFont(*font);
	//p.drawText(r, Qt::AlignLeft | Qt::AlignVCenter, text);
}
