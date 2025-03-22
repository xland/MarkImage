#pragma once

#include <QWidget>

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
};
