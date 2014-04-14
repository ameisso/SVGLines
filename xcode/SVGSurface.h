//
//  Surface.h
//  SVGLines
//
//  Created by Meissonnier A on 13/04/14.
//
//

#ifndef __SVGLines__Surface__
#define __SVGLines__Surface__

#include <tuple>
#include <sstream>
#include <string>
#include "DragablePoint.h"

#include "cinder/app/AppNative.h"
using std::list;
using namespace ci;
using namespace ci::app;
#endif /* defined(__SVGLines__Surface__) */
class SVGSurface
{
public:
    SVGSurface();
    ~SVGSurface();
    void clearPoints();
    void draw();
    void endOfSurface();
    std::tuple<bool,Vec2i,int> getBOver();
    void mouseMove(Vec2i mousePos);
    bool mouseDrag(Vec2i mousePos);
    bool checkDragged(Vec2i mousePos);
    void addPoint(Vec2i mousePos);
    std::string renderSvg();
private:
    //Vertices
    list<DragablePoint*> surfacePoints;
 
    
};