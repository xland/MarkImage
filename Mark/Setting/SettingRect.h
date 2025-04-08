#pragma once

#include <QWidget>
#include "SettingBase.h"

class SettingRect : public SettingBase
{
	Q_OBJECT

public:
	SettingRect(QWidget* parent = nullptr);
	~SettingRect();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};