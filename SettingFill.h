#pragma once

#include <QWidget>

class SettingFill : public QWidget
{
	Q_OBJECT

public:
	SettingFill(QWidget *parent = nullptr);
	~SettingFill();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
