#include <QFileDialog>
#include <QStandardPaths>
#include <Windows.h>
#include <QMessageBox>

#include "Util.h"


QFont* Util::getIconFont(const int& fontSize)
{
    static QFont font = []() {
        int fontId = QFontDatabase::addApplicationFont(":/Res/iconfont.ttf");
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont iconFont(fontName);
        iconFont.setStyleStrategy(QFont::PreferAntialias);
        iconFont.setHintingPreference(QFont::PreferNoHinting);
        return iconFont;
        }();
    font.setPixelSize(fontSize);
    return &font;
}

QFont* Util::getTextFont(const int& fontSize)
{
    static QFont font = []() {
        QFont font("Microsoft YaHei");
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setHintingPreference(QFont::PreferNoHinting);
        return font;
        }();
    font.setPixelSize(fontSize);
    return &font;
}


QString Util::getSaveFilePath()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    auto filePath = QDir::cleanPath(desktopPath + QDir::separator() + "Img" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + ".png");
    filePath = QFileDialog::getSaveFileName(nullptr, "保存文件", filePath, "MarkImage (*.png)");
    return filePath;
}

void Util::saveImgToClipboard(const QImage& img)
{
    auto width = img.width();
    auto height = img.height();
    HDC screenDC = GetDC(nullptr);
    HDC memoryDC = CreateCompatibleDC(screenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(screenDC, width, height);
    DeleteObject(SelectObject(memoryDC, hBitmap));
    BITMAPINFO bitmapInfo = { 0 };
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    //pixmap.addr() 像素数据的地址
    SetDIBitsToDevice(memoryDC, 0, 0, width, height, 0, 0, 0, height, img.bits(), &bitmapInfo, DIB_RGB_COLORS);
    if (!OpenClipboard(nullptr)) {
        QMessageBox::warning(nullptr, "Error", "Failed to open clipboard when save to clipboard.", QMessageBox::StandardButton::Ok);
        return;
    }
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
    ReleaseDC(nullptr, screenDC);
    DeleteDC(memoryDC);
    DeleteObject(hBitmap);
}