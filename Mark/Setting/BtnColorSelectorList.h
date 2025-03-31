#pragma once

#include <QWidget>

class BtnColorSelectorList : public QWidget
{
	Q_OBJECT

public:
	BtnColorSelectorList(QWidget *parent = nullptr);
	~BtnColorSelectorList();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
