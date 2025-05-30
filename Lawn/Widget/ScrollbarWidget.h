#ifndef __SCROLLBARWIDGET_H__
#define __SCROLLBARWIDGET_H__

#include "../../LawnApp.h"
#include "../../SexyAppFramework/Widget.h"

enum ScrollbarMode{
	HORIZONTAL,
	VERTICAL,
	HORIZONTAL_WITH_PAGE_UP_AND_DOWN_BUTTONS,
	VERTICAL_WITH_PAGE_UP_AND_DOWN_BUTTONS
};

class ScrollbarWidget : public Widget {
public:
	LawnApp* mApp;
	ScrollbarMode mScrollbarMode;
	Color mThumbColor;
	Color mThumbInnerHighlight;
	Color mThumbInnerHighlight2;
	Color mThumbInnerHighlightShadow; 
	Color mThumbInnerShadow;
	Color mThumbInnerShadow2; 
	Color mThumbOuterShadow;
	Color mThumbOuterShadow2;
	Color mBackgroundColor;
	Rect mViewport;
	float mThumbX;
	float mThumbY;
	float mThumbWidth;
	float mThumbHeight;
	float mScrollValue;
	float mScrollRange;
	bool mButtonNoDraw;

public:
	ScrollbarWidget(LawnApp* theApp, ScrollbarMode theScrollbarMode);
	virtual ~ScrollbarWidget();

	bool isThumbOver();
	bool isThumbDown();
	void DrawScrollBackground(Graphics* g);
	void DrawThumb(Graphics* g);
	virtual void Update();
	virtual void Draw(Graphics* g);
};

#endif