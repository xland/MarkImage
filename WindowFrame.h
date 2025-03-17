#pragma once
#include <QPixmap>
#include <QtWidgets/QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>

class WindowFrame : public QMainWindow
{
	Q_OBJECT
public:
	WindowFrame(QWidget *parent = nullptr);
	~WindowFrame();
	void setContent(QWidget* child);
private:
};
