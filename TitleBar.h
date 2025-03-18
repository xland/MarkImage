#pragma once

#include <QWidget>
#include "BtnSys.h"

class TitleBar : public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget *parent = nullptr);
	~TitleBar();
public:
	BtnSys* btnMin;
	BtnSys* btnMax;
	BtnSys* btnClose;

protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
