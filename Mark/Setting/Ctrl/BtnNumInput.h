#pragma once

#include <QWidget>
#include <QLineEdit>
#include "BtnNumInputBtn.h"

class BtnNumInput : public QWidget
{
	Q_OBJECT

public:
	BtnNumInput(const QString& text, int val=0, QWidget *parent = nullptr);
	~BtnNumInput();
	int getVal();
signals:
	void valueChanged(int val);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void onBtnClick();
private:
	BtnNumInputBtn* btnLeft;
	BtnNumInputBtn* btnRight;
	QLineEdit* input;
};
