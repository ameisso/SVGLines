#pragma once

#include "cinder/app/AppCocoaView.h"

class SVGLinesApp : public cinder::app::AppCocoaView {
  public:
	void				setup();
	void				draw();

	float				mRadius;
	cinder::Colorf		mColor;
};
