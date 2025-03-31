#pragma once
#include <QPixmap>
#include <QWidget>
#include <QPainter>

class TitleBar;
class MarkImage : public QWidget
{
    Q_OBJECT

public:
    MarkImage(QPixmap* pixmap, QWidget *parent = nullptr);
    ~MarkImage();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
    void changeEvent(QEvent* event) override;
    void showEvent(QShowEvent* event) override;
private:
public:
    int padding{ 8 };
    int normalW{ 1000 }, normalH{ 800 };
private:
    QPixmap* pixmap;
    TitleBar* titleBar;
};
