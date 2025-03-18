#pragma once

#include <QWidget>
#include "Util.h"

class BtnSys : public QWidget
{
	Q_OBJECT

public:
	BtnSys(const QChar& iconCode, bool isClose = false,QWidget *parent = nullptr);
	~BtnSys();
protected:
	void paintEvent(QPaintEvent* event) override;
	virtual void enterEvent(QEnterEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
signals:
	void click();
private:
	QChar iconCode;
	bool isHover{ false };
	bool isClose;
};
