#pragma once
#include <QPixmap>
#include <QMainWindow>

class PixInfo;
class ScreenCapture : public QMainWindow
{
	Q_OBJECT
public:
	ScreenCapture(QWidget *parent = nullptr);
	~ScreenCapture();
protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	void shotScreen();
	void showFullScreen();
	void initWinRect();
	QPoint getQtPoint(int x, int y);
	void changeMouseState(const int& x, const int& y);
	void changeRectMask(const QPoint& pos);
	void moveMaskRect(const QPoint& pos);
public:
	QPixmap pixScreen;
private:
	QPoint posPress;
	QList<QRect> rectWins;
	int x, y, w, h;
	QRect rectMask;
	/// <summary>
	/// 0 开始
	/// 1 截图区域确认
	/// 2 正在移动截图区域
	/// </summary>
	uint state{ 0 };
	uint mouseState{ 0 };
	PixInfo* pixInfo;
};
