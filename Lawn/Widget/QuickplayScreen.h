#ifndef __QUICKPLAYSCREEN_H__
#define __QUICKPLAYSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "GameButton.h"

class LawnApp;

using namespace Sexy;

class QuickplayWidget : public Widget, public ButtonListener 
{
private:
    enum
    {
		Quickplay_Back,
        Quickplay_DayStage,
		Quickplay_NightStage,
		Quickplay_PoolStage,
		Quickplay_FogStage,
		Quickplay_RoofStage,
		Quickplay_RIP
    };
public:
	LawnApp*					mApp;  
	int							thePreviousId;
	int							theCurrentId;
    NewLawnButton*				mBackButton;
	NewLawnButton*				mDayStageButton;
	NewLawnButton*				mNightStageButton;
	NewLawnButton*				mPoolStageButton;
	NewLawnButton*				mFogStageButton;
	NewLawnButton*				mRoofStageButton;
	NewLawnButton*				mRIPButton;
	ButtonWidget*				mLevelButtons[50];
	bool						mIsScrollable;
	float						mScrollAmount;
	float						mScrollPosition;
	float						mMaxScrollPosition;
	int							mTrackWidth;
	bool						mScrollableDown;
	bool						mIsDraggingThumb;
	bool						mMouseIsDragging;
	bool						mIsSwiping;
	int							mSwipeStartX;
	float						mSwipeVelocityX;
	bool						mSwipeJustReleased;
	int							mSwitchStagesCounter;
	bool						mDoSwitchStage;
	bool						mHasFinishedSliding;
	bool						mIsSlidingOut;
	int							mSlidingOutCounter;
	float						mPreviousScrollPosition;

public:
	QuickplayWidget(LawnApp* theApp);
	virtual ~QuickplayWidget();
	virtual void                Update();
	virtual void                Draw(Graphics* g);
	virtual void                AddedToManager(WidgetManager* theWidgetManager);
	virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void                OrderInManagerChanged();
	virtual void                ButtonMouseEnter(int theId);
	virtual void                ButtonDepress(int theId);
	virtual void                ButtonPress(int theId, int theClickCount);
	void						SelectStage(int theId, bool doTransition);
	void						DrawButton(Graphics* g, int theLevelIndex);
	virtual void				MouseWheel(int theDelta);
	virtual void				MouseUp(int theX, int theY);
	virtual void				MouseMove(int theX, int theY);
	void						DisableButtons(bool isDisabled);
};
#endif