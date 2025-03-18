#pragma once
#include <QPixmap>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>

class TitleBar;
class MarkImage : public QMainWindow
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
    void changeEvent(QEvent* event) override;
    //bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
private:
    void drawShadow(QPainter& p);
public:
    int padding{ 8 };
    int normalW{ 1000 }, normalH{ 800 };
private:
    QPixmap* pixmap;
    TitleBar* titleBar;

};
