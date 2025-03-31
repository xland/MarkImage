#pragma once

#include <QWidget>

class ShapeItem : public QWidget
{
	Q_OBJECT

public:
	ShapeItem(QWidget *parent = nullptr);
	~ShapeItem();
signals:
	void onClick();
protected:
	void paintEvent(QPaintEvent* event);
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
public:
	bool isCheck{ false };
private:
	bool isHover{ false };
	QPoint dragStartPosition;
};
