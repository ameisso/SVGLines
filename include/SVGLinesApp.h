#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/app/AppCocoaView.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/App/App.h"
#include "DragablePoint.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

#include <list>
#include "cinder/gl/gl.h"
using std::list;

using namespace ci;
using namespace ci::app;

class SVGLinesApp : public cinder::app::AppCocoaView {
public:
	void				setup();
	void				draw();
    void                prepareSettings( Settings *settings );
    void                keyDown(ci::app::KeyEvent event );
    void                keyUp(ci::app::KeyEvent event );
    void                mouseMove(MouseEvent event) ;
    void                mouseDrag(ci::app:: MouseEvent event );
    void                mouseDown(ci::app:: MouseEvent event );
    void                mouseUp( MouseEvent event);
    void                renderSVG();
    

    cinder::Colorf		lineColor;
    bool                polygonMode;
    bool                crossCursor;
    int                 pointerRadius;
    std::string         pathToExport;
private:
    bool isAppFullscrenn;
    bool saveFile;
    bool curveMode;
    bool endOfLine;
    bool capture;
    ci::Vec2i mousePos;//MousePosition
    
    ci::Vec2i fullScreenSize;
    bool aPointIsDragged;


    //Vertices
    list<DragablePoint*> surface;
    
    //DoubleClick
    float firstClickTime;
    float doubleClickDuration;
    bool firstClickPerformed;
    
    //SVGrenderer
    double timeCode;

   
    
    
    
};

