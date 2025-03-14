#pragma once

#include <QWidget>

class ScreenCapture;
class CutTool : public QWidget
{
	Q_OBJECT

public:
	CutTool(ScreenCapture* screenCapture, QWidget *parent = nullptr);
	~CutTool();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	ScreenCapture* screenCapture;
};
