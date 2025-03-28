#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QVBoxLayout>
#include "Util.h"
#include "ShapeItem.h"

ShapeItem::ShapeItem(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(38);
    setMouseTracking(true);
    setCursor(Qt::CursorShape::PointingHandCursor);
    setAcceptDrops(true);
}

ShapeItem::~ShapeItem()
{
}

void ShapeItem::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    if (isCheck || isHover) 
    {
        p.setPen(QColor(50, 130, 240));
    } 
    else
    {
        p.setPen(Qt::NoPen);
    }
    p.setBrush(QColor(255, 255, 255));
    p.drawRect(rect());
    p.setBrush(Qt::NoBrush);
    p.setPen(isCheck? QColor(50, 130, 240):QColor(88, 88, 88));

    auto font = Util::getIconFont(13);
    p.setFont(*font);

	auto r = rect();
    r.setLeft(10);
    p.drawText(r, QChar(isCheck?0xe896:0xe894), Qt::AlignLeft | Qt::AlignVCenter);

    r.setLeft(36);
    p.drawText(r, QChar(0xe6af), Qt::AlignLeft | Qt::AlignVCenter);

    font = Util::getTextFont(13);
    p.setFont(*font);
    r.setLeft(52);
    p.drawText(r, "多边形：边框：3,填充：无", Qt::AlignLeft | Qt::AlignVCenter);
}

void ShapeItem::enterEvent(QEnterEvent* event)
{
    if (!isHover) {
        isHover = true;
        update();
    }
}

void ShapeItem::leaveEvent(QEvent* event)
{
    if (isHover) {
        isHover = false;
        update();
    }
}

void ShapeItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {      
        dragStartPosition = event->pos();
        isCheck = !isCheck;
        update();
        emit onClick();
    }
}

void ShapeItem::mouseMoveEvent(QMouseEvent* event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-draggablewidget", QByteArray());
    drag->setMimeData(mimeData);
    drag->setPixmap(grab());
    drag->setHotSpot(QPoint(width() / 2, height() / 2));
    drag->exec(Qt::MoveAction);
}

void ShapeItem::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        event->acceptProposedAction();
    }
}

void ShapeItem::dropEvent(QDropEvent* event)
{
    //todo 这个方法应该放到ShapeLayer中
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        ShapeItem* source = qobject_cast<ShapeItem*>(event->source());
        if (source && source != this) {
            QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(parentWidget()->layout());
            if (layout) {
                int sourceIndex = layout->indexOf(source);
                int targetIndex = layout->indexOf(this);

                // 交换位置
                layout->removeWidget(source);
                layout->insertWidget(targetIndex, source);

                event->acceptProposedAction();
            }
        }
    }
}