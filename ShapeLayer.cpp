#include <QPainter>
#include <QVBoxLayout>

#include "Util.h"
#include "ShapeLayer.h"
#include "ShapeItem.h"

ShapeLayer::ShapeLayer(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(260);

	auto layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(10, 46, 10, 10);
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addWidget(new ShapeItem(this));
    layout->addStretch();
    setLayout(layout);
}

ShapeLayer::~ShapeLayer()
{
	
}

void ShapeLayer::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());

    p.setBrush(QColor(210, 220, 240));
    QRect header(0, 0, width(), 36);
    p.drawRect(header);
    p.setPen(QPen(QColor(50, 130, 240),0.5));
	p.drawLine(0, 36, width(), 36);
    

    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(50, 130, 240));
    auto font = Util::getIconFont(12);
    p.setFont(*font);
    header.setLeft(10);
    p.drawText(header, QChar(0xe894), Qt::AlignLeft | Qt::AlignVCenter);

    font = Util::getTextFont(12);
    p.setFont(*font);
    header.setLeft(28);
    p.drawText(header, "已绘元素：0", Qt::AlignLeft | Qt::AlignVCenter);
}
