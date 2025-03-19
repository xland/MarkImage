#pragma once
#include <QPixmap>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>

namespace QWK {
    class WidgetWindowAgent;
    class StyleAgent;
}

class TitleBar;
class MarkImage : public QWidget
{
    Q_OBJECT

public:
    MarkImage(QPixmap* pixmap, QWidget *parent = nullptr);
    ~MarkImage();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    //void changeEvent(QEvent* event) override;
private:
    void drawShadow(QPainter& p);
public:
    int padding{ 8 };
    int normalW{ 1000 }, normalH{ 800 };
private:
    QPixmap* pixmap;
    TitleBar* titleBar;
    QWK::WidgetWindowAgent* windowAgent;
};
