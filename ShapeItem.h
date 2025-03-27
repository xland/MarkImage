#pragma once

#include <QWidget>

class ShapeItem : public QWidget
{
	Q_OBJECT

public:
	ShapeItem(QWidget *parent = nullptr);
	~ShapeItem();
protected:
	void paintEvent(QPaintEvent* event);
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	bool isHover{ false };
	bool isCheck{ false };
};
