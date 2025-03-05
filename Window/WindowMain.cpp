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
}

void WindowMain::paintGL()
{
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
