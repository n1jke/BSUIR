#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>

class Rectangle : public QGraphicsRectItem, public QObject{
public:
    Rectangle();
    int currX = -400;
    QPointF coordinates;

public slots:
    void moveSlider(int newPos);
};

#endif // RECTANGLE_H