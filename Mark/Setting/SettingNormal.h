#pragma once

#include <QWidget>
#include "SettingBase.h"

class SettingNormal : public SettingBase
{
	Q_OBJECT

public:
	SettingNormal(QWidget* parent = nullptr);
	~SettingNormal();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};