#pragma once

#include <QWidget>
#include "Util.h"

class BtnSys : public QWidget
{
	Q_OBJECT

public:
	BtnSys(const ushort& code, bool isClose = false,QWidget *parent = nullptr);
	~BtnSys();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void moveEvent(QMoveEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
signals:
	void click();
public:
	ushort code;
private:
	bool isHover{ false };
	bool isClose;
};
