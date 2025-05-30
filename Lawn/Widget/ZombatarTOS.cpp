#include "ZombatarTOS.h"
#include "../../LawnApp.h"
#include "../../Resources.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../SexyAppFramework/ImageFont.h"
#include "../../Sexy.TodLib/EffectSystem.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/Checkbox.h"
#include "../System/PlayerInfo.h"
#include "GameSelector.h"
#include "GameButton.h"

Rect mScrollArea(-1, -1, -1, -1);
Rect mSwipeArea(-1, -1, -1, -1);
//0x45D610
ZombatarTOS::ZombatarTOS(LawnApp* theApp) : LawnDialog(
	theApp,
	DIALOG_ZOMBATARTOS,
	true,
	_S("[ZOMBATAR_TOS_HEADER]"),
	_S("[ZOMBATAR_TOS]"),
	_S(""),
	Dialog::BUTTONS_NONE)
{
    mScrollAmount = 0;
    mScrollPosition = 0;
    mMaxScrollPosition = 500;
    mHintCounter = -1;
    mIsDraggingThumb = false;
    mScrollableDown = false;
    mMouseIsDragging = false;
    mIsSwiping = false;
    mSwipeStartY = -1;
    mSwipeVelocityY = 0.0f;
    mSwipeJustReleased = false;
    
    mVerticalCenterText = false;
	SetColor(1, { 0xFF, 0xFF, 0xFF });
	SetLinesFont(Sexy::FONT_PICO129);
   
    mBackButton = MakeNewButton(
        ZombatarTOS::ZOMBATARTOS_BACK,
        this,
        _S(""),
        nullptr,
        Sexy::IMAGE_ZOMBATAR_BACK_BUTTON,
        Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT,
        Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT
    );
    mBackButton->mClip = false;
    mBackButton->mTranslateX = 0;
    mBackButton->mTranslateY = 0;

    mAgreementCheckbox = MakeNewCheckbox(ZombatarTOS::ZOMBATARTOS_AGREEMENT, this, false);

    mAcceptButton = MakeNewButton(
        ZombatarTOS::ZOMBATARTOS_ACCEPT,
        this,
        _S(""),
        nullptr,
        Sexy::IMAGE_ZOMBATAR_ACCEPT_BUTTON,
        Sexy::IMAGE_ZOMBATAR_ACCEPT_BUTTON_HIGHLIGHT,
        Sexy::IMAGE_ZOMBATAR_ACCEPT_BUTTON_HIGHLIGHT
    );
    mAcceptButton->mClip = false;
    mAcceptButton->mTranslateX = 0;
    mAcceptButton->mTranslateY = 0;

    CalcSize(0, 0);
}

//0x45D7E0��0x45D800
ZombatarTOS::~ZombatarTOS()
{
    delete mBackButton;
    delete mAgreementCheckbox;
    delete mAcceptButton;
}

//0x45D870
void ZombatarTOS::AddedToManager(WidgetManager* theWidgetManager)
{
	LawnDialog::AddedToManager(theWidgetManager);
    this->AddWidget(mBackButton);
    this->AddWidget(mAgreementCheckbox);
    this->AddWidget(mAcceptButton);
}

//0x45D8E0
void ZombatarTOS::RemovedFromManager(WidgetManager* theWidgetManager)
{
	LawnDialog::RemovedFromManager(theWidgetManager);
    this->RemoveWidget(mBackButton);
    this->RemoveWidget(mAgreementCheckbox);
    this->RemoveWidget(mAcceptButton);
}

int ZombatarTOS::GetPreferredHeight(int theWidth)
{
	return LawnDialog::GetPreferredHeight(theWidth);
}

//0x45D910
void ZombatarTOS::Resize(int theX, int theY, int theWidth, int theHeight)
{
	LawnDialog::Resize(theX, theY, theWidth, theHeight);}

//0x45D970
void ZombatarTOS::Draw(Graphics* g)
{
	//LawnDialog::Draw(g);

    if (!mDrawStandardBack)
        return;

    g->SetLinearBlend(true);

    Image* aBottomLeftImage = IMAGE_DIALOG_BOTTOMLEFT;
    Image* aBottomMiddleImage = IMAGE_DIALOG_BOTTOMMIDDLE;
    Image* aBottomRightImage = IMAGE_DIALOG_BOTTOMRIGHT;
    if (mTallBottom)
    {
        aBottomLeftImage = IMAGE_DIALOG_BIGBOTTOMLEFT;
        aBottomMiddleImage = IMAGE_DIALOG_BIGBOTTOMMIDDLE;
        aBottomRightImage = IMAGE_DIALOG_BIGBOTTOMRIGHT;
    }

    int aRepeatX = (mWidth - IMAGE_DIALOG_TOPRIGHT->mWidth - IMAGE_DIALOG_TOPLEFT->mWidth) / IMAGE_DIALOG_TOPMIDDLE->mWidth;
    int aRepeatY = (mHeight - IMAGE_DIALOG_TOPLEFT->mHeight - aBottomLeftImage->mHeight - DIALOG_HEADER_OFFSET) / IMAGE_DIALOG_CENTERLEFT->mHeight;

    int aPosX = 0;
    int aPosY = DIALOG_HEADER_OFFSET;
    g->DrawImage(IMAGE_DIALOG_TOPLEFT, aPosX, aPosY);
    aPosX += IMAGE_DIALOG_TOPLEFT->mWidth;
    for (int i = 0; i < aRepeatX; i++)
    {
        g->DrawImage(IMAGE_DIALOG_TOPMIDDLE, aPosX, aPosY);
        aPosX += IMAGE_DIALOG_TOPMIDDLE->mWidth;
    }
    g->DrawImage(IMAGE_DIALOG_TOPRIGHT, aPosX, aPosY);

    aPosY += IMAGE_DIALOG_TOPRIGHT->mHeight;
    for (int y = 0; y < aRepeatY; y++)
    {
        aPosX = 0;

        g->DrawImage(IMAGE_DIALOG_CENTERLEFT, aPosX, aPosY);
        aPosX += IMAGE_DIALOG_CENTERLEFT->mWidth;

        for (int x = 0; x < aRepeatX; x++)
        {
            g->DrawImage(IMAGE_DIALOG_CENTERMIDDLE, aPosX, aPosY);
            aPosX += IMAGE_DIALOG_CENTERMIDDLE->mWidth;
        }

        g->DrawImage(IMAGE_DIALOG_CENTERRIGHT, aPosX, aPosY);
        aPosY += IMAGE_DIALOG_CENTERLEFT->mHeight;
    }

    aPosX = 0;
    g->DrawImage(aBottomLeftImage, aPosX, aPosY);
    aPosX += aBottomLeftImage->mWidth;
    for (int i = 0; i < aRepeatX; i++)
    {
        g->DrawImage(aBottomMiddleImage, aPosX, aPosY);
        aPosX += aBottomMiddleImage->mWidth;
    }
    g->DrawImage(aBottomRightImage, aPosX, aPosY);
    g->DrawImage(IMAGE_DIALOG_HEADER, (mWidth - IMAGE_DIALOG_HEADER->mWidth) / 2 - 5, 0);

    int aFontY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
    if (mDialogHeader.size() > 0)
    {
        int aOffsetY = aFontY - mHeaderFont->GetAscentPadding() + mHeaderFont->GetAscent();
        g->SetFont(mHeaderFont);
        g->SetColor(mColors[Dialog::COLOR_HEADER]);
        WriteCenteredLine(g, aOffsetY, mDialogHeader);
        aFontY = aOffsetY - mHeaderFont->GetAscent() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
    }

    g->SetFont(mLinesFont);
    g->SetColor(mColors[Dialog::COLOR_LINES]);
    int aLinesAreaWidth = mWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - 4;
    Rect aRect(mBackgroundInsets.mLeft + mContentInsets.mLeft + 2, aFontY, aLinesAreaWidth, 0);
    if (mVerticalCenterText)
    {
        int aLinesHeight = GetWordWrappedHeight(g, aLinesAreaWidth, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset);
        int aLinesAreaHeight = mHeight - mContentInsets.mBottom - mBackgroundInsets.mBottom - mButtonHeight - aFontY - 55;
        if (mTallBottom)
        {
            aLinesAreaHeight -= 36;
        }
        aRect.mY += (aLinesAreaHeight - aLinesHeight) / 2;
    }

    aRect.mX += 20;
    aRect.mWidth -= 80;

    Graphics aLineGraphics(*g);
    aLineGraphics.SetClipRect(Rect(aRect.mX, aRect.mY, aRect.mWidth, 160));

    aRect.mY -= mScrollPosition;
    TodDrawStringWrapped(&aLineGraphics, mDialogLines, aRect, Sexy::FONT_PICO129, g->mColor, DS_ALIGN_LEFT);

    if (mWidgetManager->mFocusWidget == this)
    {
        float aThumbHeight = mScrollArea.mHeight / mMaxScrollPosition * mScrollArea.mHeight;
        const float aThumbY = mScrollArea.mY + mScrollPosition / (float)mMaxScrollPosition * (mScrollArea.mHeight - aThumbHeight);
        const int aThumbAlpha = (int)(mScrollAmount * 10) != 0  || mIsDraggingThumb || mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY) ? 255 : 128;

        Graphics gScrollBar(*g);
        gScrollBar.SetColorizeImages(true);

        gScrollBar.SetColor(Color(0x808080));
        gScrollBar.mColor.mAlpha = aThumbAlpha / 2;
        gScrollBar.FillRect(mScrollArea);

        gScrollBar.SetColor(Color::White);
        gScrollBar.mColor.mAlpha = aThumbAlpha;
        gScrollBar.FillRect(mScrollArea.mX, aThumbY, mScrollArea.mWidth, aThumbHeight);


        bool onScroll = false;

        if (mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        {
            onScroll = true;
        }

        if (onScroll || mIsDraggingThumb)
        {
            mMouseIsDragging = true;
            mApp->SetCursor(CURSOR_HAND);
        }
        
    }

    if (mHintCounter != -1)
    {
        Graphics tosG(*g);
        tosG.SetLinearBlend(true);
        tosG.SetColorizeImages(true);
        tosG.SetColor(Color::White);
        if (mHintCounter <= 100) tosG.mColor.mAlpha = (int)(255 * TodAnimateCurveFloatTime(0, 100, mHintCounter, 1.0f, 0.0f, TodCurves::CURVE_LINEAR));
        else if (mHintCounter > 100) tosG.mColor.mAlpha = (int)(255 * TodAnimateCurveFloatTime(100, 200, mHintCounter, 0.0f, 1.0f, TodCurves::CURVE_LINEAR));
        tosG.DrawImage(Sexy::IMAGE_ZOMBATAR_TOS_ARROW, mAgreementCheckbox->mX + 20, mAgreementCheckbox->mY - Sexy::IMAGE_ZOMBATAR_TOS_ARROW->mHeight);
    }
}

void ZombatarTOS::CalcSize(int theExtraX, int theExtraY)
{
    // 根据边距计算一个最小宽度
    int aWidth = mBackgroundInsets.mLeft + mBackgroundInsets.mRight + mContentInsets.mLeft + mContentInsets.mRight + theExtraX;
    // 最小宽度需要额外考虑到标题字符串的宽度
    if (mDialogHeader.size() > 0) aWidth += mHeaderFont->StringWidth(mDialogHeader);
    // 对话框贴图的最小宽度
    int aTopMidWidth = Sexy::IMAGE_DIALOG_TOPMIDDLE->mWidth;
    int aImageWidth = Sexy::IMAGE_DIALOG_TOPLEFT->mWidth + Sexy::IMAGE_DIALOG_TOPRIGHT->mWidth + aTopMidWidth;
    // 计算最终的宽度
    if (aWidth <= aImageWidth)
    {
        aWidth = aImageWidth;
    }
    else if (aTopMidWidth > 0)
    {
        int anExtraWidth = (aWidth - aImageWidth) % aTopMidWidth;
        if (anExtraWidth)
        {
            aWidth += aTopMidWidth - anExtraWidth;
        }
    }

    // 根据边距计算一个最小高度
    int aHeight = mBackgroundInsets.mTop + mBackgroundInsets.mBottom + mContentInsets.mTop + mContentInsets.mBottom + theExtraY + DIALOG_HEADER_OFFSET;
    // 额外考虑到标题字符串的高度
    if (mDialogHeader.size() > 0)
    {
        aHeight += -mHeaderFont->GetAscentPadding() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
    }
    // 对话框宽度和高度额外考虑正文文本
    if (mDialogLines.size() > 0)
    {
        aWidth += aTopMidWidth;
        aHeight += 190;
    }

    aHeight += mButtonHeight;

    // 对话框贴图的最小高度
    int aBottomHeight = (mTallBottom ? Sexy::IMAGE_DIALOG_BIGBOTTOMLEFT : Sexy::IMAGE_DIALOG_BOTTOMLEFT)->mHeight;
    int aImageHeight = Sexy::IMAGE_DIALOG_TOPLEFT->mHeight + aBottomHeight + DIALOG_HEADER_OFFSET;
    // 计算最终的高度
    
    /*if (aHeight < aImageHeight)
    {
        aHeight = aImageHeight;
    }
    else*/
    {
        int aCenterHeight = Sexy::IMAGE_DIALOG_CENTERLEFT->mHeight;
        int anExtraHeight = (aHeight - aImageHeight) % aCenterHeight;
        if (anExtraHeight) aHeight += aCenterHeight - anExtraHeight;
    }

    int aButtonAreaX = mContentInsets.mLeft + mBackgroundInsets.mLeft - 5;
    int aButtonAreaY = aHeight - mContentInsets.mBottom - mBackgroundInsets.mBottom - IMAGE_BUTTON_LEFT->mHeight + 2;
    int aButtonAreaWidth = aWidth - mContentInsets.mRight - mBackgroundInsets.mRight - mBackgroundInsets.mLeft - mContentInsets.mLeft + 8;
    int aButtonMinWidth = IMAGE_BUTTON_LEFT->mWidth + IMAGE_BUTTON_RIGHT->mWidth;
    int aBtnMidWidth = IMAGE_BUTTON_MIDDLE->mWidth;
    int aButtonExtraWidth = (aButtonAreaWidth - 10) / 2 - aBtnMidWidth - aButtonMinWidth + 1;
    // 计算按钮可以拓展的额外宽度
    if (aButtonExtraWidth <= 0)
    {
        aButtonExtraWidth = 0;
    }
    else if (aBtnMidWidth > 0)
    {
        int anExtraWidth = aButtonExtraWidth % aBtnMidWidth;
        if (anExtraWidth)
        {
            // 不足中部贴图宽度的部分补充至中部贴图宽度
            aButtonExtraWidth += aBtnMidWidth - anExtraWidth;
        }
    }
    // 最终宽度
    int aButtonWidth = aButtonMinWidth + aButtonExtraWidth;

    mBackButton->Resize(aButtonAreaX, aButtonAreaY, Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT->mHeight);
    mAgreementCheckbox->Resize(aButtonAreaWidth - aButtonWidth + aButtonAreaX + 99, aButtonAreaY - 5, 46, 45);
    mAcceptButton->Resize(aButtonAreaWidth - aButtonWidth + aButtonAreaX + 150, aButtonAreaY, Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_BACK_BUTTON_HIGHLIGHT->mHeight);

    {
        int aFontY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
        if (mDialogHeader.size() > 0)
        {
            int aOffsetY = aFontY - mHeaderFont->GetAscentPadding() + mHeaderFont->GetAscent();
            aFontY = aOffsetY - mHeaderFont->GetAscent() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
        }
        int aLinesAreaWidth = mWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - 84;
        Rect aRect(mBackgroundInsets.mLeft + mContentInsets.mLeft + 22, aFontY, aLinesAreaWidth, 0);
        mScrollArea = Rect(aRect.mX + aRect.mWidth + 10, aRect.mY, 5, 160);
        mSwipeArea = Rect(aRect.mX, aRect.mY, aRect.mWidth + 10, 160);
    }

    Resize(mX, mY, aWidth, aHeight);
}

void ZombatarTOS::MouseWheel(int theDelta)
{
    LawnDialog::MouseWheel(theDelta);

    mScrollAmount -= theDelta;
    mScrollAmount -= mScrollAmount * 0.1f;
}

void ZombatarTOS::Update()
{
    LawnDialog::Update();
    float aScrollSpeed = 1 + abs(mScrollAmount) * 0.1f;
    mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, mMaxScrollPosition);
    mScrollAmount *= 0.9f;

    if (!mButtonDelay)
    {
        mBackButton->SetDisabled(false);
        mAcceptButton->SetDisabled(false);
    }
    if (mHintCounter != - 1)
        mHintCounter = (mHintCounter + 1) % 200;

    if (mWidgetManager->mFocusWidget == this)
    {
        const bool IS_DOWN = mWidgetManager->mFocusWidget->mIsDown;

        if (!mScrollableDown && IS_DOWN) {
            if (mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
            {
                mScrollableDown = true;
                mIsDraggingThumb = true;
                float aThumbHeight = mScrollArea.mHeight / mMaxScrollPosition * mScrollArea.mHeight;
                float aScrollPosition = (mWidgetManager->mLastMouseY - mY - 75 - (mScrollArea.mHeight / 2.0f)) / (mScrollArea.mHeight - aThumbHeight) * mMaxScrollPosition;
                mScrollPosition = max(0, min(aScrollPosition, mMaxScrollPosition));
            }
        }
        else if (mScrollableDown && IS_DOWN) {
            if (mIsDraggingThumb)
            {
                float aThumbHeight = mScrollArea.mHeight / mMaxScrollPosition * mScrollArea.mHeight;
                float aScrollPosition = (mWidgetManager->mLastMouseY - mY - 75 - (mScrollArea.mHeight / 2.0f)) / (mScrollArea.mHeight - aThumbHeight) * mMaxScrollPosition;
                mScrollPosition = max(0, min(aScrollPosition, mMaxScrollPosition));
            }
        }
        else {
            mScrollableDown = false;
            mIsDraggingThumb = false;
        }

        if (IS_DOWN && !mIsDraggingThumb && !mIsSwiping)
        {
            if (mSwipeArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
            {
                mSwipeStartY = mWidgetManager->mLastMouseY - mY;
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
            float deltaY = mWidgetManager->mLastMouseY - mY - mSwipeStartY;

            mSwipeVelocityY -= deltaY * 0.01f;
            mSwipeVelocityY -= mSwipeVelocityY * 0.1f;
            mScrollAmount += mSwipeVelocityY;

            mSwipeStartY = mWidgetManager->mLastMouseY - mY;
        }

        if (mSwipeJustReleased)
        {
            mScrollAmount += mSwipeVelocityY * 0.1f;
            mSwipeVelocityY *= 0.95f;

            if (fabs(mSwipeVelocityY) < 0.1f)
            {
                mSwipeVelocityY = 0.0f;
                mSwipeJustReleased = false;
            }
        }
        
    }

    MarkDirty();
}

void ZombatarTOS::SetButtonDelay(int theDelay)
{
    LawnDialog::SetButtonDelay(theDelay);
    mBackButton->SetDisabled(true);
    mAcceptButton->SetDisabled(true);
}

void ZombatarTOS::ButtonDepress(int theId)
{
    switch (theId)
    {
        case ZombatarTOS::ZOMBATARTOS_BACK:
        {
            mApp->KillDialog(Dialogs::DIALOG_ZOMBATARTOS);
            break;
        }
        case ZombatarTOS::ZOMBATARTOS_ACCEPT:
        {
            if (!mAgreementCheckbox->mChecked) 
            {
                if (mHintCounter == -1)
                {
                    mHintCounter = 0;
                }
            }
            else if (mAgreementCheckbox->mChecked)   
            {
                mApp->mPlayerInfo->mAckZombatarTOS = true;
                mApp->KillDialog(Dialogs::DIALOG_ZOMBATARTOS);
                mApp->mWidgetManager->SetFocus(mApp->mGameSelector);
                mApp->mGameSelector->ShowZombatarScreen();
            }
            break;
        }
    }
}

void ZombatarTOS::CheckboxChecked(int theId, bool checked)
{
    switch (theId)
    {
        case ZombatarTOS::ZOMBATARTOS_AGREEMENT:
        {
            mHintCounter = -1;
            break;
        }
    }
}

void ZombatarTOS::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
    if (mMouseIsDragging && mApp->mWidgetManager->mFocusWidget == this)
    {
        bool onScroll = false;

        if (mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        {
            onScroll = true;
        }

        if (!onScroll) mApp->SetCursor(CURSOR_POINTER);
        else return;
    }

    if (mSwipeArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        return;

    LawnDialog::MouseDown(x, y, theBtnNum, theClickCount);
}

void ZombatarTOS::MouseUp(int x, int y, int theClickCount)
{
    if (mMouseIsDragging && mApp->mWidgetManager->mFocusWidget == this)
    {
        bool onScroll = false;

        if (mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY)) 
        {
            onScroll = true;
        }

        if (!onScroll) mApp->SetCursor(CURSOR_POINTER);
        else return;
    }

    if (mSwipeArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        return;

    LawnDialog::MouseUp(x, y, theClickCount);
}

void ZombatarTOS::MouseMove(int theX, int theY)
{
    if (mMouseIsDragging && mApp->mWidgetManager->mFocusWidget == this)
    {
        bool onScroll = false;

        if (mScrollArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        {
            onScroll = true;
        }

        if (!onScroll) mApp->SetCursor(CURSOR_POINTER);
        else return;
    }

    if (mSwipeArea.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY))
        return;

    Widget::MouseMove(theX, theY);
}