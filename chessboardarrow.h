#ifndef CHESSBOARDARROW_H
#define CHESSBOARDARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsWidget>

class ChessBoardArrow : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(int startIndex MEMBER _startIndex READ startIndex WRITE
                 setStartIndex NOTIFY startIndexChanged)
    Q_PROPERTY(int endIndex MEMBER _endIndex READ endIndex WRITE setEndIndex
                 NOTIFY endIndexChanged)
    Q_PROPERTY(
      QColor color MEMBER _color READ color WRITE setColor NOTIFY colorChanged)

  public:
    ChessBoardArrow(int startIndex,
                    int endIndex,
                    QColor color,
                    QGraphicsItem* parent = nullptr);

    QColor color() const;
    int endIndex() const;
    int startIndex() const;

    void setColor(QColor newColor);
    void setEndIndex(int newEndIndex);
    void setStartIndex(int newStartIndex);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

  signals:
    void startIndexChanged(int newStartIndex);
    void endIndexChanged(int newEndIndex);
    void colorChanged(const QColor& newColor);

  private:
    int _startIndex;
    int _endIndex;
    QColor _color;
    QGraphicsLineItem* _line;
};

#endif // CHESSBOARDARROW_H
