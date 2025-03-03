#include <string>
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
	//cmd.on("CmdScreenCapture", [this]() {
	//	screenCapture();
	//	});
	//cmd.on("CmdImage", std::bind(&App::editImg, this, std::placeholders::_1));
	cmd.on("CmdImage", [this](std::string& img) {
	});
	cmd.on("CmdScreenCapture", [this]() {
		});
	cmd.init();
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
