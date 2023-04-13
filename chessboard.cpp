#include <QGraphicsTextItem>
#include <QPainter>
#include <QString>

#include "chessboard.h"

ChessBoard::ChessBoard(int squareSize,
                       const QColor& lightColor,
                       const QColor& darkColor,
                       QGraphicsItem* parent)
  : QGraphicsWidget(parent)
  , squareSize(squareSize)
  , lightColor(lightColor)
  , darkColor(darkColor)
{
    int margin = 5;
    QRect rect(QPoint(-margin, -8 * squareSize - margin),
               QSize(8 * squareSize + 2 * margin, 8 * squareSize + 2 * margin));
    QGraphicsRectItem* margins = new QGraphicsRectItem(rect, this);
    margins->setBrush(Qt::black);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            QRect rect(QPoint(i * squareSize, -(j + 1) * squareSize),
                       QSize(squareSize, squareSize));
            QGraphicsRectItem* square = new QGraphicsRectItem(rect, this);
            QColor color = (i + j) % 2 ? lightColor : darkColor;
            square->setBrush(color);
        }
    }

    for (int i = 1; i <= 8; i++) {
        QString label = QString::number(i);
        QGraphicsTextItem* rankLabel = new QGraphicsTextItem(label, this);
        rankLabel->setDefaultTextColor(Qt::black);
        float h = rankLabel->boundingRect().height();
        float x = 8 * squareSize + margin;
        float y = -i * squareSize + squareSize / 2 - h / 2;
        rankLabel->setPos(x, y);
    }

    char fileNames[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    for (int i = 0; i < 8; i++) {
        QString label(fileNames[i]);
        QGraphicsTextItem* fileLabel = new QGraphicsTextItem(label, this);
        fileLabel->setDefaultTextColor(Qt::black);
        float w = fileLabel->boundingRect().width();
        float x = i * squareSize + squareSize / 2 - w / 2;
        float y = margin;
        fileLabel->setPos(x, y);
    }
}


QPoint
ChessBoard::positionOfSquare(int index) const
{
    int file = index % 8;
    int rank = (index - file) / 8;
    return QPoint(file * squareSize, -rank * squareSize - 100);
}

void
ChessBoard::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    Q_UNUSED(painter);
}
