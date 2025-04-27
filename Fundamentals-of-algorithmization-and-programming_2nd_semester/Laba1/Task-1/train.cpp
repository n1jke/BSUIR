
#include "train.h"
#include <QPainter>
#include "smoke.h"
Train::Train() : Rectangle(){ // list initisalization
      };

void Train::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* ){ // dont use last two parametrs
    painter->setBrush(Qt::darkGreen);
    int width = 400;
    int height = 200;
    int y = -100;
    painter->drawRect(currX, y, width, height);
    painter->setBrush(Qt::cyan);
    painter->drawRect(currX + 50, y + 30, 80, 130);       // left window
    painter->drawRect(currX + 250, y + 30, 80, 130);      // right window

    painter->setBrush(Qt::black);
    painter->drawEllipse(currX + 20, y + 180, 50, 50);    // 1 wheel
    painter->drawEllipse(currX + 100, y + 180, 50, 50);   // 2 wheel
    painter->drawEllipse(currX + 240, y + 180, 50, 50);   // 3 wheel
    painter->drawEllipse(currX + 320, y + 180, 50, 50);   // 4 wheel

    drawTube(painter);
}

void Train::drawTube(QPainter* painter){
    painter->setBrush(Qt::darkGray);
    int tubeWidth = 20;
    int tubeHeight = 60;
    int tubeX = currX + 380;
    int tubeY = -160;
    tubePosition = QRectF(tubeX, tubeY, tubeWidth, tubeHeight);
    painter->drawRect(tubePosition);
}

void Train::emitSmoke(){
    Smoke* smoke = new Smoke();
    int smokeX = tubePosition.x() + tubePosition.width() / 2 - smoke->boundingRect().width() / 2;
    int smokeY = tubePosition.y() - smoke->boundingRect().height();
    smoke->setPos(smokeX, smokeY);
    scene()->addItem(smoke);
}
