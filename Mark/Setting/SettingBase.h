#pragma once

#include <QWidget>

class SettingBase : public QWidget
{
	Q_OBJECT

public:
	SettingBase(QWidget *parent = nullptr);
	~SettingBase();

private:
};
