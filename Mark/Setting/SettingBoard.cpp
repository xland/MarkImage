#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

#include "../Canvas/Canvas.h"
#include "../Shape/Shapes.h"
#include "../Shape/ShapeImg.h"
#include "../Tool/ToolBar.h"
#include "../Layer/Layers.h"
#include "Comp/SettingSize.h"
#include "Util.h"
#include "SettingBoard.h"

SettingBoard::SettingBoard(QWidget *parent) : SettingBase(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFixedWidth(220);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(6, 6, 6, 6);
    auto ss = new SettingSize(this);
    layout->addWidget(ss);
    layout->addStretch();
    setLayout(layout);
}

SettingBoard::~SettingBoard()
{
}

void SettingBoard::setVal(int w, int h)
{
    auto les = findChildren<QLineEdit*>();
    les[0]->setText(QString::number(w));
    les[1]->setText(QString::number(h));
}

void SettingBoard::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());

    //p.setBrush(Qt::NoBrush);
    //p.setPen(QColor(80, 80, 80));
    //auto font = Util::getIconFont(11);
    //p.setFont(*font);
    ////p.drawText(QPoint(22, 76), QChar(0xe61f)); 
    //p.drawText(QPoint(22, 76), QChar(0xe635));
}

void SettingBoard::showEvent(QShowEvent* event)
{
    auto canvas = window()->findChild<Canvas*>();
    auto les = findChildren<QLineEdit*>();
    auto w = QString::number(canvas->width());
    auto h = QString::number(canvas->height());
    les[0]->setText(w);
    les[1]->setText(h);
	auto ss = findChild<SettingSize*>();
    connect(ss, &SettingSize::valueChanged, this, [this](int w, int h) {
        auto canvas = window()->findChild<Canvas*>();
        if (canvas) {
        	canvas->setFixedSize(w, h);
        }
        //auto les = findChildren<QLineEdit*>();
        //les[0]->setText(QString::number(w));
        //les[1]->setText(QString::number(h));
    });
}
