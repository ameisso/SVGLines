//
//  DragablePoint.h
//  SVGLines
//
//  Created by Meissonnier A on 12/04/14.
//
//

#ifndef __SVGLines__DragablePoint__
#define __SVGLines__DragablePoint__

#include "cinder/app/AppNative.h"

#include <iostream>
#endif /* defined(__SVGLines__DragablePoint__) */
class DragablePoint
{
    
    public:
    DragablePoint();
    DragablePoint(int x,int y);
    DragablePoint(cinder::Vec2i pos);
    void draw();
    void update();
    
    int posX();
    int posY();
    cinder::Vec2i pos();
    void setPos(cinder::Vec2i pos);
    void setBBeingDragged(bool state);
    void setBOver(bool state);
    void setFill(bool state);
    void setCurved(bool state);
    void setRadius(int newRadius);
    int getRadius();
    bool getBOver();
    bool getBBeingDragged();
    
    virtual ~DragablePoint();
    
    
    private :
    int x;
    int y;
    bool bBeingDragged;
    bool bOver;
    int radius;
    bool curved;
    
    
};