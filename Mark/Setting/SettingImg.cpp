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
#include "./Comp/SettingPosSize.h"
#include "Util.h"
#include "SettingImg.h"

SettingImg::SettingImg(QWidget *parent) : SettingBase(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFixedWidth(220);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(6, 6, 6, 6);

    auto btn = new QPushButton("添加图像", this);
	connect(btn, &QPushButton::clicked, this, &SettingImg::addImg);
    layout->addWidget(btn);

    layout->addWidget(new SettingPosSize(this));
    layout->addStretch();
    setLayout(layout);
}

SettingImg::~SettingImg()
{
}

void SettingImg::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}

void SettingImg::addImg()
{
    QString fileName = QFileDialog::getOpenFileName(this,"打开图像文件","","图像文件 (*.png *.jpg *.jpeg *.bmp)");
    if (fileName.isEmpty()) {
        return;
    }
    auto shapes = Shapes::get();
	auto shape = new ShapeImg(fileName,shapes);
    shapes->add(shape);

	auto canvas = window()->findChild<Canvas*>();
	canvas->addShapeImg(shape);

    auto layer = window()->findChild<Layers*>();
    layer->refreshShapes();
}
