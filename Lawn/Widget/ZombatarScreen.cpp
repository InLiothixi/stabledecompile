#include "ZombatarScreen.h"
#include "../../Resources.h"
#include "../../LawnApp.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "GameSelector.h"
#include "GameButton.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../SexyAppFramework/MemoryImage.h"
#include "../../GameConstants.h"
#include "../../Sexy.TodLib/Reanimator.h"

// GOTY @Inliothixi
ZombatarWidget::ZombatarWidget(LawnApp* theApp) {
	TodLoadResources("DelayLoad_Zombatar");
	mApp = theApp;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;
	TodLoadResources("DelayLoad_Almanac");

	mBackButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Back,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_BLANK,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT
	);
	mBackButton->Resize(278, 528.5f, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mHeight);
	mBackButton->mClip = false;
	mBackButton->mTranslateX = 0;
	mBackButton->mTranslateY = 0;

	/*mNavigationID = 0;
	

	mFinishButton = MakeNewButton(
		FinishButton,
		this,
		"",
		nullptr,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT
	);
	mFinishButton->Resize(445, 472, IMAGE_ZOMBATAR_FINISHED_BUTTON->mWidth, IMAGE_ZOMBATAR_FINISHED_BUTTON->mHeight);
	mFinishButton->mClip = false;*/
}

ZombatarWidget::~ZombatarWidget() {
	if (mBackButton)
		delete mBackButton;

	//if (mFinishButton)
	//	delete mFinishButton;
}


bool mOnBackBtn = false;

void ZombatarWidget::Update() {
	mBackButton->MarkDirty();
	//mFinishButton->MarkDirty();
}

void ZombatarWidget::Draw(Graphics* g) {
	g->DrawImage(IMAGE_ZOMBATAR_MAIN_BG, 0, 0);

	Graphics leafG(*g);
	leafG.mTransX -= BOARD_WIDTH;
	for (int i = 0; i < 3; i++)
	{
		mApp->ReanimationGet(mApp->mGameSelector->mFlowerReanimID[i])->Draw(&leafG);
	}

	g->DrawImageF(IMAGE_ZOMBATAR_DAY_GRAVE, 8.55f, 432.05f);

	g->DrawImageF(IMAGE_ZOMBATAR_WIDGET_BG, 26, 25);
	g->DrawImageF(IMAGE_ZOMBATAR_BACKGROUND_BLANK, 596, 116);
	g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK_SKIN, 630.5f, 155);
	g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK, 630.5f, 155);
	g->DrawImageF(IMAGE_ZOMBATAR_WIDGET_INNER_BG, 152, 125);
	g->PushState();
	g->SetClipRect(599, 300, 176, 200);
	g->DrawImageF(IMAGE_ALMANAC_GROUNDDAY, 599.5f, 300);
	g->PopState();
	g->DrawImageF(IMAGE_ZOMBATAR_DISPLAY_WINDOW, 5, 0);
/*
	Image* navigationImg[27] = {
		IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_SKIN_BUTTON,
		IMAGE_ZOMBATAR_SKIN_BUTTON,
		IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_HAIR_BUTTON,
		IMAGE_ZOMBATAR_HAIR_BUTTON_OVER,
		IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON,
		IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_OVER,
		IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_TIDBITS_BUTTON,
		IMAGE_ZOMBATAR_TIDBITS_BUTTON_OVER,
		IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_EYEWEAR_BUTTON,
		IMAGE_ZOMBATAR_EYEWEAR_BUTTON_OVER,
		IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_CLOTHES_BUTTON,
		IMAGE_ZOMBATAR_CLOTHES_BUTTON_OVER,
		IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_ACCESSORY_BUTTON,
		IMAGE_ZOMBATAR_ACCESSORY_BUTTON_OVER,
		IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_HATS_BUTTON,
		IMAGE_ZOMBATAR_HATS_BUTTON_OVER,
		IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT,
		IMAGE_ZOMBATAR_BACKDROPS_BUTTON,
		IMAGE_ZOMBATAR_BACKDROPS_BUTTON_OVER
	};

	for (int i = 0; i < ZombatarNavigation::MAX_NAV; i++)
	{
		int imgMode = 0;
		if (mNavigationID != i)
		{
			imgMode++;
			if (Rect(58, 128 + (36 * i), 104, 36).Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
			{
				imgMode++;
			}
		}
		g->DrawImage(navigationImg[i * 3 + imgMode], 58, 128 + 36 * i);
	}


	g->DrawImage(IMAGE_ZOMBATAR_COLORS_BG, 221, 335);
	g->SetColorizeImages(true);
	for (int i = 0; i < 12; i++)
	{
		g->SetColor(Color::White);
		g->mColor.mAlpha = 127;
		g->mColor.mBlue -= 127;
		g->mColor.mGreen -= 127;
		g->DrawImage(IMAGE_ZOMBATAR_COLORPICKER, i % 9 * 25 + 238, i / 9 * 25 + 367);
	}*/
}

void ZombatarWidget::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	//this->AddWidget(mFinishButton);
	this->AddWidget(mBackButton);
}

//0x44BCA0
void ZombatarWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	//this->RemoveWidget(mFinishButton);
	this->RemoveWidget(mBackButton);
}

//0x44BD80
void ZombatarWidget::OrderInManagerChanged()
{
	//this->PutInfront(mFinishButton, this);
	this->PutInfront(mBackButton, this);
	this->PutBehind(mApp->mGameSelector->mOverlayWidget, this);
}

void ZombatarWidget::ButtonDepress(int theId)
{
	switch (theId)
	{
		case ZombatarWidget::ZombatarScreen_Back:
		{
			mBackButton->mButtonImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mBackButton->mDownImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mBackButton->mOverImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mApp->mGameSelector->SlideTo(0, 0);
			mApp->mGameSelector->mWidgetManager->SetFocus(mApp->mGameSelector);
			mApp->mGameSelector->mAdventureButton->SetDisabled(false);
			mApp->mGameSelector->mMinigameButton->SetDisabled(false);
			mApp->mGameSelector->mPuzzleButton->SetDisabled(false);
			mApp->mGameSelector->mOptionsButton->SetDisabled(false);
			mApp->mGameSelector->mQuitButton->SetDisabled(false);
			mApp->mGameSelector->mHelpButton->SetDisabled(false);
			mApp->mGameSelector->mChangeUserButton->SetDisabled(false);
			mApp->mGameSelector->mStoreButton->SetDisabled(false);
			mApp->mGameSelector->mAlmanacButton->SetDisabled(false);
			mApp->mGameSelector->mSurvivalButton->SetDisabled(false);
			mApp->mGameSelector->mZenGardenButton->SetDisabled(false);
#ifdef _HAS_ZOMBATAR
			mApp->mGameSelector->mZombatarButton->SetDisabled(false);
#endif
#ifdef _HAS_ACHIEVEMENTS
			mApp->mGameSelector->mAchievementsButton->SetDisabled(false);
#endif
#ifdef _HAS_MORESCREEN 
			mApp->mGameSelector->mQuickPlayButton->SetDisabled(false);
#endif
			break;
		}
	}

}

void ZombatarWidget::ButtonMouseEnter(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;

	if (theId == (int)ZombatarWidget::ZombatarScreen_Back)
	{
		mApp->PlayFoley(FoleyType::FOLEY_BLEEP);
	}
}

void ZombatarWidget::ButtonPress(int theId, int theClickCount)
{
	//if (theId == GameSelector::GameSelector_Adventure)
	//	mApp->PlaySample(Sexy::SOUND_GRAVEBUTTON);
	//else
	mApp->PlaySample(Sexy::SOUND_TAP);
}