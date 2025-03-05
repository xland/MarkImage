#include "MarkImage.h"
#include <QtWidgets/QApplication>

#include "App/App.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    app.init();
    return a.exec();
}
