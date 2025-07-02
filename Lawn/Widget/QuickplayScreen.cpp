#include "QuickplayScreen.h"
#include "../../Resources.h"
#include "../../LawnApp.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "GameSelector.h"
#include "GameButton.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../GameConstants.h"
#include "../../Sexy.TodLib/Reanimator.h"
#include "../System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodStringFile.h"

const Rect aScrollArea = {10, 221, BOARD_WIDTH - 20, 5};

int slideDownCounter = 0;

// GOTY @Inliothixi
QuickplayWidget::QuickplayWidget(LawnApp* theApp) {
	TodLoadResources("DelayLoad_LevelSelector");
	mApp = theApp;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;

	mIsScrollable = false;
	mScrollAmount = 0;
	mScrollPosition = 0;
	mScrollableDown = false;
	mIsDraggingThumb = false;
	mMouseIsDragging = false;
	mIsSwiping = false;
	mSwipeStartX = -1;
	mSwipeVelocityX = 0.0f;
	mMaxScrollPosition = 1068;
	mTrackWidth = 780;
	mSwitchStagesCounter = -1;
	mHasFinishedSliding = false;
	mIsSlidingOut = false;
	mSlidingOutCounter = -1;
	mSwipeJustReleased = false;

	mPoolStageButton = MakeNewButton(
		QuickplayWidget::Quickplay_PoolStage,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_LEVELSELECTOR_POOL_BUTTON,
		Sexy::IMAGE_LEVELSELECTOR_POOL_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_LEVELSELECTOR_POOL_BUTTON_PRESSED
	);
	mPoolStageButton->mClip = false;
	mPoolStageButton->Resize(251.6f, 340.5f, Sexy::IMAGE_LEVELSELECTOR_POOL_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_LEVELSELECTOR_POOL_BUTTON_HIGHLIGHT->mHeight);
	mPoolStageButton->mTranslateX = 0;
	mPoolStageButton->mTranslateY = 0;

	mNightStageButton = MakeNewButton(
		QuickplayWidget::Quickplay_NightStage,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_LEVELSELECTOR_NIGHT_BUTTON,
		Sexy::IMAGE_LEVELSELECTOR_NIGHT_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_LEVELSELECTOR_NIGHT_BUTTON_PRESSED
	);
	mNightStageButton->mClip = false;
	mNightStageButton->Resize(104, 370.95f, Sexy::IMAGE_LEVELSELECTOR_NIGHT_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_LEVELSELECTOR_NIGHT_BUTTON_HIGHLIGHT->mHeight);
	mNightStageButton->mTranslateX = 0;
	mNightStageButton->mTranslateY = 0;

	mFogStageButton = MakeNewButton(
		QuickplayWidget::Quickplay_FogStage,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_LEVELSELECTOR_FOG_BUTTON,
		Sexy::IMAGE_LEVELSELECTOR_FOG_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_LEVELSELECTOR_FOG_BUTTON_PRESSED
	);
	mFogStageButton->mClip = false;
	mFogStageButton->Resize(368.7f, 328.25f, Sexy::IMAGE_LEVELSELECTOR_FOG_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_LEVELSELECTOR_FOG_BUTTON_HIGHLIGHT->mHeight);
	mFogStageButton->mTranslateX = 0;
	mFogStageButton->mTranslateY = 0;

	mRoofStageButton = MakeNewButton(
		QuickplayWidget::Quickplay_RoofStage,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_LEVELSELECTOR_ROOF_BUTTON,
		Sexy::IMAGE_LEVELSELECTOR_ROOF_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_LEVELSELECTOR_ROOF_BUTTON_PRESSED
	);
	mRoofStageButton->mClip = false;
	mRoofStageButton->Resize(474, 389.15f, Sexy::IMAGE_LEVELSELECTOR_ROOF_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_LEVELSELECTOR_ROOF_BUTTON_HIGHLIGHT->mHeight);
	mRoofStageButton->mTranslateX = 0;
	mRoofStageButton->mTranslateY = 0;

	mDayStageButton = MakeNewButton(
		QuickplayWidget::Quickplay_DayStage,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_LEVELSELECTOR_DAY_BUTTON,
		Sexy::IMAGE_LEVELSELECTOR_DAY_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_LEVELSELECTOR_DAY_BUTTON_PRESSED
	);
	mDayStageButton->mClip = false;
	mDayStageButton->Resize(8.55f, 432.05f, Sexy::IMAGE_LEVELSELECTOR_DAY_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_LEVELSELECTOR_DAY_BUTTON_HIGHLIGHT->mHeight);
	mDayStageButton->mTranslateX = 0;
	mDayStageButton->mTranslateY = 0;

	thePreviousId = -1;
	theCurrentId = 1;

	for (int i = 0; i < FINAL_LEVEL; i++) {
		int aLevel = i + 1;
		int aStage = (int) (i / 10.0f);
		int aSubLevel = aLevel % 10;
		ButtonWidget* aLevelButton = new ButtonWidget(QuickplayWidget::Quickplay_RoofStage + aLevel, this);
		mLevelButtons[i] = aLevelButton;
		aLevelButton->mDoFinger = true;
		aLevelButton->mFrameNoDraw = true;
		aLevelButton->Resize(10 + 186 * aSubLevel, -IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mHeight, IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mWidth, IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mHeight);
		aLevelButton->mVisible = false;
	}

	mBackButton = MakeNewButton(
		QuickplayWidget::Quickplay_Back,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_BLANK,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED
	);
	mBackButton->mClip = false;
	mBackButton->Resize(278, 528.5f, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mHeight);
	mBackButton->mTranslateX = 0;
	mBackButton->mTranslateY = 0;
}

QuickplayWidget::~QuickplayWidget() {
	if (mPoolStageButton)
		delete mPoolStageButton;
	if (mNightStageButton)
		delete mNightStageButton;
	if (mFogStageButton)
		delete mFogStageButton;
	if (mRoofStageButton)
		delete mRoofStageButton;
	if (mDayStageButton)
		delete mDayStageButton;
	for (ButtonWidget* aLevelButton : mLevelButtons) delete aLevelButton;
	if (mBackButton)
		delete mBackButton;
}

void QuickplayWidget::Update() {
	mPoolStageButton->MarkDirty();
	mNightStageButton->MarkDirty();
	mFogStageButton->MarkDirty();
	mRoofStageButton->MarkDirty();
	mDayStageButton->MarkDirty();
	for (ButtonWidget* aButton : mLevelButtons) aButton->MarkDirty();
	mBackButton->MarkDirty();

	if (mIsSlidingOut)
	{
		if (mSlidingOutCounter > 0)
		{
			mSlidingOutCounter--;
			{
				int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(theCurrentId, QuickplayWidget::Quickplay_RoofStage)) - 1;
				for (int aLevel = 0; aLevel < 10; aLevel++) {
					ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
					aLevelButton->MarkAllDirty();
					aLevelButton->mY = TodAnimateCurveFloatTime(50, 0, mSlidingOutCounter, 35, -IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mHeight, TodCurves::CURVE_LINEAR);
					aLevelButton->MarkDirty();
					mWidgetManager->RehupMouse();
				}
			}
		}
		else if (mSlidingOutCounter == 0)
		{
			mSlidingOutCounter = -1;
			mApp->mGameSelector->SlideTo(mApp->mWidth, 0);
			mApp->mGameSelector->mWidgetManager->SetFocus(mApp->mGameSelector->mMoreWidget);
		}
	}

	if (mWidgetManager->mFocusWidget == this)
	{
		if (mIsScrollable)
		{
			const bool IS_DOWN = mWidgetManager->mFocusWidget->mIsDown;

			if (!mScrollableDown && IS_DOWN) {
				if (aScrollArea.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY))
				{
					mScrollableDown = true;
					mIsDraggingThumb = true;
					float aThumbWidth = mApp->mWidth / mMaxScrollPosition * mTrackWidth;
					float aScrollPosition = (mWidgetManager->mLastMouseX - (aThumbWidth / 2.0f)) / (mTrackWidth - aThumbWidth) * mMaxScrollPosition;
					mScrollPosition = max(0, min(aScrollPosition, mMaxScrollPosition));
				}
			}
			else if (mScrollableDown && IS_DOWN) {
				if (mIsDraggingThumb)
				{
					float aThumbWidth = mApp->mWidth / mMaxScrollPosition * mTrackWidth;
					float aScrollPosition = (mWidgetManager->mLastMouseX - (aThumbWidth / 2.0f)) / (mTrackWidth - aThumbWidth) * mMaxScrollPosition;
					mScrollPosition = max(0, min(aScrollPosition, mMaxScrollPosition));
				}
			}
			else {
				mScrollableDown = false;
				mIsDraggingThumb = false;
			}

			if (IS_DOWN && !mIsDraggingThumb && !mIsSwiping)
			{
				if (mWidgetManager->mLastMouseY < BOARD_HEIGHT / 2)
				{
					mSwipeStartX = mWidgetManager->mLastMouseX;
					mIsSwiping = true;
				}
			}

			if (!IS_DOWN)
			{
				mIsSwiping = false;
				mSwipeJustReleased = true;
			}

			if (mIsSwiping)
			{
				float deltaX = mWidgetManager->mLastMouseX - mSwipeStartX;

				mSwipeVelocityX -= deltaX * 0.01f;
				mSwipeVelocityX -= mSwipeVelocityX * 0.1f;
				mScrollAmount += mSwipeVelocityX;

				mSwipeStartX = mWidgetManager->mLastMouseX;
			}

			if (mSwipeJustReleased)
			{
				mScrollAmount += mSwipeVelocityX * 0.1f;
				mSwipeVelocityX *= 0.95f;

				if (fabs(mSwipeVelocityX) < 0.1f)
				{
					mSwipeVelocityX = 0.0f;
					mSwipeJustReleased = false;
				}
			}
		}

		if (!mHasFinishedSliding && mApp->mGameSelector->mSlideCounter == 0)
		{
			mSwitchStagesCounter = 50;
			mHasFinishedSliding = true;

			{
				int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(theCurrentId, QuickplayWidget::Quickplay_RoofStage)) - 1;
				for (int aLevel = 0; aLevel < 10; aLevel++) {
					ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
					aLevelButton->mVisible = true;
				}
			}
		}


		if (mHasFinishedSliding)
		{
			if (mSwitchStagesCounter > 0)
			{
				mSwitchStagesCounter--;

				if (!mIsSlidingOut)
				{
					{
						int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(thePreviousId, QuickplayWidget::Quickplay_RoofStage)) - 1;
						for (int aLevel = 0; aLevel < 10; aLevel++) {
							ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
							aLevelButton->MarkAllDirty();
							aLevelButton->mY = TodAnimateCurveFloatTime(100, 50, mSwitchStagesCounter, 35, -IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mHeight, TodCurves::CURVE_LINEAR);
							aLevelButton->MarkDirty();
							mWidgetManager->RehupMouse();
						}
					}

					{
						int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(theCurrentId, QuickplayWidget::Quickplay_RoofStage)) - 1;
						for (int aLevel = 0; aLevel < 10; aLevel++) {
							ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
							aLevelButton->MarkAllDirty();
							aLevelButton->mY = TodAnimateCurveFloatTime(50, 0, mSwitchStagesCounter, -IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT->mHeight, 35, TodCurves::CURVE_LINEAR);
							aLevelButton->MarkDirty();
							mWidgetManager->RehupMouse();
						}
					}
				}

				if (mSwitchStagesCounter == 50)
				{
					mScrollPosition = 0;
					mScrollAmount = 0;
					mSwipeVelocityX = 0;
					mIsSwiping = false;
					mSwipeJustReleased = false;
				}

			}
			else if (mSwitchStagesCounter == 0)
			{
				mSwitchStagesCounter = -1;

				if (thePreviousId != theCurrentId && thePreviousId >= QuickplayWidget::Quickplay_DayStage && thePreviousId <= QuickplayWidget::Quickplay_RoofStage)
				{
					int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(thePreviousId, QuickplayWidget::Quickplay_RoofStage)) - 1;
					for (int aLevel = 0; aLevel < 10; aLevel++) {
						ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
						aLevelButton->mVisible = false;
					}
				}

				DisableButtons(false);
				mIsScrollable = true;
			}
		}
	}


	Widget::Update();
	float aScrollSpeed = 1 + abs(mScrollAmount);
	mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, mMaxScrollPosition);
	mScrollAmount *= 0.9f;
}

void QuickplayWidget::Draw(Graphics* g) {
	g->SetLinearBlend(false);
	g->DrawImage(IMAGE_ZOMBATAR_MAIN_BG, 0, 0);
	g->SetLinearBlend(true);

	Graphics leafG(*g);
	leafG.mTransX -= BOARD_WIDTH;
	for (int i = 0; i < 3; i++)
	{
		mApp->ReanimationGet(mApp->mGameSelector->mFlowerReanimID[i])->Draw(&leafG);
	}

	if (thePreviousId != theCurrentId)
	{
		int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(thePreviousId, QuickplayWidget::Quickplay_RoofStage)) - 1;
		for (int aLevel = 0; aLevel < 10; aLevel++)
			DrawButton(g, 10 * aCurStage + aLevel);
	}

	{
		int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(theCurrentId, QuickplayWidget::Quickplay_RoofStage)) - 1;
		for (int aLevel = 0; aLevel < 10; aLevel++)
			DrawButton(g, 10 * aCurStage + aLevel);
	}

	if (mIsScrollable)
	{
		float aThumbWidth = mApp->mWidth / mMaxScrollPosition * mTrackWidth;
		const float aThumbX = 10 +  mScrollPosition / (float)mMaxScrollPosition * (mTrackWidth - aThumbWidth);
		const int aThumbAlpha = (int)(mScrollAmount * 10) != 0 || mIsDraggingThumb || aScrollArea.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY) ? 255 : 128;

		Graphics gScrollBar(*g);
		gScrollBar.SetColorizeImages(true);

		gScrollBar.SetColor(Color(0x808080)); 
		gScrollBar.mColor.mAlpha = aThumbAlpha / 2;
		gScrollBar.FillRect(aScrollArea);

		gScrollBar.SetColor(Color::White);
		gScrollBar.mColor.mAlpha = aThumbAlpha;
		gScrollBar.FillRect(aThumbX, aScrollArea.mY, aThumbWidth, aScrollArea.mHeight);

		if (mApp->mWidgetManager->mFocusWidget == this)
		{
			bool onScroll = false;

			if (aScrollArea.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY))
			{
				onScroll = true;
			}

			if (onScroll || mIsDraggingThumb)
			{
				mMouseIsDragging = true;
				if (mApp->mWidgetManager->mOverWidget)
					mApp->SetCursor(CURSOR_HAND);
			}
		}
	}
}

void QuickplayWidget::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	this->AddWidget(mPoolStageButton);
	this->AddWidget(mNightStageButton);
	this->AddWidget(mFogStageButton);
	this->AddWidget(mRoofStageButton);
	this->AddWidget(mDayStageButton);
	for (ButtonWidget* aButton : mLevelButtons)	this->AddWidget(aButton);
	this->AddWidget(mBackButton);
}

//0x44BCA0
void QuickplayWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	this->RemoveWidget(mPoolStageButton);
	this->RemoveWidget(mNightStageButton);
	this->RemoveWidget(mFogStageButton);
	this->RemoveWidget(mRoofStageButton);
	this->RemoveWidget(mDayStageButton);
	for (ButtonWidget* aButton : mLevelButtons)	this->RemoveWidget(aButton);
	this->RemoveWidget(mBackButton);
}

//0x44BD80
void QuickplayWidget::OrderInManagerChanged()
{
	this->PutInfront(mPoolStageButton, this);
	this->PutInfront(mNightStageButton, this);
	this->PutInfront(mFogStageButton, this);
	this->PutInfront(mRoofStageButton, this);
	this->PutInfront(mDayStageButton, this);
	for (ButtonWidget* aButton : mLevelButtons)	this->PutInfront(aButton, this);
	this->PutInfront(mBackButton, this);
	this->PutBehind(mApp->mGameSelector->mOverlayWidget, this);
}

void QuickplayWidget::ButtonDepress(int theId)
{
	if (theId <= QuickplayWidget::Quickplay_RoofStage)
		return;

	int level = theId - Quickplay_RoofStage;
	mApp->KillGameSelector();
	mApp->PreNewGame(GameMode::GAMEMODE_ADVENTURE, true, level);
}

void QuickplayWidget::ButtonMouseEnter(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;

	mApp->PlayFoley(FoleyType::FOLEY_BLEEP);
}

void QuickplayWidget::ButtonPress(int theId, int theClickCount)
{
	mApp->PlaySample(Sexy::SOUND_TAP);

	if (theId <= QuickplayWidget::Quickplay_RoofStage)
	{
		SelectStage(theId, true);
	}
}

void QuickplayWidget::SelectStage(int theId, bool doTransition)
{
	mIsScrollable = false;

	bool isStageButton = theId <= QuickplayWidget::Quickplay_RoofStage;

	if (theId == QuickplayWidget::Quickplay_Back)
	{
		mIsSlidingOut = true;
		mSlidingOutCounter = 50;
		//mApp->mGameSelector->DisableButtons(false);
		mIsScrollable = false;
	}
	else
	{
		thePreviousId = theCurrentId;
		theCurrentId = theId;
	}

	if (doTransition)
	{
		mSwitchStagesCounter = 100;

		{
			int aCurStage = max(QuickplayWidget::Quickplay_DayStage, min(theCurrentId, QuickplayWidget::Quickplay_RoofStage)) - 1;
			for (int aLevel = 0; aLevel < 10; aLevel++) {
				ButtonWidget* aLevelButton = mLevelButtons[10 * aCurStage + aLevel];
				aLevelButton->mVisible = true;
			}
		}
	}
	else
	{
		mScrollPosition = 0;
		mScrollAmount = 0;
		mSwipeVelocityX = 0;
		mIsSwiping = false;
		mSwipeJustReleased = false;
	}

	if (isStageButton)
	{
		DisableButtons(true);
	}

	const bool ON_DAY = theId == QuickplayWidget::Quickplay_DayStage;
	const bool ON_NIGHT = theId == QuickplayWidget::Quickplay_NightStage;
	const bool ON_POOL = theId == QuickplayWidget::Quickplay_PoolStage;
	const bool ON_FOG = theId == QuickplayWidget::Quickplay_FogStage;
	const bool ON_ROOF = theId == QuickplayWidget::Quickplay_RoofStage;
	const bool ON_BACK = theId == QuickplayWidget::Quickplay_Back;

	mDayStageButton->mOverImage = ON_DAY ? IMAGE_LEVELSELECTOR_DAY_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_DAY_BUTTON_HIGHLIGHT;
	mDayStageButton->mButtonImage = ON_DAY ? IMAGE_LEVELSELECTOR_DAY_BUTTON_PRESSED: IMAGE_LEVELSELECTOR_DAY_BUTTON;
	mDayStageButton->mMouseVisible = !ON_DAY;
	mNightStageButton->mOverImage = ON_NIGHT ? IMAGE_LEVELSELECTOR_NIGHT_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_NIGHT_BUTTON_HIGHLIGHT;
	mNightStageButton->mButtonImage = ON_NIGHT ? IMAGE_LEVELSELECTOR_NIGHT_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_NIGHT_BUTTON;
	mNightStageButton->mMouseVisible = !ON_NIGHT;
	mPoolStageButton->mOverImage = ON_POOL ? IMAGE_LEVELSELECTOR_POOL_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_POOL_BUTTON_HIGHLIGHT;
	mPoolStageButton->mButtonImage = ON_POOL ? IMAGE_LEVELSELECTOR_POOL_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_POOL_BUTTON;
	mPoolStageButton->mMouseVisible = !ON_POOL;
	mFogStageButton->mOverImage = ON_FOG ? IMAGE_LEVELSELECTOR_FOG_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_FOG_BUTTON_HIGHLIGHT;
	mFogStageButton->mButtonImage = ON_FOG ? IMAGE_LEVELSELECTOR_FOG_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_FOG_BUTTON;
	mFogStageButton->mMouseVisible = !ON_FOG;
	mRoofStageButton->mOverImage = ON_ROOF ? IMAGE_LEVELSELECTOR_ROOF_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_ROOF_BUTTON_HIGHLIGHT;
	mRoofStageButton->mButtonImage = ON_ROOF ? IMAGE_LEVELSELECTOR_ROOF_BUTTON_PRESSED : IMAGE_LEVELSELECTOR_ROOF_BUTTON;
	mRoofStageButton->mMouseVisible = !ON_ROOF;
	mBackButton->mOverImage = ON_BACK ? IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED : IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT;
	mBackButton->mButtonImage = ON_BACK ? IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED : IMAGE_BLANK;
	//mBackButton->mMouseVisible = !ON_BACK;
}

void QuickplayWidget::DrawButton(Graphics* g, int theLevelIndex)
{
	ButtonWidget* aLevelButton = mLevelButtons[theLevelIndex];
	if (!aLevelButton->mVisible)	return;

	int aLevel = theLevelIndex;
	int aStage = (int)(theLevelIndex / 10.0f);
	int aSubLevel = aLevel % 10;
	aLevelButton->mX = 10 + 186 * aSubLevel - mScrollPosition;

	if (aStage == 0)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_DAY_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}
	else if (aStage == 1)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_NIGHT_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}
	else if (aStage == 2)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_POOL_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}
	else if (aStage == 3)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_FOG_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}
	else if (aStage == 4 && aSubLevel == 9)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_BOSS_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}
	else if (aStage == 4)
	{
		g->DrawImage(IMAGE_LEVELSELECTOR_ROOF_THUMBNAIL, aLevelButton->mX + 15, aLevelButton->mY + 20);
	}

	if (aLevelButton->mIsOver)
		g->DrawImage(IMAGE_LEVELSELECTOR_LEVEL_BUTTON_HIGHLIGHT, aLevelButton->mX, aLevelButton->mY);
	else
		g->DrawImage(IMAGE_LEVELSELECTOR_LEVEL_BUTTON, aLevelButton->mX, aLevelButton->mY);

	SexyString aName = StrFormat(_S("Level %d-%d"), aStage + 1, aSubLevel + 1);
	Sexy::Font* theFont = aLevelButton->mIsOver ? Sexy::FONT_DWARVENTODCRAFT18 : Sexy::FONT_DWARVENTODCRAFT18YELLOW;
	Color theColor = aLevelButton->mIsOver ? Color(0x00FF00) : Color::White;
	TodDrawString(g, aName, aLevelButton->mX + 52 + 22 + 12.5f, aLevelButton->mY + 96 + 55, theFont, theColor, DS_ALIGN_CENTER);
}

void QuickplayWidget::MouseWheel(int theDelta)
{
	Widget::MouseWheel(theDelta);

	if (!mIsScrollable)	return;

	mWidgetManager->RehupMouse();

	mScrollAmount -= theDelta;
	mScrollAmount -= mScrollAmount * 0.1f;
}

void QuickplayWidget::MouseUp(int theX, int theY)
{
	if (mMouseIsDragging && mApp->mWidgetManager->mFocusWidget == this && mApp->mWidgetManager->mOverWidget)
	{
		bool onScroll = false;

		if (aScrollArea.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY))
		{
			onScroll = true;
		}

		if (!onScroll) mApp->SetCursor(CURSOR_POINTER);
	}

	Widget::MouseUp(theX, theY);
}

void QuickplayWidget::MouseMove(int theX, int theY)
{
	if (mMouseIsDragging && mApp->mWidgetManager->mFocusWidget == this && mApp->mWidgetManager->mOverWidget)
	{
		bool onScroll = false;

		if (aScrollArea.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY))
		{
			onScroll = true;
		}

		if (!onScroll) mApp->SetCursor(CURSOR_POINTER);
	}

	Widget::MouseMove(theX, theY);
}

void QuickplayWidget::DisableButtons(bool isDisabled)
{
	mPoolStageButton->SetDisabled(isDisabled);
	mNightStageButton->SetDisabled(isDisabled);
	mFogStageButton->SetDisabled(isDisabled);
	mRoofStageButton->SetDisabled(isDisabled);
	mDayStageButton->SetDisabled(isDisabled);
	mBackButton->SetDisabled(isDisabled);

	for (ButtonWidget* aLevelButton : mLevelButtons)	aLevelButton->SetDisabled(isDisabled);
}