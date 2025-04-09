#pragma once

#include <QWidget>

class SettingSize : public QWidget
{
	Q_OBJECT

public:
	SettingSize(QWidget *parent = nullptr);
	~SettingSize();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
