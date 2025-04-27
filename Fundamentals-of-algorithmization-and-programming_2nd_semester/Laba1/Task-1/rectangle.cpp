#include "rectangle.h"


Rectangle::Rectangle() : QGraphicsRectItem(){
    coordinates = pos();
}


void Rectangle::moveSlider(int newPos){
    currX = newPos;
    coordinates.setX(currX);
    setPos(coordinates);
}