#include "LanguageScreen.h"
#include "../../Resources.h"
#include "../../LawnApp.h"
#include "../../GameConstants.h"
#include "../System/Music.h"
#include "../../Sexy.TodLib/TodCommon.h"

LanguageWidget::LanguageWidget(LawnApp* theApp) {
	mApp = theApp;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;
	mApp->mMusic->StopAllMusic();

	mBackButton = MakeNewButton(LanguageWidget::Langauge_Back, this, _S("[BACK]"), Sexy::FONT_BRIANNETOD32, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mBackButton->mTextDownOffsetX = 0;
	mBackButton->mTextDownOffsetY = 0;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color::White;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(32, 205, 32);
	mBackButton->Resize(679, 526, 111, 64);

	mLanguageButtons[0] = MakeNewButton(LanguageWidget::Language_English, this, _S("English"), Sexy::FONT_BRIANNETOD32, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mLanguageButtons[1] = MakeNewButton(LanguageWidget::Language_English, this, _S("Filipino"), Sexy::FONT_BRIANNETOD32, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);


	int row = 1;
	for (NewLawnButton* aButton : mLanguageButtons)
	{
		aButton->mTextDownOffsetX = 0;
		aButton->mTextDownOffsetY = 0;
		aButton->mColors[ButtonWidget::COLOR_LABEL] = Color::White;
		aButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(32, 205, 32);
		aButton->Resize(250, 64 + 64 * row, 300, 64);
		row++;
	}
}

LanguageWidget::~LanguageWidget() {
	if (mBackButton)
		delete mBackButton;
	for (NewLawnButton* aButton : mLanguageButtons) delete aButton;
	
}

void LanguageWidget::Draw(Graphics* g) {
	g->SetColorizeImages(true);
	g->SetColor(Color::Black);
	g->FillRect(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

	TodDrawString(g, _S("[SELECT_LANGUAGE]"), 400, 64, Sexy::FONT_BRIANNETOD32, Color::White, DrawStringJustification::DS_ALIGN_CENTER);

	Graphics* clipG(g);
	
	g->SetColorizeImages(false);
}

void LanguageWidget::Update() {
	mBackButton->MarkDirty();
	for (NewLawnButton* aButton : mLanguageButtons) aButton->MarkDirty();
}

void LanguageWidget::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	this->AddWidget(mBackButton);
	mBackButton->MarkDirty();
	for (NewLawnButton* aButton : mLanguageButtons) this->AddWidget(aButton);
}

//0x44BCA0
void LanguageWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	this->RemoveWidget(mBackButton);
	for (NewLawnButton* aButton : mLanguageButtons) this->RemoveWidget(aButton);
}

void LanguageWidget::ButtonDepress(int theId)
{
	if (theId == LanguageWidget::Langauge_Back)
	{
		mApp->KillLanguageScreen();
		mApp->ShowGameSelector();
	}
}