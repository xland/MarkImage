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
	CutTool(bool disablePin, QWidget *parent = nullptr);
	~CutTool();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;
private:
	void saveFile();
	void saveClipboard();
	void showToolTip();
	void pinImage();
private:
	int hoverIndex{-1};
	bool disablePin;
};
