#include <Windows.h>
#include <dwmapi.h>
#include <QTimer>
#include <QVBoxLayout>
#include <QEvent>
#include <QApplication>

#include "ContentBox.h"
#include "StatusBar.h"
#include "MarkImage.h"
#include "./Title/TitleBar.h"

MarkImage::MarkImage(QPixmap* pixmap, QWidget* parent) : QWidget(parent), pixmap{ pixmap }
{
    titleBar = new TitleBar(this);
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(titleBar);
	layout->addWidget(new ContentBox(this));
    layout->addWidget(new StatusBar(this));
    setLayout(layout);

    setAttribute(Qt::WA_DontCreateNativeAncestors);
    HWND hwnd = reinterpret_cast<HWND>(winId());
    MARGINS margins = { 1, 1, 1, 1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    int value = 2;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &value, sizeof(value));
    DwmSetWindowAttribute(hwnd, DWMWA_ALLOW_NCPAINT, &value, sizeof(value));

    LONG style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLongPtr(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    setGeometry(0, 0, 1200, 800);
    //show();
    showMaximized();
}

MarkImage::~MarkImage()
{
    delete pixmap;
}

bool MarkImage::nativeEvent(const QByteArray& eventType, void* message, qintptr* result) {
    MSG* msg = static_cast<MSG*>(message);
    switch (msg->message) {
        case WM_GETMINMAXINFO: {
            MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(msg->lParam);
            RECT workArea;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
            mmi->ptMaxPosition.x = workArea.left;
            mmi->ptMaxPosition.y = workArea.top;
            mmi->ptMaxSize.x = workArea.right - workArea.left;
            mmi->ptMaxSize.y = workArea.bottom - workArea.top;
            *result = 0;
            return true;
        }
        case WM_NCHITTEST: {
            const static int borderWidth = 8;
            QPoint pos = mapFromGlobal(QCursor::pos());
            bool left = pos.x() < borderWidth;
            bool right = pos.x() > width() - borderWidth;
            bool top = pos.y() < borderWidth;
            bool bottom = pos.y() > height() - borderWidth;
            if (left && top) *result = HTTOPLEFT;
            else if (right && top) *result = HTTOPRIGHT;
            else if (left && bottom) *result = HTBOTTOMLEFT;
            else if (right && bottom) *result = HTBOTTOMRIGHT;
            else if (left) *result = HTLEFT;
            else if (right) *result = HTRIGHT;
            else if (top) *result = HTTOP;
            else if (bottom) *result = HTBOTTOM;
            else if (pos.x() < titleBar->btnMin->pos().x() && pos.y() < 34) {
                *result = HTCAPTION;
            }
            else {
                *result = HTCLIENT;
            }
            return true;
        }
        case WM_NCLBUTTONDBLCLK: {
            QPoint pos = mapFromGlobal(QCursor::pos());
            if (pos.x() < titleBar->btnMin->pos().x() && pos.y() < 34) {
                if (windowState() & Qt::WindowMaximized) {
					showNormal();
                }
                else {
                    showMaximized();
                }
                return true;
            }
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void MarkImage::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (windowState() & Qt::WindowMaximized) {
            titleBar->btnMax->code = 0xe6ea;
            titleBar->update();
        }
        else {
            titleBar->btnMax->code = 0xe6e5;
            titleBar->update();
        }
    }
    QWidget::changeEvent(event);
}
void MarkImage::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);
    HWND hwnd = reinterpret_cast<HWND>(winId());
    LPARAM pos = MAKELPARAM(1, 1);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, pos);
    PostMessage(hwnd, WM_LBUTTONUP, 0, pos);
}

void MarkImage::mousePressEvent(QMouseEvent* event)
{

}

void MarkImage::mouseMoveEvent(QMouseEvent* event)
{

}

void MarkImage::mouseReleaseEvent(QMouseEvent* event)
{

}

