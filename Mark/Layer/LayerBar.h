#pragma once

#include <QWidget>

class LayerBar : public QWidget
{
	Q_OBJECT
public:
	LayerBar(QWidget *parent = nullptr);
	~LayerBar();
signals:
	void onClick();
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event) override;
public:
	bool isChecked{ false };
private:

};
