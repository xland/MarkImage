#pragma once
#include <QList>
#include <QObject>

class ShapeBase;
class Shapes  : public QObject
{
	Q_OBJECT

public:
	Shapes(QObject *parent);
	~Shapes();
	static Shapes* get();
	void add(ShapeBase* shape);
	void removeNotReady();
private:
	QList<ShapeBase*> shapes;
};
