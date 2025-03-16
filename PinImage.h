#pragma once
#include <QPixmap>
#include <QMainWindow>
#include "CutTool.h"

class PinImage : public QMainWindow
{
	Q_OBJECT

public:
	PinImage(const QPoint& pos, const QPixmap& pixmap,QWidget *parent = nullptr);
	~PinImage();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	QPoint posPress;
	QPixmap pixmap;
	QPoint pos;
	CutTool* cutTool;
};
