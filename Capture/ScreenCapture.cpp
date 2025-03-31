#include <Windows.h>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QApplication>
#include <Windows.h>
#include <dwmapi.h>
#include <ShellScalingApi.h>

#include "Util.h"
#include "PixInfo.h"
#include "ScreenCapture.h"
#include "CutTool.h"
#include "PinImage.h"
#include "./Mark/MarkImage.h"

ScreenCapture::ScreenCapture(QWidget *parent) : QMainWindow(parent),
    x{ GetSystemMetrics(SM_XVIRTUALSCREEN) },
    y{ GetSystemMetrics(SM_YVIRTUALSCREEN) },
    w{ GetSystemMetrics(SM_CXVIRTUALSCREEN) },
    h{ GetSystemMetrics(SM_CYVIRTUALSCREEN) }
{	
    setMouseTracking(true);
    initWinRect();
    shotScreen();
    showFullScreen();
    pixInfo = new PixInfo(this);
    setCursor(Qt::CrossCursor);
}

ScreenCapture::~ScreenCapture()
{
	
}

void ScreenCapture::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(0, 0, pixScreen);

    p.setBrush(QColor(0, 0, 0, 120));
    QColor borderColor(22, 118, 255);
    p.setPen(QPen(QBrush(borderColor), 1.5));
    QPainterPath path;
    path.addRect(-1, -1, w + 1, h + 1);
    path.addRect(rectMask);
    p.drawPath(path);
    if (state != 1) return;
    if (QApplication::mouseButtons() & Qt::LeftButton) return;

    //绘制边框上的拖动圆点
    p.setBrush(borderColor);
    p.setPen(QPen(QBrush(QColor(255, 255, 255)), 1));
    auto r{ 3 };
    auto hw{ rectMask.width() / 2 };
    auto hh{ rectMask.height() / 2 };
    p.drawEllipse(rectMask.topLeft().toPointF(), r, r);
    p.drawEllipse(QPointF(rectMask.left() + hw, rectMask.top()), r, r);
    p.drawEllipse(rectMask.topRight().toPointF(), r, r);
    p.drawEllipse(QPointF(rectMask.right(), rectMask.top() + hh), r, r);
    p.drawEllipse(rectMask.bottomRight().toPointF(), r, r);
    p.drawEllipse(QPointF(rectMask.left() + hw, rectMask.bottom()), r, r);
    p.drawEllipse(rectMask.bottomLeft().toPointF(), r, r);
    p.drawEllipse(QPointF(rectMask.left(), rectMask.top() + hh), r, r);

    //绘制截图区域位置和大小
    auto text = QString("X:%1 Y:%2 R:%3 B:%4 W:%5 H:%6")
        .arg(rectMask.x()).arg(rectMask.y())
        .arg(rectMask.right()).arg(rectMask.bottom())
        .arg(rectMask.width()).arg(rectMask.height());
    auto font = Util::getTextFont(10);
    p.setFont(*font);
    QFontMetrics fm(*font);
    int w = fm.horizontalAdvance(text);
    if (y < 0) y = rectMask.y() + 4;
    QRect rect(rectMask.x(), rectMask.y() - 25, w + 14, 22);
    p.setBrush(QColor(0, 0, 0, 120));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,3,3);
    p.setPen(QPen(QBrush(Qt::white), 1));
    p.setBrush(Qt::NoBrush);
    p.drawText(rect, Qt::AlignCenter, text);
}

void ScreenCapture::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        posPress = event->pos();
        if (state == 1) {
            changeRectMask(posPress);
            update();
        }
        if (pixInfo) {
            pixInfo->hide();
        }
    }
}

void ScreenCapture::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        auto pos = event->pos();
        if (cutTool && cutTool->isVisible()) {
            cutTool->hide();
        }
        if (state == 0) {
            if (pos == posPress) return;
            rectMask.setCoords(posPress.x(), posPress.y(), pos.x(), pos.y());
            update();
        }
        else if (state == 1) {
            if (mouseState == 0)
            {
                moveMaskRect(pos);
            }
            else {
                changeRectMask(pos);
            }
            update();
        }
    }
    else {
        auto pos = event->pos();
        if (state == 0) {
            pixInfo->mouseMove(pos);
            for (const auto& rect : rectWins)
            {
                if (rect.contains(pos)) {
                    if (rectMask == rect) return;
                    rectMask = rect;
                    update();
                    return;
                }
            }
        }
        else if (state == 1) {
            changeMouseState(pos.x(), pos.y());
        }
    }
}

void ScreenCapture::mouseReleaseEvent(QMouseEvent* event)
{
    state = 1;
    rectMask = rectMask.normalized();
    update();
    if (!cutTool) {
        cutTool = new CutTool(false,this);
        connect(cutTool, &CutTool::onSaveFile, this, &ScreenCapture::saveFile);
        connect(cutTool, &CutTool::onSaveClipboard, this, &ScreenCapture::saveClipboard);
        connect(cutTool, &CutTool::onClose, this, &ScreenCapture::closeBtnClick);
        connect(cutTool, &CutTool::onPinImg, this, &ScreenCapture::pinImage);
        connect(cutTool, &CutTool::onEditImg, this, &ScreenCapture::editImage);
    }
    auto br = rectMask.bottomRight();
    cutTool->move(br.x() - cutTool->width(), br.y() + 4);
    cutTool->show();
}

void ScreenCapture::moveMaskRect(const QPoint& pos)
{
    auto span = pos - posPress;
    posPress = pos;
    auto target = rectMask.topLeft() + span;
    if (target.x() < 0) {
        target.setX(0);
        rectMask.moveTo(target);
        return;
    }
    if (target.y() < 0) {
        target.setY(0);
        rectMask.moveTo(target);
        return;
    }
    if (target.x() + rectMask.width() > width()) {
        target.setX(width()- rectMask.width());
        rectMask.moveTo(target);
        return;
    }
    if (target.y() + rectMask.height() > height()) {
        target.setY(height() - rectMask.height());
        rectMask.moveTo(target);
        return;
    }
    rectMask.moveTo(target);
}

void ScreenCapture::shotScreen()
{
    auto screens = QGuiApplication::screens();
    for (auto screen:screens) {
        auto screenPos = screen->geometry().topLeft();
        if (screenPos.x() == 0 && screenPos.y() == 0) {
            auto dpr = screen->devicePixelRatio();
            pixScreen = screen->grabWindow(0, x / dpr, y / dpr, w / dpr, h / dpr);
            break;
        }
    }
}

void ScreenCapture::showFullScreen()
{
    setGeometry(x, y, w, h);
    setWindowFlag(Qt::FramelessWindowHint);
    show();
    //注意 必须先重置大小，再设置缩放比例
    auto hwnd = (HWND)winId();
    SetWindowPos(hwnd, nullptr, x, y, w, h, SWP_NOZORDER | SWP_SHOWWINDOW);
    //注意 这里必须用窗口的dpr来设置img的dpr，不能用主屏的dpr，此操作必须最后执行
    auto dpr = devicePixelRatio();
    pixScreen.setDevicePixelRatio(dpr);
}

QPoint ScreenCapture::getQtPoint(int x, int y) {
    POINT point{ .x{x},.y{y} };
    HMONITOR hMonitor = MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
    double dpr;
    if (hMonitor) {
        UINT dpiX, dpiY;
        HRESULT hr = GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
        if (FAILED(hr)) {
            dpr = 1.0;
        }
        dpr = static_cast<double>(dpiX) / 96.0;
    }
    else {
        dpr = 1.0;
    }
    return QPoint(x / dpr, y / dpr);
}

void ScreenCapture::initWinRect()
{
    rectWins.clear();
    EnumWindows([](HWND hwnd, LPARAM lparam)
        {
            if (!hwnd) return TRUE;
            if (!IsWindowVisible(hwnd)) return TRUE;
            if (IsIconic(hwnd)) return TRUE;
            if (GetWindowTextLength(hwnd) < 1) return TRUE;
            RECT rect;
            DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
            if (rect.right - rect.left <= 6 || rect.bottom - rect.top <= 6) {
                return TRUE;
            }
            auto self = (ScreenCapture*)lparam;
            if (rect.left < self->x) rect.left = self->x;
            if (rect.top < self->y) rect.top = self->y;
            if (rect.right > self->x+self->w) rect.right = self->x + self->w;
            if (rect.bottom > self->y+self->h) rect.bottom = self->y + self->h;
            auto lt = self->getQtPoint(rect.left, rect.top);
            auto rb = self->getQtPoint(rect.right, rect.bottom);
            lt = self->mapFromGlobal(lt);
            rb = self->mapFromGlobal(rb);
            self->rectWins.push_back(QRect(lt, rb));
            return TRUE;
        }, (LPARAM)this);
}

void ScreenCapture::changeMouseState(const int& x, const int& y)
{
    auto leftX = rectMask.left(); auto topY = rectMask.top();
    auto rightX = rectMask.right(); auto bottomY = rectMask.bottom();
    if (x > leftX + 1 && y > topY + 1 && x < rightX - 1 && y < bottomY - 1) //不然截图区域上顶天，下顶地的时候没法改变高度
    {
        setCursor(Qt::SizeAllCursor);
        mouseState = 0;
    }
    else if (x <= leftX && y <= topY)
    {
        setCursor(Qt::SizeFDiagCursor);
        mouseState = 1;
    }
    else if (x >= leftX && x <= rightX && y <= topY)
    {
        setCursor(Qt::SizeVerCursor);
        mouseState = 2;
    }
    else if (x >= rightX && y <= topY)
    {
        setCursor(Qt::SizeBDiagCursor);
        mouseState = 3;
    }
    else if (x >= rightX && y >= topY && y <= bottomY)
    {
        setCursor(Qt::SizeHorCursor);
        mouseState = 4;
    }
    else if (x >= rightX && y >= bottomY)
    {
        setCursor(Qt::SizeFDiagCursor);
        mouseState = 5;
    }
    else if (x >= leftX && x <= rightX && y >= bottomY)
    {
        setCursor(Qt::SizeVerCursor);
        mouseState = 6;
    }
    else if (x <= leftX && y >= bottomY)
    {
        setCursor(Qt::SizeBDiagCursor);
        mouseState = 7;
    }
    else if (x <= leftX && y <= bottomY && y >= topY)
    {
        setCursor(Qt::SizeHorCursor);
        mouseState = 8;
    }
}

void ScreenCapture::changeRectMask(const QPoint& pos)
{
    if (mouseState == 1)
    {
        rectMask.setTopLeft(pos);
    }
    else if (mouseState == 2)
    {
        rectMask.setTop(pos.y());
    }
    else if (mouseState == 3)
    {
        rectMask.setTopRight(pos);
    }
    else if (mouseState == 4)
    {
        rectMask.setRight(pos.x());
    }
    else if (mouseState == 5)
    {
        rectMask.setBottomRight(pos);
    }
    else if (mouseState == 6)
    {
        rectMask.setBottom(pos.y());
    }
    else if (mouseState == 7)
    {
        rectMask.setBottomLeft(pos);
    }
    else if (mouseState == 8)
    {
        rectMask.setLeft(pos.x());
    }
}


void ScreenCapture::saveFile()
{
    auto filePath = Util::getSaveFilePath();
    if (filePath.isEmpty())
    {
        return;
    }
    auto dpr = devicePixelRatio();
    QRect rr(rectMask.topLeft() * dpr, rectMask.size() * dpr);
    pixScreen.copy(rr).save(filePath);
    closeBtnClick();
}

void ScreenCapture::saveClipboard()
{
    auto dpr = devicePixelRatio();
    QRect rr(rectMask.topLeft() * dpr, rectMask.size() * dpr);
    auto tempImg = pixScreen.copy(rr).toImage();
    Util::saveImgToClipboard(tempImg);
    closeBtnClick();
}

void ScreenCapture::closeBtnClick()
{
    close();
    deleteLater();
}

void ScreenCapture::pinImage()
{
    auto dpr = devicePixelRatio();
    auto pos = rectMask.topLeft();
    QRect rr(rectMask.topLeft() * dpr, rectMask.size() * dpr);
    auto pixmap = pixScreen.copy(rr);
    new PinImage(pos, pixmap);
    closeBtnClick();
}

void ScreenCapture::editImage()
{
    auto dpr = devicePixelRatio();
    QRect rr(rectMask.topLeft() * dpr, rectMask.size() * dpr);
    //auto tempImg = pixScreen.copy(rr);
    auto pix = new QPixmap(pixScreen.copy(rr));
    new MarkImage(pix);
    closeBtnClick();
}
