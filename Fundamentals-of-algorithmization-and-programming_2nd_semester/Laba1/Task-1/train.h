#ifndef TRAIN_H
#define TRAIN_H

#include "rectangle.h"
#include<QPainter>
#include<QGraphicsItem>
class Train : public Rectangle{
public:
    Train();
    void drawTube(QPainter* painter);
    void emitSmoke();
    QRectF tubePosition;

protected:
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // TRAIN_H