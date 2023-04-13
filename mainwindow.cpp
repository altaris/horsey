#include <QGraphicsScene>

#include "chessboard.h"
#include "chesspiece.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    ChessBoard* board = new ChessBoard(100, Qt::white, Qt::blue);
    scene->addItem(board);
    ui->graphicsView->ensureVisible(board->boundingRect(), 10, 10);

    ChessPiece* bishop =
      new ChessPiece(":/rc/pieces/merida_new/wB.svg", 100, 256, board);
    bishop->setPos(board->positionOfSquare(10));

    ChessPiece* king =
      new ChessPiece(":/rc/pieces/merida_new/bK.svg", 100, 256, board);
    king->setPos(board->positionOfSquare(30));
}

MainWindow::~MainWindow()
{
    delete ui;
}
