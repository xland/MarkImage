#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <QString>

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

#include "App.h"
#include "ScreenCapture.h"

App::App(QObject *parent) : QObject(parent)
{
}

App::~App()
{
}

void App::start()
{
    attachCmd();
	processCmd();
    //qDebug() << "out put";
    //QTimer::singleShot(600, [this]() {
    //    qDebug() << "out put2";
    //});
}

void App::processCmd()
{
	auto arguments = QCoreApplication::arguments();
    if (arguments.length() < 2) {
        return;
    }
    QJsonParseError err;
    QJsonDocument jd = QJsonDocument::fromJson(arguments[1].toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || jd.isNull())
    {
        qWarning() << "json parse error" << err.errorString();
        return;
    }
    auto param = jd.object();
    if (param["type"] == "editImage") {

    }
    else if(param["type"] == "screenCapture"){
        new ScreenCapture();
    }
    else if (param["type"] == "pinImage") {

    }
}

void App::attachCmd()
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
