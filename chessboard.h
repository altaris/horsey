#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chesspiece.h"
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

    /**
     * @brief addPiece Adds a piece onto the board.
     * @return A pointer to the piece that was added.
     * @todo Fail if the square is occupied.
     */
    ChessPiece* addPiece(ChessPiece::Piece piece,
                         ChessPiece::Color color,
                         int squareIndex);

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
     * @brief Returns the square index (from a1 to a2 to ... to h8) of a given
     * piece.
     * @return The index, which is an number between 0 and 63. Returns -1 if the
     * piece does not belong or is not on this board.
     *
     * The index is calculated from the position (in the graphics scene) of the
     * piece.
     */
    int squareIndexOfPiece(ChessPiece* piece) const;

  private slots:
    void onPieceRequestToMove(QPointF newPosition);

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
    QSet<ChessPiece*> pieces;
    QHash<ChessPiece*, int> lastValidPieceIndex;
};

#endif // CHESSBOARD_H
