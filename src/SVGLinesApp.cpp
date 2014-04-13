#include "SVGLinesApp.h"


using namespace ci;
using namespace ci::app;

#define WIDTH 512
#define HEIGHT 512
//--------------------------------------------------------------
void SVGLinesApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(WIDTH,HEIGHT);
	settings->setFrameRate(60.f);
    mousePos = Vec2i(200,200);
}
//--------------------------------------------------------------
void SVGLinesApp::setup(){
    saveFile=false;
    curveMode=false;
    endOfLine=false;
    isAppFullscrenn=false;
    aPointIsDragged=false;
    crossCursor=true;
    firstClickPerformed=false;
    doubleClickDuration=0.3;
    pointerRadius=3;
}

//--------------------------------------------------------------
void SVGLinesApp::draw(){
    gl::clear( Color( 0, 0, 0 ), true );//blackBG

    
    gl::color(ColorA(lineColor.r, lineColor.g, lineColor.b, 1.0f));
    if(polygonMode)
        gl::begin(GL_QUAD_STRIP);
    else
        gl::begin(GL_LINE_STRIP);

    for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
    {
        cinder::gl::vertex((*it)->posX(),(*it)->posY());
    }
    if(aPointIsDragged==false) {
        cinder::gl::vertex(mousePos.x, mousePos.y);
    }
    if(endOfLine)
    {
        endOfLine=false;
        //remove the last point created by the double click
        surface.remove(surface.back());
        list<DragablePoint*>::iterator firstIt = surface.begin();
        cinder::gl::vertex((*firstIt)->posX(),(*firstIt)->posY());
        surface.push_back(new DragablePoint((*firstIt)->pos()));
    }
    gl::end();

    //mouseCursor
    if(aPointIsDragged==false)
    {
        cinder::gl::color( 1.0f, 0, 0);
        if (crossCursor)
        {
            cinder::gl::drawSolidRect(cinder::Rectf(Vec2i(mousePos.x+pointerRadius/2,0),Vec2i(mousePos.x-pointerRadius/2,getWindowSize().y)));
            cinder::gl::drawSolidRect(cinder::Rectf(Vec2i(0,mousePos.y+pointerRadius/2),Vec2i(getWindowSize().x,mousePos.y-pointerRadius/2)));
        }
        else
        {
            cinder::gl::drawSolidCircle(mousePos,pointerRadius);
        }
    }
    
    //circles arround points
    gl::color(ColorA(lineColor.r, lineColor.g, lineColor.b, 1.f));
    for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
    {
        
        if ((*it)->getBOver())
            cinder::gl::drawStrokedCircle((*it)->pos(),(*it)->getRadius());
        else
            cinder::gl::drawSolidCircle((*it)->pos(),(*it)->getRadius());
    }

}

//--------------------------------------------------------------
void SVGLinesApp::keyDown( KeyEvent event )
{
    //std::cout<<"key pressed : "<<event.getChar()<<" "<<event.getCode()<<std::endl;
    char key=event.getChar();
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );

    if(key=='c')
    {
        surface.clear();
    }
    if(key=='r')
    {
        renderSVG();
    }
}

//--------------------------------------------------------------
void SVGLinesApp::keyUp(KeyEvent event )
{
    std::cout<<"key released : "<<event.getChar()<<" "<<event.getCode()<<std::endl;
    char key=event.getChar();
    if(key=='f'||key=='F')
    {
        isAppFullscrenn=!isAppFullscrenn;
        if(isAppFullscrenn)
        fullScreenSize=getWindowSize();
        return;
    }
}

//------------- -------------------------------------------------
void SVGLinesApp::mouseMove( MouseEvent event ) {
    //store mouse position :
    mousePos=event.getPos();
    for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
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

//--------------------------------------------------------------
void SVGLinesApp::mouseDrag( MouseEvent event ) {
    
    for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
    {
		if ((*it)->getBBeingDragged() == true){
            (*it)->setPos(event.getPos());
            if ((*it)==surface.front()) {
                surface.back()->setPos(event.getPos());
            }
            aPointIsDragged=true;
            break;
		}
        else
        {
            aPointIsDragged=false;
        }
	}
}

//--------------------------------------------------------------
void SVGLinesApp::mouseDown( MouseEvent event ) {
    if( ((app::getElapsedSeconds() - firstClickTime) <= doubleClickDuration) && (firstClickPerformed ==false) )
    {
        //std::cout<<"doubleClick"<<app::getElapsedSeconds()-firstClickTime<<std::endl;
        endOfLine=true;
        firstClickPerformed=true;
    }
    else
    {
        firstClickPerformed = false;
        bool newPoint=true;
        for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
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
        if(newPoint)
        {
            surface.push_back(new DragablePoint(mousePos));
        }
    }
    firstClickTime = app::getElapsedSeconds();
    }
void SVGLinesApp::mouseUp( MouseEvent event)
{
    aPointIsDragged=false;
    mousePos=event.getPos();
}
void SVGLinesApp::renderSVG()
{
    timeCode-=clock();
    std::stringstream ss;
    ss << "/Users/antoine/Desktop/svgLines"<<(int)timeCode<<".svg";
    std::string myPath = ss.str();
    timeCode=clock();
    // Get an ofstream which is what you'll use to write to your file.
    std::ofstream oStream( myPath );
    
    // write the string.

    oStream << "<!-- Created with SVGLines (ameisso.fr) -->\n";
    oStream << "<svg width=\""<<fullScreenSize.x<<"\" height=\""<<fullScreenSize.y<<"\">\n";
    oStream<<"<path d=\"M"<<surface.front()->posX()<<" "<<surface.front()->posY()<<" ";
    for( list<DragablePoint*>::iterator it = surface.begin(); it != surface.end(); ++it )
    {
        oStream<<"L"<<(*it)->posX()<<" "<<(*it)->posY()<<" ";
    }
    oStream<<"Z\" />";
    oStream << "</svg>";
    oStream.close();

}