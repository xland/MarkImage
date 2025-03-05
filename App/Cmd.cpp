#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include "../Lib/cxxopts/cxxopts.hpp"
#include "Cmd.h"
#include "App.h"

Cmd::Cmd()
{
}

Cmd::~Cmd()
{
}

void Cmd::init()
{
    LPWSTR cmdLine = GetCommandLineW();
    int argc;
    LPWSTR* argvW = CommandLineToArgvW(cmdLine, &argc);
    if (argc > 1) {
        attachCmd();
    }
    std::vector<std::string> argvUtf8(argc);
    std::vector<const char*> argv(argc);
    for (int i = 0; i < argc; ++i) {
        QString qstr = QString::fromWCharArray(argvW[i], wcslen(argvW[i]));
        argvUtf8[i] = qstr.toStdString();
        argv[i] = argvUtf8[i].data();
    }
    cxxopts::Options options(argv[0], "MarkImage: add shapes, paths, mosaics, and text to images.");
    options.allow_unrecognised_options();
    options.add_options()
        ("Help", "Print help")
        ("Image", "Target image file", cxxopts::value<std::string>())
        ("ScreenCapture", "Capture screen");
    auto result = options.parse(argc, argv.data());
    if (result.count("Help")) {
        //帮助
        std::cout << options.help() << std::endl;
    }
    else if (result.count("Image")) {
        //编辑图像
        auto imgPath = result["Image"].as<std::string>();
        App::get()->editImg(imgPath);
    }
    else if (result.count("ScreenCapture")) {
        //截屏
        App::get()->screenCapture();
    }
    else {
        //正常启动，常驻托盘
        App::get()->start();
    }
    LocalFree(argvW);
}

void Cmd::attachCmd()
{
    if (::AttachConsole(ATTACH_PARENT_PROCESS)) {
        FILE* unused;
        if (freopen_s(&unused, "CONOUT$", "w", stdout)) {
            _dup2(_fileno(stdout), 1);
        }
        if (freopen_s(&unused, "CONOUT$", "w", stderr)) {
            _dup2(_fileno(stdout), 2);
        }
        std::ios::sync_with_stdio();
    }
}
