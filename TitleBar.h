#pragma once

#include <QWidget>

class TitleBar : public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget *parent = nullptr);
	~TitleBar();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:

	QPoint posPress;
};
