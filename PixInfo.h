#pragma once

#include <QWidget>

class ScreenCapture;
class PixInfo : public QWidget
{
	Q_OBJECT
public:
	PixInfo(ScreenCapture* screenCapture,QWidget *parent = nullptr);
	~PixInfo();
	void mouseMove(const QPoint& nativePos);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	bool posInScreen(const int& x, const int& y);
private:
	QPoint mousePos;
	ScreenCapture* screenCapture;
};
