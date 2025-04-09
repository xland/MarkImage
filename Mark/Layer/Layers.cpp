#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>


#include "Util.h"
#include "../Canvas/Canvas.h"
#include "Layers.h"
#include "LayerItem.h"

Layers::Layers(QWidget *parent) : QWidget(parent)
{
    setVisible(false);
    setAcceptDrops(true);
    setFixedWidth(260);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layerBar = new LayerBar(this);
    connect(layerBar, &LayerBar::onClick, this, &Layers::barClick);
    layout->addWidget(layerBar);
    listCtrl = new QScrollArea(this);
    listCtrl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listCtrl->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listCtrl->setStyleSheet(R"(QScrollArea{border: none; background: transparent;}
QScrollBar:vertical { border: none; background: transparent; /* 滚动条背景颜色 */
    width: 6px; /* 滚动条宽度 */ margin: 0px 0px 0px 0px; }
QScrollBar::handle:vertical { background: #dddddd; /* 滑块颜色 */
    min-height: 20px;/* 滑块最小高度 */ border-radius: 2px;  /* 圆角 */ }
QScrollBar::handle:vertical:hover { background: #cccccc; /* 鼠标悬停时的滑块颜色 */ }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px; /* 移除上下箭头 */ background: none; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
    background: none;/* 滑块上下区域的背景 */ })");
    layout->addWidget(listCtrl);
    setLayout(layout);
}

Layers::~Layers()
{

}

void Layers::refreshShapes()
{
    if (itemBox) {
        delete itemBox;
    }
    itemBox = new QWidget(listCtrl);
    itemBox->setFixedWidth(this->width());
    itemBox->setStyleSheet(R"(background:transparent;margin:0px;padding:0px;)");
    auto layout = new QVBoxLayout(itemBox);
    layout->setSpacing(6);
    layout->setContentsMargins(8, 8, 8, 8);
    auto shapes = Shapes::get();
    for (size_t i = 0; i < shapes->shapes.size(); i++)
    {
        auto item = new LayerItem(shapes->shapes[i], this);
        item->index = i;
        connect(item, &LayerItem::onClick, this, &Layers::itemClick);
        layout->insertWidget(0, item);
    }
    layout->addStretch();
    listCtrl->setWidget(itemBox);
    if (!isVisible()) {
        show();
    }
}

void Layers::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setBrush(QColor(238, 242, 255));
    p.setPen(Qt::NoPen);
    p.drawRect(rect());
}

void Layers::itemClick()
{
    auto items = findChildren<LayerItem*>();
    bool needCheck = false;
    for (size_t i = 0; i < items.length(); i++)
    {
        if (items[i]->isCheck) {
            needCheck = true;
            break;
        }
    }
    if (layerBar->isChecked != needCheck) {
        layerBar->isChecked = needCheck;
        layerBar->update();
        auto canvas = parentWidget()->findChild<Canvas*>();
        if (needCheck) {
            canvas->changeState(3);
        }
        else {
            canvas->changeState(1);
        }
    }
}
void Layers::barClick()
{
    auto items = findChildren<LayerItem*>();
    for (size_t i = 0; i < items.length(); i++)
    {
        if (items[i]->isCheck == layerBar->isChecked) {
            continue;
        }
		items[i]->isCheck = layerBar->isChecked;
		items[i]->update();
    }
    auto canvas = parentWidget()->findChild<Canvas*>();
    if (layerBar->isChecked)
    {
        canvas->changeState(3);
    }
    else {
        canvas->changeState(1);
    }
}
void Layers::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        event->acceptProposedAction();
    }
}
void Layers::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        LayerItem* source = qobject_cast<LayerItem*>(event->source());
        if (source) {
            auto l = (QVBoxLayout*)itemBox->layout();
            auto pos = event->position();
            pos.setY(pos.y() - 40);
            int index = 0;
            for (int i = 0; i < l->count(); ++i) {
                auto obj = l->itemAt(i);
                if (!obj || !obj->widget()) continue;
                auto item = qobject_cast<LayerItem*>(obj->widget());
				if (item == source) continue;
                index = i;
                if (item) {
                    if (pos.y() < item->y() + item->height() / 2) {
                        break;
                    }
                }
            }
            l->removeWidget(source);
            l->insertWidget(index, source);
            event->acceptProposedAction();
        }
    }
}