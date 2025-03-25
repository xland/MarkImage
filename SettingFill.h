#pragma once

#include <QWidget>
#include "BtnCheck.h"
#include "BtnColorSelector.h"

class SettingFill : public QWidget
{
	Q_OBJECT

public:
	SettingFill(QWidget *parent = nullptr);
	~SettingFill();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void onCheckChange();
private:
	BtnCheck* checkNoFill;
	BtnCheck* checkPureColor;
	BtnCheck* checkGradientColor;
	BtnColorSelector* colorSelector;
};
