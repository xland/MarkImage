#pragma once

#include <QWidget>

class BtnColorSelector : public QWidget
{
	Q_OBJECT

public:
	BtnColorSelector(QWidget *parent = nullptr);
	~BtnColorSelector();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public:
	QColor color;
private:
};
