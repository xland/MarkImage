#pragma once

#include <QWidget>

class BtnTool;
class ToolBar : public QWidget
{
	Q_OBJECT

public:
	ToolBar(QWidget *parent = nullptr);
	~ToolBar();
	void btnClick();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
