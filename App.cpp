#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QGuiApplication>

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

#include "App.h"
#include "ScreenCapture.h"
#include "MarkImage.h"

App::App(QObject *parent) : QObject(parent)
{
    //QFont font("Microsoft YaHei Light", 10);
    //qApp->setFont(font);
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
        new MarkImage(nullptr);
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
        new MarkImage(nullptr);
    }
    else if(param["type"] == "screenCapture"){
        //{\"type\":\"screenCapture\"}
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
