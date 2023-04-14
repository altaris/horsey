#include <QCursor>
#include <QGraphicsSceneMouseEvent>
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
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            QRect rect(QPoint(i * squareSize, -(j + 1) * squareSize),
                       QSize(squareSize, squareSize));
            QGraphicsRectItem* square = new QGraphicsRectItem(rect, this);
            QColor color = (i + j) % 2 ? lightColor : darkColor;
            square->setBrush(color);
            squares.append(square);
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
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    setHandlesChildEvents(true);
}

ChessPiece*
ChessBoard::addPiece(ChessPiece::Piece piece,
                     ChessPiece::Color color,
                     int squareIndex)
{
    ChessPiece* cp = new ChessPiece(
      piece, color, ChessPiece::MeridaNew, squareSize, 256, this);
    cp->setPos(positionOfSquare(squareIndex));
    lastValidPieceIndex.insert(cp, squareIndex);
    return cp;
}

QRectF
ChessBoard::boundingRect() const
{
    return QRect(QPoint(0, -8 * squareSize),
                 QSize(8 * squareSize, 8 * squareSize));
}

void
ChessBoard::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint scenePos = event->scenePos().toPoint();
    if (!boundingRect().contains(scenePos)) {
        return;
    }
    int index = squareIndexOfPoint(scenePos);
    if (event->buttons() & Qt::LeftButton) {
        ChessPiece* piece =
          currentPiece == nullptr ? pieceAtSquare(index) : currentPiece;
        if (piece == nullptr) {
            return;
        }
        piece->setPos(scenePos - piece->boundingRect().center());
        unhighlightAllSquares();
        setSquareHighlighted(lastValidPieceIndex[piece]);
        setSquareHighlighted(index);
    }
}

void
ChessBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint scenePos = event->scenePos().toPoint();
    if (!boundingRect().contains(scenePos)) {
        return;
    }
    int index = squareIndexOfPoint(scenePos);
    if (event->button() == Qt::LeftButton) {
        ChessPiece* piece =
          currentPiece == nullptr ? pieceAtSquare(index) : currentPiece;
        if (piece == nullptr) {
            return;
        }
        currentPiece = piece;
        setSquareHighlighted(index);
        setCursor(Qt::ClosedHandCursor);
    }
}

void
ChessBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint scenePos = event->scenePos().toPoint();
    int index = squareIndexOfPoint(scenePos);
    if (event->button() == Qt::LeftButton) {
        ChessPiece* piece =
          currentPiece == nullptr ? pieceAtSquare(index) : currentPiece;
        if (piece != nullptr) {
            if (pieceCanMove(piece, index)) {
                movePiece(lastValidPieceIndex[piece], index);
            } else {
                piece->setPos(positionOfSquare(lastValidPieceIndex[piece]));
            }
        }
        currentPiece = nullptr;
    }
    unhighlightAllSquares();
    setCursor(Qt::OpenHandCursor);
}

bool
ChessBoard::movePiece(int from, int to)
{
    ChessPiece* piece = pieceAtSquare(from);
    if (piece == nullptr || pieceAtSquare(to) != nullptr) {
        return false;
    }
    piece->setPos(positionOfSquare(to));
    lastValidPieceIndex[piece] = to;
    return true;
}

ChessPiece*
ChessBoard::pieceAtSquare(int index) const
{
    if (index < 0 or index >= 64) {
        qWarning() << Q_FUNC_INFO << "Invalid square index" << index;
        return nullptr;
    }
    for (auto it = lastValidPieceIndex.constKeyValueBegin();
         it != lastValidPieceIndex.constKeyValueEnd();
         it++) {
        if (it->second == index) {
            return it->first;
        }
    }
    return nullptr;
}

bool
ChessBoard::pieceCanMove(ChessPiece* piece, int to) const
{
    // Mock implementation
    Q_UNUSED(piece);
    bool noPiecePresent = pieceAtSquare(to) == nullptr;
    return to >= 0 && noPiecePresent;
}

QPoint
ChessBoard::positionOfSquare(int index) const
{
    int file = index % 8;
    int rank = (index - file) / 8;
    return QPoint(file * squareSize, -rank * squareSize - 100);
}

bool
ChessBoard::removePiece(int index)
{
    ChessPiece* piece = pieceAtSquare(index);
    if (piece == nullptr) {
        return false;
    }
    lastValidPieceIndex.remove(piece);
    piece->deleteLater();
    return true;
}

void
ChessBoard::setSquareHighlighted(int index, bool highlighted)
{
    if (index < 0 || index >= 64) {
        qWarning() << Q_FUNC_INFO << "Invalid index" << index;
    }
    int i = index % 8;
    int j = index / 8;
    QColor color =
      highlighted ? Qt::green : ((i + j) % 2 ? lightColor : darkColor);
    squares[index]->setBrush(color);
}

int
ChessBoard::squareIndexOfPoint(const QPoint& point) const
{
    if (!boundingRect().contains(point)) {
        return -1;
    }
    int x = point.x() / squareSize;
    int y = -point.y() / squareSize;
    return 8 * y + x;
}

int
ChessBoard::squareIndexOfPoint(const QPointF& point) const
{
    return squareIndexOfPoint(point.toPoint());
}

void
ChessBoard::unhighlightAllSquares()
{
    for (int i = 0; i < 64; i++) {
        setSquareHighlighted(i, false);
    }
}
