#pragma once
#include <string>
#include <iostream>
#include "Cmd.h"
class App
{
public:
	App();
	~App();
	void init();
	void editImg(std::string& data);
	void screenCapture();
	void start();
	static App* get();
};