#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

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
    layout->addWidget(new SettingSize(this));
    layout->addStretch();
    setLayout(layout);
}

SettingBoard::~SettingBoard()
{
}

void SettingBoard::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}
