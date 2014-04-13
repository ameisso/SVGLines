#include "testSVGCocoaApp.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

#define WIDTH 512
#define HEIGHT 512
//--------------------------------------------------------------
void testSVGCocoaApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(WIDTH,HEIGHT);
	settings->setFrameRate(60.f);
}
//--------------------------------------------------------------
void testSVGCocoaApp::setup(){

    
    
    
    //TEST
    
  
    saveFile=false;
    curveMode=false;
    endOfLine=false;
}

//--------------------------------------------------------------
void testSVGCocoaApp::draw(){
//    if(capture){
//        output.beginEPS("test.eps");
//    }
    gl::color(ColorA(1.f, 0.f, 0.f, 0.f));//red
    cinder::gl::drawStrokedCircle(mousePos,5);
    gl::color(ColorA(1.f, 1.f, 1.f, 1.f));//red

	
    if(curveVertices.size()>1);
    {
        Vec2f previousPos;
        previousPos.x=mousePos.x;
        previousPos.y=mousePos.y;
        gl::begin(GL_LINE_STRIP);
        for( list<draggableVertex>::iterator it = curveVertices.begin(); it != curveVertices.end(); ++it )
        {
                cinder::gl::vertex(it->x,it->y);
            
            if (it->bOver == true)
            {
                endOfLine=true;
            }
            else
            {
                endOfLine=false;
            }
            
            cinder::gl::drawStrokedCircle(mousePos, 5);
            previousPos.x=it->x;
            previousPos.y=it->y;
        }

            cinder::gl::vertex(mousePos.x, mousePos.y);
            //output.line(previousPos.x,previousPos.y,mouseX,mouseY);
    }
    if(capture){
        //output.endEPS();
        capture =false;
    }
    gl::end();
}

//--------------------------------------------------------------
void testSVGCocoaApp::keyPressed(KeyEvent event ){

    //if( event.getChar() == 'w' ) {
        std::cout<<"key pressed : "<<event.getChar()<<std::endl;
    char key=event.getChar();
    if(key==78||key==110)//N
    {
        std::cout<<"new curve"<<std::endl;
        curveVertices.push_back(curveVertices.front());
    }
    if(key==83||key==115)//S
    {
        std::cout<<"write file"<<std::endl;
        capture = true;
    }
    if(key=='c')
    {
        curveVertices.clear();
    }
    if (event.getCode()==1280)
    {
        curveMode=true;
    }
}

//--------------------------------------------------------------
void testSVGCocoaApp::keyReleased(KeyEvent event ){
    if (event.getCode()==1280)
    {
        curveMode=false;
    }
}

//------------- -------------------------------------------------
void testSVGCocoaApp::mouseMove( MouseEvent event ) {
    //store mouse position :
    mousePos=event.getPos();
    for( list<draggableVertex>::iterator it = curveVertices.begin(); it != curveVertices.end(); ++it )
    {
		float diffx = mousePos.x - it->x;
		float diffy = mousePos.y - it->y;
		float dist = sqrt(diffx*diffx + diffy*diffy);
		if (dist < it->radius){
			it->bOver = true;
		} else {
			it->bOver = false;
		}
	}
}

//--------------------------------------------------------------
void testSVGCocoaApp::mouseDrag( MouseEvent event ) {
    
    for( list<draggableVertex>::iterator it = curveVertices.begin(); it != curveVertices.end(); ++it )
    {
		if (it->bBeingDragged == true){
			it->x = event.getPos().x;
			it->y = event.getPos().y;
		}
	}
}

//--------------------------------------------------------------
void testSVGCocoaApp::mouseDown( MouseEvent event ) {
    bool newPoint=true;
    mousePos=event.getPos();
    for( list<draggableVertex>::iterator it = curveVertices.begin(); it != curveVertices.end(); ++it )
    {
		float diffx = mousePos.x - it->x;
		float diffy = mousePos.y - it->y;
		float dist = sqrt(diffx*diffx + diffy*diffy);
		if (dist < it->radius){
			it->bBeingDragged = true;
            newPoint=false;
		} else {
			it->bBeingDragged = false;
		}
	}
    if(newPoint)
    {
        draggableVertex newVertex;
        newVertex.x=mousePos.x;
        newVertex.y=mousePos.y;
        newVertex.bOver=false;
        newVertex.bBeingDragged=false;
        newVertex.radius=4;
        if(curveMode)newVertex.curved=true;
        else newVertex.curved=false;
        curveVertices.push_back(draggableVertex (newVertex));

    }
}