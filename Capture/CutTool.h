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
signals:
	void onSaveFile();
	void onSaveClipboard();
	void onClose();
	void onPinImg();
	void onEditImg();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;
private:
	void showToolTip();
private:
	int hoverIndex{-1};
	bool disablePin;
};
