#include "MainProperty.h"

MainProperty::MainProperty() : QMainWindow()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	setWindowTitle("属性");
}

MainProperty::~MainProperty()
{
}
