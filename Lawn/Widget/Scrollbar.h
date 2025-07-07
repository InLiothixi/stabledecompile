#ifndef __SCROLLBAR_H__
#define __SCROLLBARWIDGET_H__

#include "../../LawnApp.h"
#include "../../SexyAppFramework/Widget.h"

enum ScrollMode {
	SCROLLMODE_VERTICAL,
	SCROLLMODE_HORIZONTAL,
};

class Scrollbar : public Widget {
public:
	LawnApp*			mApp;
	ScrollMode			mScrollMode;
	Color				mThumbColor;
	Color				mBackgroundColor;
	int					mOutAlpha;
	Rect				mViewRect;
	Rect				mThumbRect;
	float				mScrollAmount;
	float				mScrollValue;
	float				mScrollRange;
	bool				mButtonNoDraw;
	float				mThumbPadX;
	float				mThumbPadY;

public:
	Scrollbar(LawnApp* theApp, ScrollMode theScrollMode);
	virtual ~Scrollbar();

	virtual void		CalculateThumbSize();
	virtual void		SetScrollRange(float theScrollRange);
	virtual void		Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void		SetView(int theX, int theY, int theWidth, int theHeight);

	virtual void		UpdateThumbPosition();
	virtual void		Update();

	virtual void		ScrollbarDown(int theX, int theY);

	virtual void		MouseUp(int theX, int theY, int theClickCount);
	virtual void		MouseDown(int theX, int theY, int theClickCount);
	virtual void		MouseDrag(int theX, int theY);
	virtual void		MouseWheel(int theDelta);

	virtual void		DrawBackground(Graphics* g);
	virtual void		DrawThumb(Graphics* g);
	virtual void        Draw(Graphics* g);
};

#endif