#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grid(new Grid(this, 600, 600, 30))
{
    setCentralWidget(grid);

    resize(600, 600);
    /*ui->setupUi(this);

    int sizeX = 600;
    int sizeY = 600;

    int gridSize = 40;
    int cellSize = sizeX/gridSize;

    QImage image = QImage(sizeX, sizeY, QImage::Format_RGB32);

    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            image.setPixel(i*cellSize, j*cellSize, qRgb(255, 0, 0));
        }
    }

    QGraphicsScene *graphic = new QGraphicsScene(this);
    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

