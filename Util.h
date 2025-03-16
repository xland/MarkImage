#pragma once
#include <QList>
#include <QString>
#include <QFont>
#include <QFontDatabase>

class Util
{
public:
	static QFont* getIconFont(const int& fontSize);
	static QFont* getTextFont(const int& fontSize);
	static QString getSaveFilePath();
	static void saveImgToClipboard(const QImage& img);
};

