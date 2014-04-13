
#include "cinder/app/CinderView.h"
#include "SVGLinesApp.h"
#import <Cocoa/Cocoa.h>

@interface SVGLinesDelegate : NSObject <NSApplicationDelegate>
{
	IBOutlet CinderView		*cinderView;
	IBOutlet NSWindow		*window;
	IBOutlet NSColorWell	*colorWell;
	
	SVGLinesApp		*mApp;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)subdivisionSliderChanged:(id)sender;
- (IBAction)colorChanged:(id)sender;
- (IBAction)crossCursorCheckBox:(id)sender;

@end
