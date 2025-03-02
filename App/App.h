#pragma once
#include "../Util/Eventer.h"
class App
{
public:
	App();
	~App();
	static void init();
	static void editImg(std::string& data);
	static void screenCapture();
private:
};

