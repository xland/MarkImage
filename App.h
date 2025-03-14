#pragma once

#include <QObject>

class App  : public QObject
{
	Q_OBJECT

public:
	App(QObject *parent);
	~App();
	void start();
private:
	void processCmd();
	void attachCmd();
};
