#pragma once

#include <QWidget>
#include "BtnCheck.h"
#include "BtnNumInput.h"
#include "BtnColorSelector.h"

class SettingBorder : public QWidget
{
	Q_OBJECT

public:
	SettingBorder(QWidget *parent = nullptr);
	~SettingBorder();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void adjustHeight();
private:
	void onCheckChange();
private:
	BtnCheck* checkNoBorder;
	BtnCheck* checkSolidBorder;
	BtnCheck* checkdotBorder;
	BtnNumInput* borderWidth;
	BtnColorSelector* colorSelector;
};
