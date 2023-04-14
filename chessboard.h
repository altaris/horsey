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

    QRectF boundingRect() const override;

    /**
     * @brief movePiece Moves a piece from a square (specified by its index) to
     * another square.
     * @param from
     * @param to
     * @return `false` if there is no piece in `from`, or if there is another
     * piece in `to`.
     */
    bool movePiece(int from, int to);

    /**
     * @brief Graphics scene coordinates of a given square
     * @param index Square index, from a1 (index 0) to a2 (index 1) to ... to h8
     * (index 63)
     * @return Graphics scene coordinates of the given square
     * @todo Throw if index is invalid
     */
    QPoint positionOfSquare(int index) const;

    /**
     * @brief removePiece Removes a piece from a given square (specified by its
     * index).
     * @param squareIndex
     * @return `false` if no piece was present, otherwise `true`.
     *
     * Wether or not a piece is present on that square is checked using
     * ChessBoard::lastValidPieceIndex;
     */
    bool removePiece(int index);

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  private:
    /**
     * @brief pieceAtSquare Returns the piece at a given square.
     * @param index Square index (from a1 to a2 to ...
     * to h8).
     * @return The piece pointer, or `nullptr` if no piece is present.
     * @warning This method does not consider the actual position of the piece
     * in the graphics scene, but rather the last valid square of each piece.
     * This prevents some weird behavior when pieces are being dragged over the
     * board.
     */
    ChessPiece* pieceAtSquare(int index) const;

    /**
     * @brief pieceCanMove Wether a piece can move to a given square (specified
     * by its index).
     * @param piece
     * @param to
     * @return
     * @todo Implement game logic (or most probably, raise a PieceMoveRequest to
     * be processed and accepted/rejected by another class up the chain.
     */
    bool pieceCanMove(ChessPiece* piece, int to) const;

    /**
     * @brief setSquareHighlighted Set highlight status of a square
     * @param index
     * @todo Allow to change highlight color
     */
    void setSquareHighlighted(int index, bool highlighted = true);

    /**
     * @brief squareIndexOfPoint Returns the square index (from a1 to a2 to ...
     * to h8) of the square containing a given point.
     * @param point
     * @return The index, which is an number between 0 and 63. Returns -1 if the
     * point is not on this board.
     */
    int squareIndexOfPoint(const QPoint& point) const;

    int squareIndexOfPoint(const QPointF& point) const;

    /**
     * @brief unhighlightAllSquares Reverts the color of all squares.
     */
    void unhighlightAllSquares();

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

    QHash<ChessPiece*, int> lastValidPieceIndex;

    /**
     * @brief squares Squares of the board, sorted by index (i.e a1 to a2 to ...
     * to h8).
     */
    QList<QGraphicsRectItem*> squares;

    /**
     * @brief currentPiece Piece that is currently being dragged;
     */
    ChessPiece* currentPiece = nullptr;
};

#endif // CHESSBOARD_H
