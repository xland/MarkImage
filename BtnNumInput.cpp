#include <QPainter>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "Util.h"
#include "BtnNumInput.h"
#include "BtnNumInputBtn.h"

BtnNumInput::BtnNumInput(const QString& text, int val, QWidget* parent) : QWidget(parent), 
val{val}
{
	setFixedHeight(22);
	auto layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	auto label = new QLabel(text, this);
	label->setStyleSheet(R"(QLabel{color:#888888;font-size:13px})");
	layout->addWidget(label);
	layout->addWidget(new BtnNumInputBtn(0xe78e, this));
	auto input = new QLineEdit(this);
	input->setFixedHeight(22);
	input->setFixedWidth(80);
	input->setStyleSheet(R"(QLineEdit{border:none;padding:0px;margin:0px;}
QLineEdit:focus{border:none;outline:none;})");
	layout->addWidget(input);
	layout->addWidget(new BtnNumInputBtn(0xe711, this));
	setLayout(layout);
}

BtnNumInput::~BtnNumInput()
{

}

void BtnNumInput::paintEvent(QPaintEvent* event)
{
	//QPainter p(this);
	//p.setRenderHint(QPainter::Antialiasing, true);
	//p.setRenderHint(QPainter::TextAntialiasing, true);
	//p.setBrush(QColor(255, 255, 255));
	//p.setPen(QColor(88, 88, 88));
	//p.drawRoundedRect(rect().right() - 124, 0, width(), height(),3,3);
}
