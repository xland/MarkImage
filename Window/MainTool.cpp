#include "MainTool.h"

MainTool::MainTool() : QMainWindow()
{
	setWindowFlags(Qt::FramelessWindowHint| Qt::Tool);	
	setWindowTitle("标题");
}

MainTool::~MainTool()
{

}
