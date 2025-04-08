#pragma once

#include <QWidget>
#include "SettingBase.h"

class SettingImg : public SettingBase
{
	Q_OBJECT

public:
	SettingImg(QWidget *parent = nullptr);
	~SettingImg();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
