#include "MoreSettingsDialog.h"
#include "../../LawnApp.h"
#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Checkbox.h"
#include "../../SexyAppFramework/Font.h"
#include "../../Resources.h"
#include "GameButton.h"
#include "../../SexyAppFramework/DDInterface.h"
#include "../System/Music.h"

MoreSettingsDialog::MoreSettingsDialog(LawnApp* theApp) :
	LawnDialog(theApp, Dialogs::DIALOG_MORESETTINGS, true, _S("MORE SETTINGS"), "", _S("CLOSE"), Dialog::BUTTONS_FOOTER)
{
	mApp = theApp;
	mPage1 = MakeButton(MoreSettingsDialog::MoreSettingsDialog_Page1, this, _S("1"));
	mPage2 = MakeButton(MoreSettingsDialog::MoreSettingsDialog_Page2, this, _S("2"));

	// PP1
	mHardwareAcceleration = MakeNewCheckbox(MoreSettingsDialog::MoreSettingsDialog_HardwareAcceleration, this, mApp->Is3DAccelerated());
	mCustomCursor = MakeNewCheckbox(MoreSettingsDialog::MoreSettingsDialog_CustomCursor, this, false); // !mApp->mWindowCursor
	mFPSToggle = MakeNewCheckbox(MoreSettingsDialog::MoreSettingsDialog_FPS, this, false); // mApp->mFPSToggled
	mAutoPause = MakeNewCheckbox(MoreSettingsDialog::MoreSettingsDialog_AutoPause, this, false); //  !mApp->mNoAutoPause
	mShowToolTip = MakeNewCheckbox(MoreSettingsDialog::MoreSettingsDialog_NoToolTip, this, false); //!mApp->mNoTooltip


	ChangePage(MoreSettingsDialog::MoreSettingsPage_1);

	Resize(0, 0, 600, 450);
	LawnApp::CenterDialog(this, mWidth, mHeight);
}

MoreSettingsDialog::~MoreSettingsDialog() 
{
	delete mPage1;
	delete mPage2;

	delete mHardwareAcceleration;
	delete mCustomCursor;
	delete mFPSToggle;
	delete mAutoPause;
	delete mShowToolTip;
}

void MoreSettingsDialog::AddedToManager(Sexy::WidgetManager* theWidgetManager) 
{
	LawnDialog::AddedToManager(theWidgetManager);
	AddWidget(mPage1);
	AddWidget(mPage2);

	AddWidget(mHardwareAcceleration);
	AddWidget(mCustomCursor);
	AddWidget(mFPSToggle);
	AddWidget(mAutoPause);
	AddWidget(mShowToolTip);
}

void MoreSettingsDialog::RemovedFromManager(Sexy::WidgetManager* theWidgetManager)
{
	LawnDialog::RemovedFromManager(theWidgetManager);
	RemoveWidget(mPage1);
	RemoveWidget(mPage2);

	RemoveWidget(mHardwareAcceleration);
	RemoveWidget(mCustomCursor);
	RemoveWidget(mFPSToggle);
	RemoveWidget(mAutoPause);
	RemoveWidget(mShowToolTip);
}

void MoreSettingsDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
	LawnDialog::Resize(theX, theY, theWidth, theHeight);

	int aStartY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET + 10;
	if (mDialogHeader.size() > 0)
	{
		int aOffsetY = aStartY - mHeaderFont->GetAscentPadding() + mHeaderFont->GetAscent();
		aStartY = aOffsetY - mHeaderFont->GetAscent() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
	}

	int startX = mBackgroundInsets.mLeft + mContentInsets.mLeft + 2;
	int offsetY = 0;
	int aWidth = mWidth - mBackgroundInsets.mLeft - mContentInsets.mLeft - IMAGE_DIALOG_BOTTOMRIGHT->GetWidth() / 2 + 4;

	if (mCurPage == MoreSettingsPage_1)
	{
		mHardwareAcceleration->Resize(startX, aStartY + offsetY - 12, 46, 45);
		mCustomCursor->Resize(startX, mHardwareAcceleration->mY + mHardwareAcceleration->mHeight / 1.75f + 10, 46, 45);
		mFPSToggle->Resize(startX, mCustomCursor->mY + mCustomCursor->mHeight / 1.75f + 10, 46, 45);

		startX += aWidth / 2;

		mAutoPause->Resize(startX, aStartY - 12, 46, 45);
		mShowToolTip->Resize(startX, mAutoPause->mY + mAutoPause->mHeight / 1.75f + 10, 46, 45);
	}
	else if (mCurPage == MoreSettingsPage_2)
	{
		//
		startX += aWidth / 2;
		//
	}

	mPage1->Resize(40, aStartY + 110 + 18, mPage1->mWidth, 46);
	mPage2->Resize(mPage1->mX + mPage1->mWidth + 2, mPage1->mY, mPage2->mWidth, 46);
}

void MoreSettingsDialog::Draw(Graphics* g)
{
	LawnDialog::Draw(g);

	int aStartY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
	if (mDialogHeader.size() > 0) 
	{
		int aOffsetY = aStartY - mHeaderFont->GetAscentPadding() + mHeaderFont->GetAscent();
		aStartY = aOffsetY - mHeaderFont->GetAscent() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
	}

	int startX = mBackgroundInsets.mLeft + mContentInsets.mLeft + 2;
	int width = mWidth - mBackgroundInsets.mLeft - mContentInsets.mLeft - IMAGE_DIALOG_BOTTOMRIGHT->GetWidth() / 2 + 4;

	Color fontColor(107, 109, 145);
	TodDrawString(g, StrFormat("%d/%d", mCurPage + 1, MoreSettingsPages::NUM_OF_PAGES),
		startX + width + IMAGE_DIALOG_BOTTOMRIGHT->GetWidth() / 2 - 70 /*60*/, aStartY - DIALOG_HEADER_OFFSET + 24 /*28*/, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_RIGHT);

	g->PushState();
	g->SetColor(fontColor);
	//g->DrawLine(startX, aStartY, mBackgroundInsets.mLeft + mContentInsets.mLeft + 2 + width, aStartY);
	g->DrawLine(startX, aStartY - 7, mBackgroundInsets.mLeft + mContentInsets.mLeft + 2 + width, aStartY - 7);
	g->PopState();

	int aTextOffsetX = 40;
	int aTextOffsetY = 24;

	if (mCurPage == MoreSettingsPage_1)
	{
		TodDrawString(g, "3D Acceleration", mHardwareAcceleration->mX + aTextOffsetX, mHardwareAcceleration->mY + aTextOffsetY, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_LEFT);
		TodDrawString(g, "Custom Cursor", mCustomCursor->mX + aTextOffsetX, mCustomCursor->mY + aTextOffsetY, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_LEFT);
		TodDrawString(g, "Show FPS", mFPSToggle->mX + aTextOffsetX, mFPSToggle->mY + aTextOffsetY, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_LEFT);
		TodDrawString(g, "Auto-Pause", mAutoPause->mX + aTextOffsetX, mAutoPause->mY + aTextOffsetY, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_LEFT);
		TodDrawString(g, "Show Tooltip", mShowToolTip->mX + aTextOffsetX, mShowToolTip->mY + aTextOffsetY, FONT_DWARVENTODCRAFT18, fontColor, DS_ALIGN_LEFT);
	}
	else if (mCurPage == MoreSettingsPage_2)
	{
		
	}
}

void MoreSettingsDialog::CheckboxChecked(int theId, bool checked)
{
	switch (theId)
	{
		case MoreSettingsDialog::MoreSettingsDialog_HardwareAcceleration:
		{
			if (checked)
			{
				if (!mApp->Is3DAccelerationSupported())
				{
					mHardwareAcceleration->SetChecked(false, false);
					mApp->DoDialog(
						Dialogs::DIALOG_INFO,
						true,
						_S("[NOT_SUPPORTED_HEADER]"),
						_S("[NOT_SUPPORTED_LINES]"),
						_S("[OK_LABEL]"),
						Dialog::BUTTONS_FOOTER
					);

					return;
				}
				else if (!mApp->Is3DAccelerationRecommended())
				{
					mApp->DoDialog(
						Dialogs::DIALOG_INFO,
						true,
						_S("[WARNING_HEADER]"),
						_S("[WARNING_LINES]"),
						_S("[OK_LABEL]"),
						Dialog::BUTTONS_FOOTER
					);
				}

			}

			break;
		}
	}

	mApp->PlaySample(SOUND_BUTTONCLICK);
}

void MoreSettingsDialog::ChangePage(MoreSettingsPages thePage)
{
	MoreSettingsPages prevPage = mCurPage;
	mCurPage = thePage;
	if (prevPage != mCurPage)
	{
		mApp->PlaySample(SOUND_BUTTONCLICK);
	}

	mHardwareAcceleration->mVisible = mCustomCursor->mVisible = mFPSToggle->mVisible =
	mAutoPause->mVisible  = mShowToolTip->mVisible = mCurPage == MoreSettingsPage_1;

	Resize(mX, mY, mWidth, mHeight);
}

void MoreSettingsDialog::ButtonDepress(int theId)
{
	LawnDialog::ButtonDepress(theId);

	MoreSettingsPages prevPage = mCurPage;

	switch (theId)
	{
	case MoreSettingsDialog::MoreSettingsDialog_Page1:
		ChangePage((MoreSettingsPages)max((int)mCurPage - 1, 0));
		break;
	case MoreSettingsDialog::MoreSettingsDialog_Page2:
		ChangePage((MoreSettingsPages)min((int)mCurPage + 1, (int)MoreSettingsPages::NUM_OF_PAGES - 1));
		break;
	}
}

void MoreSettingsDialog::Update()
{
	LawnDialog::Update();
}