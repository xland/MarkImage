#pragma once
#include <QMouseEvent>
#include <QEvent>
#include <QEnterEvent>
#include <QWidget>

class ScreenCapture;
class CutTool : public QWidget
{
	Q_OBJECT

public:
	CutTool(QWidget *parent = nullptr);
	~CutTool();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;
private:
	void saveFile();
	void saveClipboard();
private:
	int hoverIndex{-1};
};
