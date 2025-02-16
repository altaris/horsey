#include "chessboardarrow.h"

ChessBoardArrow::ChessBoardArrow(int startIndex,
                                 int endIndex,
                                 QColor color,
                                 QGraphicsItem* parent)
  : QGraphicsWidget(parent)
  , _startIndex(startIndex)
  , _endIndex(endIndex)
  , _color(color)
{
}

QColor
ChessBoardArrow::color() const
{
    return _color;
}

int
ChessBoardArrow::endIndex() const
{
    return _endIndex;
}

void
ChessBoardArrow::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*)
{
    Q_UNUSED(painter)
}

void
ChessBoardArrow::setColor(QColor newColor)
{
    _color = newColor;
}

void
ChessBoardArrow::setEndIndex(int newEndIndex)
{
    _endIndex = newEndIndex;
}

void
ChessBoardArrow::setStartIndex(int newStartIndex)
{
    _startIndex = newStartIndex;
}

int
ChessBoardArrow::startIndex() const
{
    return _startIndex;
}
