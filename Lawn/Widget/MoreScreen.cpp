#include "MoreScreen.h"
#include "GameButton.h"
#include "GameSelector.h"
#include "../../LawnApp.h"
#include "../../Resources.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../SexyAppFramework/Dialog.h"
#include "../../GameConstants.h"
#include "../System/PlayerInfo.h"

bool aOnBackBtn = false;

MoreWidget::MoreWidget(LawnApp* theApp) {
	mApp = theApp;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;

	mBackButton = MakeNewButton(
		MoreWidget::More_Back, 
		this, _S(""), 
		nullptr, 
		Sexy::IMAGE_QUICKPLAY_BACK_BUTTON,
		Sexy::IMAGE_QUICKPLAY_BACK_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_QUICKPLAY_BACK_BUTTON_HIGHLIGHT);
	mBackButton->mClip = false;
	mBackButton->Resize(651, 455, Sexy::IMAGE_QUICKPLAY_BACK_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_QUICKPLAY_BACK_BUTTON_HIGHLIGHT->mHeight);
	mBackButton->mTranslateX = 0;
	mBackButton->mTranslateY = 0;

	mQuickplayButton = MakeNewButton(
		MoreWidget::More_Quickplay,
		this, _S(""),
		nullptr,
		Sexy::IMAGE_QUICKPLAY_SIGN,
		Sexy::IMAGE_QUICKPLAY_SIGN_HIGHLIGHT,
		Sexy::IMAGE_QUICKPLAY_SIGN_HIGHLIGHT);
	mQuickplayButton->mClip = false;
	mQuickplayButton->Resize(25, 377, Sexy::IMAGE_QUICKPLAY_SIGN_HIGHLIGHT->mWidth, Sexy::IMAGE_QUICKPLAY_SIGN_HIGHLIGHT->mHeight);
	mQuickplayButton->mTranslateX = 0;
	mQuickplayButton->mTranslateY = 0;
}

MoreWidget::~MoreWidget() {
	if (mBackButton)
		delete mBackButton;
	if (mQuickplayButton)
		delete mQuickplayButton;
}

void MoreWidget::Update() {
	Widget::Update();
	mBackButton->MarkDirty();
	mQuickplayButton->MarkDirty();

}

void MoreWidget::Draw(Graphics* g) {
	bool hadFocus = false;
	g->SetLinearBlend(true);

	g->DrawImage(IMAGE_SELECTORSCREEN_MOREWAYSTOPLAY_BG, 0, 0);
}

void MoreWidget::MouseDown(int x, int y, int theClickCount) {
	(void)theClickCount;

	if (mApp->mGameSelector->mSlideCounter > 0)
		return;
}

void MoreWidget::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	this->AddWidget(mBackButton);
	this->AddWidget(mQuickplayButton);
}

void MoreWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	this->RemoveWidget(mBackButton);
	this->RemoveWidget(mQuickplayButton);
}

void MoreWidget::OrderInManagerChanged()
{
	this->PutInfront(mBackButton, this);
	this->PutInfront(mQuickplayButton, this);
}

void MoreWidget::ButtonMouseEnter(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;

	mApp->PlayFoley(FoleyType::FOLEY_BLEEP);
}

void MoreWidget::ButtonPress(int theId, int theClickCount)
{
	mApp->PlaySample(Sexy::SOUND_TAP);
}

void MoreWidget::ButtonDepress(int theId)
{
	if (theId == MoreWidget::More_Back)	mApp->mGameSelector->ShowGameSelectorScreen();
	else if (theId == MoreWidget::More_Quickplay) mApp->mGameSelector->ShowQuickplayScreen();
}