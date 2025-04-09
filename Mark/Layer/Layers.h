#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "LayerBar.h"

class Layers : public QWidget
{
	Q_OBJECT

public:
	Layers(QWidget *parent = nullptr);
	~Layers();
	void refreshShapes();
protected:
	void paintEvent(QPaintEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
private:
	void itemClick();
	void barClick();
private:
	LayerBar* layerBar;
	QScrollArea* listCtrl;
	QWidget* itemBox;
};
