#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPainter>
#include <QSvgRenderer>

#include "chesspiece.h"

ChessPiece::ChessPiece(const QString& filename,
                       int size,
                       int resolution,
                       QGraphicsItem* parent)
  : QGraphicsWidget(parent)
  , filename(filename)
  , resolution(resolution)
  , size(size)
{
    setPreferredSize(size, size);
}

void
ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint scenePos = event->scenePos().toPoint();
    QRect boardRect(0, -8 * size, 8 * size, 8 * size);
    if (boardRect.contains(scenePos)) {
        setPos(event->scenePos() - boundingRect().center());
    }
}

void
ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    setCursor(Qt::ClosedHandCursor);
}

void
ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint scenePos = event->scenePos().toPoint();
    int x = scenePos.x();
    int y = scenePos.y();
    x -= x % size;
    y -= y % size + size;
    setPos(x, y);
    setCursor(Qt::OpenHandCursor);
}

void
ChessPiece::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QImage img(resolution, resolution, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter pntr(&img);
    pntr.setRenderHint(QPainter::Antialiasing);
    pntr.setRenderHint(QPainter::SmoothPixmapTransform);
    QSvgRenderer(filename).render(&pntr);
    painter->drawImage(boundingRect(), img);
    // painter->drawRect(boundingRect());
}
