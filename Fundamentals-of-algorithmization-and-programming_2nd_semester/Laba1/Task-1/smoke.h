#ifndef SMOKE_H
#define SMOKE_H

#include <QGraphicsItem>

class Smoke : public QGraphicsItem{
public:
    Smoke();
    QRectF boundingRect() const override; // smoke size
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // SMOKE_H