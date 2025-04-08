#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>


#include "Util.h"
#include "../Canvas/Canvas.h"
#include "ShapeLayer.h"
#include "ShapeItem.h"

ShapeLayer::ShapeLayer(QWidget *parent) : QWidget(parent)
{
    setVisible(false);
    setAcceptDrops(true);
    setFixedWidth(260);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    shapeLayerBar = new ShapeLayerBar(this);
    connect(shapeLayerBar, &ShapeLayerBar::onClick, this, &ShapeLayer::barClick);
    layout->addWidget(shapeLayerBar);
    listCtrl = new QScrollArea(this);
    listCtrl->setStyleSheet(R"(QScrollArea{border: none; background: transparent;}
QScrollBar:vertical {
    border: none;
    background: transparent; /* 滚动条背景颜色 */
    width: 6px;         /* 滚动条宽度 */
    margin: 0px 0px 0px 0px;
}
QScrollBar::handle:vertical {
    background: #dddddd; /* 滑块颜色 */
    min-height: 20px;    /* 滑块最小高度 */
    border-radius: 2px;  /* 圆角 */
}
QScrollBar::handle:vertical:hover {
    background: #cccccc; /* 鼠标悬停时的滑块颜色 */
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;         /* 移除上下箭头 */
    background: none;
}
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
    background: none;     /* 滑块上下区域的背景 */
})");
    layout->addWidget(listCtrl);
    setLayout(layout);

 //   QWidget* contentWidget = widget();
 //   if (contentWidget) {
 //       delete contentWidget;
 //   }
 //   contentWidget = new QWidget(this);
 //   contentWidget->setFixedWidth(this->width());
 //   QVBoxLayout* layout = new QVBoxLayout(this);
 //   layout->setSpacing(8);
 //   layout->setContentsMargins(0, 0, 0, 10);
	//shapeLayerBar = new ShapeLayerBar(this);
 //   connect(shapeLayerBar, &ShapeLayerBar::onClick, this, &ShapeLayer::barClick);
	//layout->addWidget(shapeLayerBar);
 //   setLayout(layout);
}

ShapeLayer::~ShapeLayer()
{

}

void ShapeLayer::refreshShapes()
{
    if (itemBox) {
        delete itemBox;
    }
    itemBox = new QWidget(listCtrl);
    itemBox->setFixedWidth(this->width());
    itemBox->setStyleSheet(R"(background:transparent;margin:0px;padding:0px;)");
    auto layout = new QVBoxLayout(itemBox);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 8, 0, 8);
    auto shapes = Shapes::get();
    for (size_t i = 0; i < shapes->shapes.size(); i++)
    {
        auto item = new ShapeItem(this);
        item->index = i;
        connect(item, &ShapeItem::onClick, this, &ShapeLayer::itemClick);
        layout->insertWidget(i+1, item);
    }
    layout->addStretch();
    listCtrl->setWidget(itemBox);
    if (!isVisible()) {
        show();
    }
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
        auto canvas = parentWidget()->findChild<Canvas*>();
        if (needCheck) {
            canvas->changeState(3);
        }
        else {
            canvas->changeState(1);
        }
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