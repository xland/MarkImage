#include "MarkImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarkImage w;
    w.show();
    return a.exec();
}
