#ifndef SCREEN_H
#define SCREEN_H

#include "vec2.h"
#include <QWidget>

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QImage image;
    QTimer *timer;

    int sizeX;
    int sizeY;

    Vec2 mousePos;
    Vec2 cursorDirection;

    std::vector<QPoint> path;
    std::vector<Vec2> directions;
    unsigned int index;
    unsigned int wndSize;

private slots:
    void updateScreen();
};

#endif // SCREEN_H
