#pragma once
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QImage>
#include <QOpenGLFunctions>

class WindowScreen : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	WindowScreen();
	~WindowScreen();
private:
};
