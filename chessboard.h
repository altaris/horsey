#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsWidget>

/**
 * @brief Graphical representation of a chess board. Includes squares, margins,
 * coordinates, but not pieces. See ChessPiece for that.
 */
class ChessBoard : public QGraphicsWidget
{
    Q_OBJECT
  public:
    ChessBoard(int squareSize,
               const QColor& lightColor,
               const QColor& darkColor,
               QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

    /**
     * @brief Graphics scene coordinates of a given square
     * @param index Square index, from a1 (index 0) to a2 (index 1) to ... to h8
     * (index 63)
     * @return Graphics scene coordinates of the given square
     * @todo Throw if index is invalid
     */
    QPoint positionOfSquare(int index) const;

  private:
    /**
     * @brief squareSize Width (or height) of a single square of the board.
     *
     * The whole board will therefore by `(8 * squareSize)` by `(8 *
     * squareSize)`.
     */
    int squareSize;
    /**
     * @brief lightColor Color of the light squares.
     */
    QColor lightColor;
    /**
     * @brief darkColor Color of the dark squares.
     */
    QColor darkColor;
};

#endif // CHESSBOARD_H
