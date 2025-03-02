#include "App.h"

#include "../Util/Eventer.h"

App::App()
{
}

App::~App()
{
}

void App::init()
{
	//cmd.on("CmdImage", std::function<void(std::string&)>(App::editImg));
	cmd.on("CmdScreenCapture", std::bind(&App::screenCapture, this));
	cmd.on<std::string>("CmdImage", std::bind(&App::editImg, this, std::placeholders::_1));
	//Eventer::on("CmdScreenCapture", App::screenCapture);
	cmd.init();
}

void App::editImg(const std::string& data)
{
	//auto str = std::any_cast<std::string>(data);
	auto a = 1;
}

void App::screenCapture()
{
	auto a = 1;
}
