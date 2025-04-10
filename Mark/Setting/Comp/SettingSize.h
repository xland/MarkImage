#pragma once

#include <QWidget>

class SettingSize : public QWidget
{
	Q_OBJECT

public:
	SettingSize(QWidget *parent = nullptr);
	~SettingSize();
signals:
	void valueChanged(int w, int h);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
