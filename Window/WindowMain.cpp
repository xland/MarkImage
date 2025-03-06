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
    auto pHwnd = (HWND)winId();

    //mainProperty = new MainProperty();
    //auto hwnd1 = (HWND)mainProperty->winId();
    //SetParent(hwnd1, pHwnd);
    //mainProperty->setFixedSize(QSize(width(), 60));

    //mainTool = new MainTool();
    //auto hwnd2 = (HWND)mainTool->winId();
    //SetParent(hwnd2, pHwnd);
    //mainTool->move(600, 100);

    setMaximumSize(QSize(1200, 800));
    setMinimumSize(QSize(1200, 800));
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
    //mainTool->close();
    //mainTool->deleteLater();
    deleteLater();
}

void WindowMain::showEvent(QShowEvent*)
{
    //mainTool->show();
    //mainProperty->show();
}

void WindowMain::resizeEvent(QResizeEvent*)
{
    //if (!mainProperty) return;
    //mainProperty->setFixedWidth(width()-30);
    //mainProperty->move(0, 0);
}
