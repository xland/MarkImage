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
    connect(shapeLayerBar, &ShapeLayerBar::onClick, this, &ShapeLayer::barClick);
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
void ShapeLayer::barClick()
{
    auto items = findChildren<ShapeItem*>();
    for (size_t i = 0; i < items.length(); i++)
    {
        if (items[i]->isCheck == shapeLayerBar->isChecked) {
            continue;
        }
		items[i]->isCheck = shapeLayerBar->isChecked;
		items[i]->update();
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
            int index = -1;
            bool flag = false;
            for (int i = 0; i < l->count(); ++i) {
                auto obj = l->itemAt(i);
                if (!obj || !obj->widget()) continue;
                auto item = qobject_cast<ShapeItem*>(obj->widget());
				if (item == source) continue;
                if (item) {
                    index += 1;
                    if (pos.y() < item->y() + item->height() / 2) {
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag) {
                index += 1;
            }
            l->removeWidget(source);
            l->insertWidget(index+1, source);
            event->acceptProposedAction();
        }
    }
}