#pragma once

#include <QWidget>

class BtnNumInputBtn : public QWidget
{
	Q_OBJECT

public:
	BtnNumInputBtn(const ushort& code, QWidget *parent = nullptr);
	~BtnNumInputBtn();
signals:
	void click();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public:
	ushort code;
private:
	bool isHover{ false };
private:
};
