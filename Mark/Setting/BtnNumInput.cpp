#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "Util.h"
#include "BtnNumInput.h"

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
	btnLeft = new BtnNumInputBtn(0xe78e, this);
	layout->addWidget(btnLeft);
	input = new QLineEdit(this);
	input->setFixedHeight(22);
	input->setFixedWidth(80);
	input->setAlignment(Qt::AlignCenter);
	input->setStyleSheet(R"(QLineEdit{border:none;padding:0px;margin:0px;}
QLineEdit:focus{border:none;outline:none;})");
	QRegularExpression regExp("^[0-9]*$");
	QRegularExpressionValidator* validator = new QRegularExpressionValidator(regExp, input);
	input->setValidator(validator);
	input->setFocusPolicy(Qt::ClickFocus);
	input->setText(QString::number(val));
	layout->addWidget(input);
	btnRight = new BtnNumInputBtn(0xe711, this);
	layout->addWidget(btnRight);
	connect(btnLeft, &BtnNumInputBtn::click, this,&BtnNumInput::onBtnClick);
	connect(btnRight, &BtnNumInputBtn::click, this, &BtnNumInput::onBtnClick);
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

void BtnNumInput::onBtnClick()
{
	auto btn = (BtnNumInputBtn*)sender();
	if (btn == btnLeft) {
		val--;
	}
	else {
		val++;
	}
	input->setText(QString::number(val));
}
