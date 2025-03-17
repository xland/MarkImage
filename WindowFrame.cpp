#include "WindowFrame.h"

WindowFrame::WindowFrame(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#666"));
    shadow->setBlurRadius(8);
    this->setGraphicsEffect(shadow);
}

WindowFrame::~WindowFrame()
{

}

void WindowFrame::setContent(QWidget* child)
{
    child->setParent(this);
    child->move(8, 8);
    setFixedSize(child->width()+16, child->height() + 16);
}
