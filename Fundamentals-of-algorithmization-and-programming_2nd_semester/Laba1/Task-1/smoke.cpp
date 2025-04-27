#include "smoke.h"
#include <QPainter>
Smoke::Smoke()
{
}

QRectF Smoke::boundingRect() const{
    return QRectF(-5, 20, 15, 15);
}

void Smoke::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){ // dont use last two parametrs
    painter->setBrush(Qt::lightGray);
    painter->drawEllipse(boundingRect());
}