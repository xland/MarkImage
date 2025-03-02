#include "App.h"
#include "Cmd.h"
#include "../Util/Eventer.h"

App::App()
{
}

App::~App()
{
}

void App::init()
{
	//Eventer::on("CmdImage", std::function<void(std::string&)>(App::editImg));
	//Eventer::on("CmdScreenCapture", std::function<void()>(App::screenCapture));
	Eventer::on("CmdImage", App::editImg);
	//Eventer::on("CmdScreenCapture", App::screenCapture);
	Cmd::init();
}

void App::editImg(std::string& data)
{
	//auto str = std::any_cast<std::string>(data);
	auto a = 1;
}

void App::screenCapture()
{
	auto a = 1;
}
