#pragma once

#include <QWidget>

class BtnNumInput : public QWidget
{
	Q_OBJECT

public:
	BtnNumInput(const QString& text, int val=0, QWidget *parent = nullptr);
	~BtnNumInput();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	int val;
};
