#pragma once

#include <QWidget>

class ToolSetting : public QWidget
{
	Q_OBJECT

public:
	ToolSetting(QWidget *parent = nullptr);
	~ToolSetting();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
