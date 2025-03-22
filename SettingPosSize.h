#pragma once

#include <QWidget>

class SettingPosSize : public QWidget
{
	Q_OBJECT

public:
	SettingPosSize(QWidget *parent = nullptr);
	~SettingPosSize();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
