#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "BtnSys.h"

class TitleBar : public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget *parent = nullptr);
	~TitleBar();
private:
	void initSysBtns();
public:
	BtnSys* btnMin;
	BtnSys* btnMax;
	BtnSys* btnClose;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	QHBoxLayout* layout;
};
