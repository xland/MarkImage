#pragma once
#include <QMainWindow>

class BtnCheck : public QWidget
{
	Q_OBJECT
public:
	BtnCheck(const QString& text,bool isChecked = false, QWidget *parent = nullptr);
	~BtnCheck();
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public:
	bool isChecked{ false };
	QString text;
private:
};
