//
//  DragablePoint.cpp
//  SVGLines
//
//  Created by Meissonnier A on 12/04/14.
//
//

#include "DragablePoint.h"
DragablePoint::DragablePoint()
{
    //ctor
}

DragablePoint::~DragablePoint()
{

}
DragablePoint::DragablePoint(int posX, int posY)
{
    x=posX;
    y=posY;
    bOver=false;
    bBeingDragged=false;
    radius=4;
}
DragablePoint::DragablePoint(cinder::Vec2i pos)
{
    x=pos.x;
    y=pos.y;
    bOver=false;
    bBeingDragged=false;
    radius=4;
}
int DragablePoint::posX()
{
    return x;
}
int DragablePoint::posY()
{
    return y;
}
cinder::Vec2i DragablePoint::pos()
{
    return cinder::Vec2i(x,y);
}
int DragablePoint::getRadius()
{
    return radius;
}
void DragablePoint::setPos(cinder::Vec2i pos)
{
    x=pos.x;
    y=pos.y;
}
void DragablePoint::draw()
{
    
}
void DragablePoint::update()
{
    
}
void DragablePoint::setBBeingDragged(bool state)
{
    bBeingDragged=state;
}
void DragablePoint::setBOver(bool state)
{
    bOver=state;
}
void DragablePoint::setRadius(int newRadius)
{
    radius=newRadius;
}
bool DragablePoint::getBBeingDragged()
{
    return bBeingDragged;
}
bool DragablePoint::getBOver()
{
    return bOver;
}
