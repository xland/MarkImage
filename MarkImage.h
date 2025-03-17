#pragma once
#include <QPixmap>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>
#include "WindowFrame.h"

class TitleBar;
class MarkImage : public QMainWindow
{
    Q_OBJECT

public:
    MarkImage(QPixmap* pixmap, QWidget *parent = nullptr);
    ~MarkImage();
protected:
    //void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    void drawShadow(QPainter& p);
private:
    QPixmap* pixmap;
    TitleBar* titleBar;
    int padding{ 8 };
};
