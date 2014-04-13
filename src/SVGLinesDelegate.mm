#include "cinder/Cinder.h"
#include "cinder/Rand.h"
#import "SVGLinesDelegate.h"

@implementation SVGLinesDelegate

@synthesize window;

- (void)dealloc
{
    [super dealloc];
}
	
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	mApp = new SVGLinesApp;
	mApp->prepareLaunch();
	mApp->setupCinderView( cinderView, cinder::app::RendererGl::create() );
	mApp->launch();
    mApp->lineColor=ci::Colorf(1,1,1);
    mApp->polygonMode=false;
    [[self window] setAcceptsMouseMovedEvents:YES];
    
    //default path
    
    NSArray * paths = NSSearchPathForDirectoriesInDomains (NSDesktopDirectory, NSUserDomainMask, YES);
    //NSLog(@"path %@",[[paths objectAtIndex:0]stringValue]);
    std::string vam=[[paths objectAtIndex:0]UTF8String];
    mApp->pathToExport =[[paths objectAtIndex:0]UTF8String];
}

- (IBAction)subdivisionSliderChanged:(id)sender
{
    mApp->pointerRadius=[sender integerValue];
   // NSLog(@"newVal %i",[sender integerValue]);
}

- (IBAction)colorChanged:(id)sender
{
    NSColor *color = [sender color];
	mApp->lineColor = ci::Colorf( [color redComponent], [color greenComponent], [color blueComponent] );
}

- (IBAction)crossCursorCheckBox:(id)sender {
    mApp->crossCursor=[sender integerValue];
}
- (IBAction)polygonMode:(id)sender
{
    mApp->polygonMode=[sender integerValue];
}
- (BOOL)acceptsFirstResponder
{
    return YES;
}


@end
