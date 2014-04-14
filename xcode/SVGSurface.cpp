//
//  Surface.cpp
//  SVGLines
//
//  Created by Meissonnier A on 13/04/14.
//
//

#include "SVGSurface.h"
SVGSurface::SVGSurface()
{

}
SVGSurface::~SVGSurface()
{
    
}
void SVGSurface::draw()
{
    for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
    {
    cinder::gl::vertex((*it)->posX(),(*it)->posY());
    }
}
void SVGSurface::endOfSurface()
{
    //remove the last point created by the double click
    surfacePoints.remove(surfacePoints.back());
    list<DragablePoint*>::iterator firstIt = surfacePoints.begin();
    cinder::gl::vertex((*firstIt)->posX(),(*firstIt)->posY());
    surfacePoints.push_back(new DragablePoint((*firstIt)->pos()));
}
std::tuple <bool,Vec2i,int> SVGSurface::getBOver()
{

    bool isBover=false;
    Vec2i position;
    int radius;
    if (surfacePoints.size()>0)
    {
        for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
        {
            if ((*it)->getBOver()) {
                isBover=true;
                position=(*it)->pos();
                radius=(*it)->getRadius();
                break;
            }
        }
    }
    else
    {
        isBover=false;
        radius=4;
        position=Vec2i(0,0);
    }
    return  std::make_tuple(isBover,position, radius);
}
void SVGSurface::mouseMove(Vec2i mousePos)
{
    for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
    {
        float diffx = mousePos.x - (*it)->posX();
        float diffy = mousePos.y - (*it)->posY();
        float dist = sqrt(diffx*diffx + diffy*diffy);
        if (dist < (*it)->getRadius()){
            (*it)->setBOver(true);
            (*it)->setRadius(6);
        } else {
            (*it)->setBOver (false);
            (*it)->setRadius(4);
        }
    }
}
bool SVGSurface::mouseDrag(Vec2i mousePos)
{
    bool aPointIsDragged;
    for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
    {
		if ((*it)->getBBeingDragged() == true){
            (*it)->setPos(mousePos);
            if ((*it)==surfacePoints.front()) {
                surfacePoints.back()->setPos(mousePos);
            }
            aPointIsDragged=true;
            break;
		}
        else
        {
           aPointIsDragged=false;
        }
	}
    return aPointIsDragged;

}
bool SVGSurface::checkDragged(Vec2i mousePos)
{
    bool newPoint=true;
    for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
    {
        float diffx = mousePos.x - (*it)->posX();
        float diffy = mousePos.y - (*it)->posY();
        float dist = sqrt(diffx*diffx + diffy*diffy);
        if (dist < (*it)->getRadius()){
            (*it)->setBBeingDragged(true);
            newPoint=false;
        } else {
            (*it)->setBBeingDragged(false);
        }
    }
    return newPoint;
}
void SVGSurface::clearPoints()
{
    surfacePoints.clear();
}
void SVGSurface::addPoint(Vec2i mousePos)
{
    surfacePoints.push_back(new DragablePoint(mousePos));
}
std::string SVGSurface::renderSvg()
{
    std::stringstream ss;
    ss << "<path d=\"M"<<surfacePoints.front()->posX()<<" "<<surfacePoints.front()->posY()<<" ";

    for( list<DragablePoint*>::iterator it = surfacePoints.begin(); it != surfacePoints.end(); ++it )
    {
        ss<<"L"<<(*it)->posX()<<" "<<(*it)->posY()<<" ";
    }
    ss<<"Z\" />";

    
    return ss.str();
}