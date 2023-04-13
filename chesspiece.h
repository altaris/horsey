#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsWidget>

class ChessPiece : public QGraphicsWidget
{
    Q_OBJECT
  public:
    /**
     * @brief ChessPiece
     * @param filename File name or ressource name of the piece SVG.
     * @param size Size of the piece. Should be the same as the board's
     * ChessBoard::squareSize.
     * @param resolution Size of the internal image onto which the piece SVG
     * will be painted, before that image itself gets painted onto the scene.
     * @param parent
     */
    ChessPiece(const QString& filename,
               int size,
               int resolution = 256,
               QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  private:
    /**
     * @brief filename File name or ressource name of the piece SVG.
     */
    QString filename;
    /**
     * @brief resolution Size of the internal image onto which the piece SVG
     * will be painted, before that image itself gets painted onto the scene
     */
    int resolution;
    /**
     * @brief size Size of the piece. Should be the same as the board's
     * ChessBoard::squareSize.
     */
    int size;
};

#endif // CHESSPIECE_H
