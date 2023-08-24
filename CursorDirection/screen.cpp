#include "screen.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <qtimer.h>

Screen::Screen(QWidget *parent)
    : QWidget{parent}
    , sizeX{600}
    , sizeY{600}
{
    image = QImage(sizeX, sizeY, QImage::Format_RGB32);
    image.fill(qRgb(0, 0, 0));

    wndSize = 10;
    path.resize(2);
    directions.resize(wndSize);
    index = wndSize - 1;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScreen()));
    timer->start(10);
    update();
}

void Screen::updateScreen()
{
    update();
}

void Screen::mousePressEvent(QMouseEvent *event)
{
    mousePos.x = event->pos().x();
    mousePos.y = event->pos().y();

    path.push_back(QPoint(mousePos.x, mousePos.y));
    cursorDirection.x = 0;
    cursorDirection.y = 0;
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    Vec2 currentPos = Vec2(event->pos().x(), event->pos().y());
    Vec2 speed = currentPos - mousePos;
    //qDebug()<<speed.x<<", "<<-speed.y<<": "<<speed.length();
    mousePos = currentPos;
    speed.y *= -1;
    cursorDirection = speed;
    path.push_back(QPoint(mousePos.x, mousePos.y));
    index = (index+1) % wndSize;
    directions[index] = cursorDirection;
}

void Screen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    painter.setPen(Qt::red);
    for(unsigned int i = 1; i < path.size(); i++){
        painter.drawLine(path[i-1], path[i]);
    }

    QPen pen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    painter.translate(mousePos.x, mousePos.y);
    painter.scale(1, -1);

    Vec2 smoothDir(0, 0);
    for(Vec2 v : directions){
        smoothDir = smoothDir + v;
    }

    smoothDir = smoothDir * (1/(double)wndSize);

    QLineF line(0, 0, smoothDir.x*10, smoothDir.y*10);
    painter.drawLine(line);
    painter.setPen(Qt::red);

    QPolygon head;
    int h = 10;
    double len = smoothDir.length();
    int x = smoothDir.x*10;
    int y = smoothDir.y*10;
    head << QPoint((x - y/len*3), (y + x/len*3))
         << QPoint((x + y/len*3), (y - x/len*3))
         << QPoint(x + h * (x/len), y + h * (y/len));

    painter.setPen(Qt::green);
    painter.drawPolygon(head);

    painter.resetTransform();
}
