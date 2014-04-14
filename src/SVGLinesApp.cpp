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
    endOfLine=false;
    isAppFullscrenn=false;
    aPointIsDragged=false;
    crossCursor=true;
    firstClickPerformed=true;
    doubleClickDuration=0.3;
    pointerRadius=3;
    surfaces.push_back(new SVGSurface());
}

//--------------------------------------------------------------
void SVGLinesApp::draw(){
    gl::clear( Color( 0, 0, 0 ), true );//blackBG

    
    gl::color(ColorA(lineColor.r, lineColor.g, lineColor.b, 1.0f));
    if(polygonMode)
        gl::begin(GL_QUAD_STRIP);
    else
        gl::begin(GL_LINE_STRIP);

    for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
    {
        (*it)->draw();
    }
    if(aPointIsDragged==false) {
        cinder::gl::vertex(mousePos.x, mousePos.y);
    }
    if(endOfLine)
    {
        endOfLine=false;
        surfaces.back()->endOfSurface();
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
    for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
    {
        auto bOverTuple=(*it)->getBOver();
        Vec2i position=std::get<1>(bOverTuple);
        int radius=std::get<2>(bOverTuple);
        if (std::get<0>(bOverTuple))
            cinder::gl::drawStrokedCircle(position,radius);
        else
            cinder::gl::drawSolidCircle(position,radius);
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
        for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
        {
            (*it)->clearPoints();
        }
        
        surfaces.clear();
        surfaces.push_back(new SVGSurface());
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
    for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
    {
        (*it)->mouseMove(mousePos);
	
	}
}

//--------------------------------------------------------------
void SVGLinesApp::mouseDrag( MouseEvent event ) {
    for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
    {
		(*it)->mouseDrag(mousePos);
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
        for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
        {
           newPoint=(*it)->checkDragged(mousePos);
        }
        if(newPoint)
        {
            surfaces.back()->addPoint(mousePos);
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
    for( list<SVGSurface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it )
    {
        oStream<<(*it)->renderSvg();
    }
    
    oStream << "</svg>";
    oStream.close();

}