#include "grid.h"
#include "jetcolormap.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <QTimer>
#include <iostream>
#include <cmath>
#include <cassert>

Grid::Grid(QWidget *parent, int sizeX, int sizeY, int gridSize)
    : QWidget{parent}
    , sizeX{sizeX}
    , sizeY{sizeY}
    , gridSize{gridSize}
{
    wndSize = 20;
    directions.resize(wndSize);
    index = wndSize - 1;

    values.resize(gridSize, std::vector<double>(gridSize, 0.0));
    next_values.resize(gridSize, std::vector<double>(gridSize, 0.0));
    velocityField.resize(gridSize, std::vector<Vec2>(gridSize));
    next_velocityField.resize(gridSize, std::vector<Vec2>(gridSize));

    srand(time(NULL));
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            if(i == 0){
                velocityField[i][j].x = 100;
                next_velocityField[i][j].x = 100;
            }
            else if(i == gridSize - 1){
                velocityField[i][j].x = -100;
                next_velocityField[i][j].x = -100;
            }
            else if(j == 0){
                velocityField[i][j].y = 100;
                next_velocityField[i][j].y = 100;
            }
            else if(j == gridSize - 1){
                velocityField[i][j].y = -100;
                next_velocityField[i][j].y = -100;
            }
        }
    }


    diff_rate = 0.01;
    leftClick = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(10);

    image = QImage(sizeX, sizeY, QImage::Format_RGB32);
    clear();
    update();
}

void Grid::addSource(int posx, int posy, double amount)
{
    // Screen coordinates to index conversion as follows
    // y = i
    // x = j

    posx /= sizeX/gridSize;
    posy /= sizeY/gridSize;

    int i = posy;
    int j = posx;

    values[i][j] = amount;
    values[i][j+1] = amount;
    values[i][j-1] = amount;
    values[i+1][j] = amount;
    values[i-1][j] = amount;
}

void Grid::drawGrid()
{
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++) {
            colorCell(i, j, values[i][j]);
        }
    }

    // Update QImage and repaint screen
    update();
}

void Grid::diffuse()
{
    Vec2 vec;
    double local_avg = 0;
    double diff = 0;
    for(int i = 1; i < gridSize-1; i++){
        for(int j = 1; j < gridSize-1; j++){
            vec = velocityField[i][j].normalize(); // Vectors of length 0 are handled during normalization
            /*local_avg = (values[i][j] + values[i-1][j] + values[i+1][j] + values[i][j-1] + values[i][j+1])/5.0;
            diff = local_avg - values[i][j];
            if(diff < 0){
                next_values[i][j] = values[i][j] + diff_rate;
            }
            else if(diff > 0){
                next_values[i][j] = values[i][j] - diff_rate;
            }
            else{
                next_values[i][j] = values[i][j];
            }*/

            double sum = 0;
            if(vec.x > 0 && vec.y > 0){
                sum = (vec.y)*values[i+1][j] + (vec.x)*values[i][j-1];
            }
            else if(vec.x > 0 && vec.y < 0){
                sum = (-vec.y)*values[i-1][j] + (vec.x)*values[i][j-1];
            }
            else if(vec.x < 0 && vec.y < 0){
                sum = (-vec.y)*values[i-1][j] + (-vec.x)*values[i][j+1];
            }
            else if(vec.x < 0 && vec.y > 0){
                sum = (vec.y)*values[i+1][j] + (-vec.x)*values[i][j+1];
            }

            if(std::abs(vec.x) + std::abs(vec.y) == 0) next_values[i][j] = 0;
            else next_values[i][j] = sum/(std::abs(vec.x) + std::abs(vec.y));

            /*
            next_values[i][j] =
                (values[i][j] + values[i-1][j] + values[i+1][j] + values[i][j-1] + values[i][j+1])/5;
            */
        }
    }
    values.swap(next_values);
}

void Grid::advect()
{
    for(int i = 1; i < gridSize-1; i++){
        for(int j = 1; j < gridSize-1; j++){
            next_velocityField[i][j] = (velocityField[i][j] + velocityField[i-1][j] + velocityField[i+1][j] + velocityField[i][j-1] + velocityField[i][j+1])*(1/5.0);
            if(next_velocityField[i][j].length() < 0.1) next_velocityField[i][j] = Vec2(0, 0);
        }
    }
    velocityField.swap(next_velocityField);
}

void Grid::updateGrid()
{
    diffuse();
    advect();
    drawGrid();
}

void Grid::colorCell(int x, int y, double value)
{
    JetColorMap jet;
    int cellSize = sizeX/gridSize;
    for(int i = y*cellSize; i < y*cellSize + cellSize; i++){
        for(int j = x*cellSize; j < x*cellSize + cellSize; j++){
            image.setPixelColor(i, j, jet.getColor(value));
        }
    }
}

void Grid::clear()
{
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            image.setPixel(i, j, qRgb(0, 0, 0));
        }
    }
}

// Events

void Grid::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        leftClick = true;
        addSource(event->pos().x(), event->pos().y(), 1);
    }
    else if(event->button() == Qt::RightButton){
        mousePos.x = event->pos().x();
        mousePos.y = event->pos().y();
        cursorDirection.x = 0;
        cursorDirection.y = 0;
    }
}

void Grid::mouseMoveEvent(QMouseEvent *event)
{
    if(leftClick){
        addSource(event->pos().x(), event->pos().y(), 1);
    }
    else{
        Vec2 currentPos = Vec2(event->pos().x(), event->pos().y());
        Vec2 speed = currentPos - mousePos;
        //qDebug()<<speed.x<<", "<<-speed.y<<": "<<speed.length();
        mousePos = currentPos;
        speed.y *= -1;
        cursorDirection = speed;
        index = (index+1) % wndSize;
        directions[index] = cursorDirection;

        Vec2 smoothDir(0, 0);
        for(Vec2 v : directions){
            smoothDir = smoothDir + v;
        }

        smoothDir = smoothDir * (1/(double)wndSize);

        velocityField[event->pos().y()/(sizeY/gridSize)][event->pos().x()/(sizeX/gridSize)] = smoothDir;
    }
}

void Grid::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        leftClick = false;
    }
}

void Grid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    int cellSize = sizeX/gridSize;

    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            painter.translate(j*cellSize + cellSize/2.0, i*cellSize + cellSize/2.0);
            painter.scale(1, -1);
            QLineF line(0, 0, velocityField[i][j].x, velocityField[i][j].y);
            painter.setPen(Qt::red);
            painter.drawLine(line);

            QPolygon head;
            int h = 10;
            double len = sqrt(velocityField[i][j].x*velocityField[i][j].x + velocityField[i][j].y*velocityField[i][j].y);
            head << QPoint((velocityField[i][j].x - velocityField[i][j].y/len*3), (velocityField[i][j].y + velocityField[i][j].x/len*3))
                 << QPoint((velocityField[i][j].x + velocityField[i][j].y/len*3), (velocityField[i][j].y - velocityField[i][j].x/len*3))
                 << QPoint(velocityField[i][j].x + h * (velocityField[i][j].x/len), velocityField[i][j].y + h * (velocityField[i][j].y/len));

            painter.setPen(Qt::green);
            painter.drawPolygon(head);
            painter.resetTransform();
        }
    }
}


// Move to next time step

void Grid::updateTime()
{
    updateGrid();
}
