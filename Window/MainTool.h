#pragma once

#include <QMainWindow>

class MainTool : public QMainWindow
{
	Q_OBJECT

public:
	MainTool();
	~MainTool();
protected:
	void paintEvent(QPaintEvent* event);
private:
};
