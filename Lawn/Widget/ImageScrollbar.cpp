#include "ImageScrollbar.h"
#include "../../Sexy.TodLib/TodCommon.h"

ImageScrollbar::ImageScrollbar(LawnApp* theApp, ScrollMode theScrollMode)
	: Scrollbar(theApp, theScrollMode)
{
	mBackgroundColor = Color::White;
	mThumbColor = Color::White;
	mBackGroundImage = nullptr;
	mThumbImage = nullptr;
	mOverlayImage = nullptr;
	mDoStretchImage = true;
}

ImageScrollbar::~ImageScrollbar() {}

void ImageScrollbar::GetScaledPadding(float& thePadX, float& thePadY)
{
	float aScaleX = mDoStretchImage ? (float)mWidth / mBackGroundImage->GetWidth() : 1.0f;
	float aScaleY = mDoStretchImage ? (float)mHeight / mBackGroundImage->GetHeight() : 1.0f;

	thePadX *= aScaleX;
	thePadY *= aScaleY;
}

void ImageScrollbar::DrawBackground(Graphics* g)
{
	if (!mBackGroundImage)
	{
		Scrollbar::DrawBackground(g);
		return;
	}

	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mBackgroundColor);
	g->mColor.mAlpha = mBackgroundColor.mAlpha * aAlpha / 255;
	float aScaleX = mDoStretchImage ? (float)mWidth / mBackGroundImage->GetWidth() : 1.0f;
	float aScaleY = mDoStretchImage ? (float)mHeight / mBackGroundImage->GetHeight() : 1.0f;
	if (mScrollMode == ScrollMode::SCROLLMODE_VERTICAL)
		g->SetClipRect(0, 0, mWidth, mThumbRect.mY + mThumbPadY);
	else
		g->SetClipRect(0, 0, mThumbRect.mX + mThumbPadX, mHeight);
	TodDrawImageScaledF(g, mBackGroundImage, 0.0f, 0.0f, aScaleX, aScaleY);
	if (mScrollMode == ScrollMode::SCROLLMODE_VERTICAL)
		g->SetClipRect(0, mThumbRect.mY + mThumbRect.mHeight - mThumbPadY, mWidth, mHeight - mThumbRect.mY - mThumbRect.mHeight);
	else
		g->SetClipRect(mThumbRect.mX + mThumbRect.mWidth - mThumbPadX, 0, mWidth - mThumbRect.mX - mThumbRect.mWidth, mHeight);
	TodDrawImageScaledF(g, mBackGroundImage, 0.0f, 0.0f, aScaleX, aScaleY);
	g->PopState();
}

void ImageScrollbar::DrawThumb(Graphics* g)
{
	float oldPadX = mThumbPadX;
	float oldPadY = mThumbPadY;

	GetScaledPadding(mThumbPadX, mThumbPadY);

	if (!mThumbImage)
	{
		Scrollbar::DrawThumb(g);
		DrawOverlay(g);
		mThumbPadX = oldPadX;
		mThumbPadY = oldPadY;
		return;
	}

	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mThumbColor);
	g->mColor.mAlpha = mThumbColor.mAlpha * aAlpha / 255;
	int paddedX = mThumbRect.mX + mThumbPadX;
	int paddedY = mThumbRect.mY + mThumbPadY;
	float paddedWidth = mThumbRect.mWidth - 2 * mThumbPadX;
	float paddedHeight = mThumbRect.mHeight - 2 * mThumbPadY;
	float aScaleX = mDoStretchImage ? paddedWidth / mThumbImage->GetWidth() : 1.0f;
	float aScaleY = mDoStretchImage ? paddedHeight / mThumbImage->GetHeight() : 1.0f;
	TodDrawImageScaledF(g, mThumbImage, paddedX, paddedY, aScaleX, aScaleY);
	g->PopState();

	DrawOverlay(g);
	mThumbPadX = oldPadX;
	mThumbPadY = oldPadY;
}

void ImageScrollbar::DrawOverlay(Graphics* g)
{
	if (!mOverlayImage)		return;

	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mBackgroundColor);
	g->mColor.mAlpha = mThumbColor.mAlpha * aAlpha / 255;
	float aScaleX = mDoStretchImage ? (float)mWidth / mOverlayImage->GetWidth() : 1.0f;
	float aScaleY = mDoStretchImage ? (float)mHeight / mOverlayImage->GetHeight() : 1.0f;
	TodDrawImageScaledF(g, mOverlayImage, 0, 0, aScaleX, aScaleY);
	g->PopState();
}