#pragma once
#include <QOpenGLWindow>
#include <QImage>
#include <QOpenGLPaintDevice>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include "MainTool.h"
#include "MainProperty.h"

class WindowMain : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	WindowMain();
	~WindowMain();
protected:
	void initializeGL() override;
	void paintGL() override;
	void closeEvent(QCloseEvent*) override;
	void showEvent(QShowEvent*) override;
	void resizeEvent(QResizeEvent*) override;
private:
	MainTool* mainTool;
	MainProperty* mainProperty;
	QPixmap pixmap;
};
