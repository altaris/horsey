#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPainter>
#include <QSvgRenderer>

#include "chesspiece.h"

ChessPiece::ChessPiece(Piece piece,
                       Color color,
                       Set set,
                       int size,
                       int resolution,
                       QGraphicsItem* parent)
  : QGraphicsWidget(parent)
  , piece(piece)
  , color(color)
  , set(set)
  , size(size)
  , resolution(resolution)
{
    setPreferredSize(size, size);
}

void
ChessPiece::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QImage img(resolution, resolution, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter pntr(&img);
    pntr.setRenderHint(QPainter::Antialiasing);
    pntr.setRenderHint(QPainter::SmoothPixmapTransform);
    QSvgRenderer(pieceImagePath()).render(&pntr);
    painter->drawImage(boundingRect(), img);
}

QString
ChessPiece::pieceImagePath() const
{
    QString c(color == Black ? "b" : "w");
    const char pieces[6] = { 'K', 'Q', 'B', 'N', 'R', 'P' };
    QString p(pieces[piece]);
    QString s;
    switch (set) {
        case Alpha:
            s = "alpha";
            break;
        case Companion:
            s = "companion";
            break;
        case Leipzig:
            s = "leipzig";
            break;
        case MeridaNew:
            s = "merida_new";
            break;
    }
    return QString(":/rc/pieces/%1/%2%3.svg").arg(s, c, p);
}
