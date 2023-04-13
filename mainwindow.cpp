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

    board->addPiece(ChessPiece::Bishop, ChessPiece::White, 10);
    board->addPiece(ChessPiece::King, ChessPiece::Black, 30);
}

MainWindow::~MainWindow()
{
    delete ui;
}
