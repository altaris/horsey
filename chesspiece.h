#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsWidget>

class ChessPiece : public QGraphicsWidget
{
    Q_OBJECT
  public:
    /**
     * @brief Chess piece kinds
     */
    enum Piece
    {
        King = 0,
        Queen = 1,
        Bishop = 2,
        Knight = 3,
        Rook = 4,
        Pawn = 5,
    };

    /**
     * @brief Piece color
     */
    enum Color
    {
        White,
        Black
    };

    /**
     * @brief Chess piece set
     */
    enum Set
    {
        Alpha,
        Companion,
        Leipzig,
        MeridaNew,
    };

    /**
     * @brief ChessPiece
     * @param piece
     * @param color
     * @param set Chess piece set name
     * @param size Size of the piece. Should be the same as the board's
     * ChessBoard::squareSize.
     * @param resolution Size of the internal image onto which the piece SVG
     * will be painted, before that image itself gets painted onto the scene.
     * @param parent
     *
     * @warning Pieces should be added to a board using ChessBoard::addPiece
     * rather than be constructed explicitely.
     */
    ChessPiece(Piece piece,
               Color color,
               Set set,
               int size,
               int resolution = 256,
               QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

  signals:
    void requestToMove(QPointF newPosition);

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  private:
    /**
     * @brief pieceImagePath Returns the ressource path of this piece, which is
     * determined from its ChessPiece::piece, ChessPiece::color, and
     * ChessPiece::set.
     */
    QString pieceImagePath() const;

  private:
    Piece piece;
    Color color;
    Set set;
    /**
     * @brief size Size of the piece. Should be the same as the board's
     * ChessBoard::squareSize.
     */
    int size;
    /**
     * @brief resolution Size of the internal image onto which the piece SVG
     * will be painted, before that image itself gets painted onto the scene
     */
    int resolution;
};

#endif // CHESSPIECE_H
