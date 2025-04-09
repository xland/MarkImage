#pragma once

#include <QWidget>
#include "SettingBase.h"

class SettingBoard : public SettingBase
{
	Q_OBJECT

public:
	SettingBoard(QWidget *parent = nullptr);
	~SettingBoard();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
