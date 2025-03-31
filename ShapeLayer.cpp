#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>

#include "Util.h"
#include "ShapeLayer.h"
#include "ShapeItem.h"

ShapeLayer::ShapeLayer(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    setFixedWidth(260);
	auto layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 0, 0, 10);
	shapeLayerBar = new ShapeLayerBar(this);
	layout->addWidget(shapeLayerBar);
    for (size_t i = 0; i < 10; i++)
    {
        auto item = new ShapeItem(this);
        connect(item, &ShapeItem::onClick, this,&ShapeLayer::itemClick);
        layout->addWidget(item);
    }
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
}

void ShapeLayer::itemClick()
{
    auto items = findChildren<ShapeItem*>();
    bool needCheck = false;
    for (size_t i = 0; i < items.length(); i++)
    {
        if (items[i]->isCheck) {
            needCheck = true;
            break;
        }
    }
    if (shapeLayerBar->isChecked != needCheck) {
        shapeLayerBar->isChecked = needCheck;
        shapeLayerBar->update();
    }
}
void ShapeLayer::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        event->acceptProposedAction();
    }
}
void ShapeLayer::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        ShapeItem* source = qobject_cast<ShapeItem*>(event->source());
        if (source) {
            auto l = (QVBoxLayout*)this->layout();   
            auto pos = event->position();
            auto items = findChildren<ShapeItem*>();
            int index = -1;
            for (size_t i = 0; i < items.length(); i++)
            {
                if (pos.y() < items[i]->y() + items[i]->height() / 2) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                index = items.size()-1;
            }
            l->removeWidget(source);
            l->insertWidget(index+1, source);
            event->acceptProposedAction();
        }
    }
}