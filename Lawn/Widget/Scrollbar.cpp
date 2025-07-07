#include "Scrollbar.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../Sexy.TodLib/TodCommon.h"

Scrollbar::Scrollbar(LawnApp* theApp, ScrollMode theScrollMode)
{
	mApp = theApp;
	mScrollMode = theScrollMode;
	mThumbColor = Color::White;
	mBackgroundColor = Color(0x808080);
	mOutAlpha = 128;
	mViewRect = Rect();
	mThumbRect = Rect();
	mScrollAmount = 0.0f;
	mScrollValue = 0;
	mScrollRange = 0;
	mDoFinger = true;
	mButtonNoDraw = false;
	mThumbPadX = 0.0f;
	mThumbPadY = 0.0f;
}

Scrollbar::~Scrollbar() {}

void Scrollbar::CalculateThumbSize()
{
	mThumbRect = Rect(0, 0, mWidth, mHeight);

	if (mScrollRange <= 0)
		return;

	if (mScrollMode == ScrollMode::SCROLLMODE_HORIZONTAL)
	{
		mThumbRect.mWidth = (mViewRect.mWidth / (mViewRect.mWidth + mScrollRange)) * mWidth;
		mThumbRect.mX = mScrollValue / mScrollRange * (mWidth - mThumbRect.mWidth);

	}
	else
	{
		mThumbRect.mHeight = (mViewRect.mHeight / (mViewRect.mHeight + mScrollRange)) * mHeight;
		mThumbRect.mY = mScrollValue / mScrollRange * (mHeight - mThumbRect.mHeight);
	}
}

void Scrollbar::SetScrollRange(float theScrollRange)
{
	mScrollRange = theScrollRange;
	CalculateThumbSize();
}

void Scrollbar::Resize(int theX, int theY, int theWidth, int theHeight)
{
	Widget::Resize(theX, theY, theWidth, theHeight);
	CalculateThumbSize();
}

void Scrollbar::SetView(int theX, int theY, int theWidth, int theHeight)
{
	mViewRect = Rect(theX, theY, theWidth, theHeight);
	CalculateThumbSize();
}

void Scrollbar::UpdateThumbPosition()
{
	if (mScrollMode == ScrollMode::SCROLLMODE_HORIZONTAL)
	{
		mThumbRect.mWidth = (mViewRect.mWidth / (mViewRect.mWidth + mScrollRange)) * mWidth;
		mThumbRect.mX = mScrollValue / mScrollRange * (mWidth - mThumbRect.mWidth);

	}
	else
	{
		mThumbRect.mHeight = (mViewRect.mHeight / (mViewRect.mHeight + mScrollRange)) * mHeight;
		mThumbRect.mY = mScrollValue / mScrollRange * (mHeight - mThumbRect.mHeight);
	}
}

void Scrollbar::Update()
{
	Widget::Update();

	if (mDisabled) return;

	float aScrollSpeed = 1 + abs(mScrollAmount) * 0.7f;
	mScrollValue = ClampFloat(mScrollValue += mScrollAmount * aScrollSpeed, 0, mScrollRange);
	if (!FloatApproxEqual(mScrollAmount, 0.0f)) 
	{
		UpdateThumbPosition();
		MarkDirty();
	}

	mScrollAmount *= 0.9f;
}

void Scrollbar::ScrollbarDown(int theX, int theY)
{
	if (mScrollRange <= 0)
		return;

	if (mScrollMode == ScrollMode::SCROLLMODE_HORIZONTAL)
	{
		mThumbRect.mWidth = (mViewRect.mWidth / (mViewRect.mWidth + mScrollRange)) * mWidth;
		mThumbRect.mX = mScrollValue / mScrollRange * (mWidth - mThumbRect.mWidth);

		float newThumbCenterX = theX - mThumbRect.mWidth / 2.0f;
		mScrollValue = (newThumbCenterX / (mWidth - mThumbRect.mWidth)) * mScrollRange;
	}
	else
	{
		mThumbRect.mHeight = (mViewRect.mHeight / (mViewRect.mHeight + mScrollRange)) * mHeight;
		mThumbRect.mY = mScrollValue / mScrollRange * (mHeight - mThumbRect.mHeight);

		float newThumbCenterY = theY - mThumbRect.mHeight / 2.0f;
		mScrollValue = (newThumbCenterY / (mHeight - mThumbRect.mHeight)) * mScrollRange;
	}

	mScrollValue = max(0.0f, min(mScrollValue, mScrollRange));

	if (mIsOver)
		mApp->SetCursor(CURSOR_DRAGGING);
}

void Scrollbar::MouseWheel(int theDelta)
{
	Widget::MouseWheel(theDelta);

	mScrollAmount -= theDelta;
	mScrollAmount -= mScrollAmount * 0.1f;
}

void Scrollbar::MouseUp(int theX, int theY, int theClickCount)
{
	Widget::MouseUp(theX, theY);

	if (mIsOver)
		mApp->SetCursor(CURSOR_HAND);
	else if (mWidgetManager->mOverWidget == NULL)
		mApp->SetCursor(CURSOR_POINTER);
}

void Scrollbar::MouseDown(int theX, int theY, int theClickCount)
{
	Widget::MouseDown(theX, theY, theClickCount);

	ScrollbarDown(theX, theY);
}

void Scrollbar::MouseDrag(int theX, int theY)
{
	Widget::MouseDrag(theX, theY);

	ScrollbarDown(theX, theY);
}


void Scrollbar::DrawBackground(Graphics* g)
{
	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mBackgroundColor);
	g->mColor.mAlpha = mBackgroundColor.mAlpha * (aAlpha / 2) / 255;
	if (mScrollMode == ScrollMode::SCROLLMODE_HORIZONTAL)
	{
		g->FillRect(0, 0, mThumbRect.mX + mThumbPadX, mHeight);
		g->FillRect(mThumbRect.mX + mThumbRect.mWidth - mThumbPadX, 0, mWidth - mThumbRect.mWidth - mThumbRect.mX, mThumbRect.mHeight);
	}
	else
	{
		g->FillRect(0, 0, mWidth, mThumbRect.mY + mThumbPadY);
		g->FillRect(0, mThumbRect.mY + mThumbRect.mHeight - mThumbPadY, mWidth, mHeight - mThumbRect.mY - mThumbRect.mHeight);
	}
	g->PopState();
}

void Scrollbar::DrawThumb(Graphics* g)
{
	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mThumbColor);
	g->mColor.mAlpha = mThumbColor.mAlpha * aAlpha / 255;
	g->FillRect(mThumbRect.mX + mThumbPadX, mThumbRect.mY + mThumbPadY, mThumbRect.mWidth - mThumbPadX * 2, mThumbRect.mHeight - mThumbPadY * 2);
	g->PopState();
}

void Scrollbar::Draw(Graphics* g)
{
	if (mDisabled || mButtonNoDraw)	return;
	g->PushState();
	g->SetColorizeImages(true);
	if (mOutAlpha != 0xFF)
	g->mColor.mAlpha = mIsOver || mIsDown ? 0xFF : mOutAlpha;
	DrawBackground(g);
	DrawThumb(g);
	g->PopState();
}