#pragma once

#include <QWidget>

class StatusBar : public QWidget
{
	Q_OBJECT

public:
	StatusBar(QWidget *parent = nullptr);
	~StatusBar();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
