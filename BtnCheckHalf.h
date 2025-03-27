#pragma once

#include <QWidget>

class BtnCheckHalf : public QWidget
{
	Q_OBJECT

public:
	BtnCheckHalf(QWidget *parent = nullptr);
	~BtnCheckHalf();
signals:
	void onClick();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public:
	bool isChecked{ false };
	QString text;
private:

};
