#pragma once
#include "Cmd.h"
#include "../Util/Eventer.h"
class App
{
public:
	App();
	~App();
	void init();
	void editImg(const std::string& data);
	void screenCapture();
private:
	Cmd cmd;
};

