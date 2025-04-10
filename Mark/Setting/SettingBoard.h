#pragma once

#include <QWidget>
#include "SettingBase.h"

class SettingBoard : public SettingBase
{
	Q_OBJECT

public:
	SettingBoard(QWidget *parent = nullptr);
	~SettingBoard();
	void setVal(int w, int h);

protected:
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
private:
};
