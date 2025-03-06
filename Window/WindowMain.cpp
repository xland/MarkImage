#include <QPainter>
#include "WindowMain.h"

WindowMain::WindowMain()
{
    QSurfaceFormat format;
    format.setSamples(8);
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    mainTool = new MainTool();
    auto hwnd = (HWND)mainTool->winId();
    auto pHwnd = (HWND)winId();
    SetParent(hwnd, pHwnd);
    mainTool->move(100, 100);
}

WindowMain::~WindowMain()
{

}

void WindowMain::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    pixmap.load("D:\\test.png");
    pixmap.setDevicePixelRatio(1.5);
}

void WindowMain::paintGL()
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void WindowMain::closeEvent(QCloseEvent*)
{
    mainTool->close();
    mainTool->deleteLater();
    deleteLater();
}

void WindowMain::showEvent(QShowEvent*)
{
    mainTool->show();
}
