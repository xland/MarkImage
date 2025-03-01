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
	Eventer::on("CmdImage", App::editImg);
	Cmd::init();
}

void App::editImg(std::any& data)
{
	auto str = std::any_cast<std::string>(data);
	auto a = 1;
}
