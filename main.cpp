#include "MarkImage.h"
#include <QtWidgets/QApplication>
#include <QCoreApplication>

#include "App.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    App app(qApp);
    app.start();
    return a.exec();
}
