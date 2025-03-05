#include "../Window/WindowMain.h"

#include "App.h"

namespace {
	std::unique_ptr<App> app;
}

App::App()
{
}

App::~App()
{
}

void App::init()
{
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

void App::start()
{
	auto win = new WindowMain();
	win->showMaximized();
}

App* App::get()
{
	return app.get();
}
