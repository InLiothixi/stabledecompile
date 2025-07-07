#ifndef __IMAGESCROLLBAR_H__
#define __IMAGESCROLLBAR_H__

#include "Scrollbar.h"
#include "../../SexyAppFramework/Image.h"

class ImageScrollbar : public Scrollbar
{
public:
	Image*			mBackGroundImage;
	Image*			mThumbImage;
	Image*			mOverlayImage;
	bool			mDoStretchImage;

public:
	ImageScrollbar(LawnApp* theApp, ScrollMode theScrollMode);
	virtual ~ImageScrollbar();

	void				GetScaledPadding(float& thePadX, float& thePadY);
	virtual void		DrawBackground(Graphics* g);
	virtual void		DrawThumb(Graphics* g);
	void				DrawOverlay(Graphics* g);

};

#endif