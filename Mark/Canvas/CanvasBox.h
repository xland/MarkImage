#pragma once

#include <QWidget>

class Canvas;
class CanvasBox : public QWidget
{
	Q_OBJECT

public:
	CanvasBox(QWidget *parent = nullptr);
	~CanvasBox();
signals:
	void onResize(const int w, const int h);
protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
public:

private:
	Canvas* canvas;
};
