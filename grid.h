#ifndef GRID_H
#define GRID_H

#include "vec2.h"
#include <QWidget>

class Grid : public QWidget
{
    Q_OBJECT
public:
    Grid(QWidget *parent = nullptr, int sizeX = 600, int sizeY = 600, int gridSize = 40);
    void addSource(int x, int y, double amount);
    void drawGrid();
    void updateGrid();
    void colorCell(int x, int y, double value);
    void diffuse();
    void advect();
    void clear();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    int sizeX;
    int sizeY;
    QImage image;
    QTimer *timer;

    bool leftClick;
    Vec2 mousePos;
    Vec2 cursorDirection;
    std::vector<Vec2> directions;
    unsigned int index;
    unsigned int wndSize;

    int gridSize;
    double diff_rate;

    std::vector<std::vector<double>> values;
    std::vector<std::vector<double>> next_values;

    std::vector<std::vector<Vec2>> velocityField;
    std::vector<std::vector<Vec2>> next_velocityField;

private slots:
    void updateTime();
};

#endif // GRID_H
