#pragma once
#include <QWidget>

class BtnTool : public QWidget
{
	Q_OBJECT

public:
	BtnTool(const QString& text,const uint& code, QWidget *parent = nullptr,bool isSelected=false);
	~BtnTool();
signals:
	void click();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public:
	bool isSelected{ false };
private:
	bool isHover{ false };
	QString text;
	uint code;
};
