#pragma once

#include <QtWidgets/QMainWindow>

class MarkImage : public QMainWindow
{
    Q_OBJECT

public:
    MarkImage(QWidget *parent = nullptr);
    ~MarkImage();
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
};
