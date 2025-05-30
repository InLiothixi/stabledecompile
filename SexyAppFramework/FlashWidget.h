#ifndef __FLASHWIDGET_H__
#define __FLASHWIDGET_H__

#include "Common.h"
#include "Widget.h"

struct IOleObject;
struct IOleInPlaceObjectWindowless;

namespace ShockwaveFlashObjects
{
	struct IShockwaveFlash;
}

namespace Sexy
{

class Image;
class FlashSink;
class MemoryImage;
class DDImage;
class ControlSite;

class FlashListener
{
public:
	virtual void			FlashAnimEnded(int theId) {}
	virtual void			FlashCommand(int theId, const SexyString& theCommand, const SexyString& theParam) {}
};

class FlashWidget : public Widget
{
public:
	enum
	{
		STATE_IDLE,
		STATE_PLAYING,
		STATE_STOPPED
	};

	enum
	{
		QUALITY_LOW,
		QUALITY_MEDIUM,
		QUALITY_HIGH
	};

public:
	int						mState;
	int						mId;
	FlashListener*			mFlashListener;
	HMODULE					mFlashLibHandle;		

	ControlSite*			mControlSite;
	FlashSink*				mFlashSink;
	ShockwaveFlashObjects::IShockwaveFlash* mFlashInterface;
	IOleObject*				mOleObject;
	IOleInPlaceObjectWindowless* mWindowlessObject;

	int						mCOMCount;
	DDImage*				mImage;	
	int						mPauseCount;
	bool					mHasLostFocus;

	Rect					mDirtyRect;
	bool					mFlashDirty;
	
	int						mCurCursor;
	HCURSOR					mCurOverrideCursor;
	
	bool					mAutoPause;
	Image*					mBkgImage;
	Rect					mBkgImageSrcRect;
	Color					mBkgColor;				

public:
	void					CleanupImages();
	void					RebuildImages();
	void					CheckCursor();

protected:
	virtual void			DrawFlashBackground(Graphics* g);

public:
	FlashWidget(int theId, FlashListener* theFlashListener);
	~FlashWidget();
	
	static double			GetFlashVersion();

	bool					StartAnimation(const SexyString& theFileName);
	void					SetQuality(int theQuality);
	void					Pause();
	void					Unpause();
	bool					IsPlaying();	
	void					Rewind();
	void					Back();
	void					Forward();	
	void					GotoFrame(int theFrameNum);
	int						GetCurrentFrame();
	SexyString				GetCurrentLabel(const SexyString& theTimeline);
	void					CallFrame(const SexyString& theTimeline, int theFrameNum);
	void					CallLabel(const SexyString& theTimeline, const SexyString& theLabel);
	SexyString				GetVariable(const SexyString& theName);
	void					SetVariable(const SexyString& theName, const SexyString& theValue);
		
	virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
	
	virtual void			Update();
	virtual void			Draw(Graphics* g);

	virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);		
	virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseMove(int x, int y);
	virtual void			MouseDrag(int x, int y);
	
	virtual void			MouseLeave();

	virtual void			SysColorChanged();
};

}

#endif //__FLASHWIDGET_H__
