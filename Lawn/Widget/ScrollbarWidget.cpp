#include "ScrollbarWidget.h"
#include "../../SexyAppFramework/WidgetManager.h"

ScrollbarWidget::ScrollbarWidget(LawnApp* theApp, ScrollbarMode theScrollbarMode) {
	mApp = theApp;
	mScrollbarMode = theScrollbarMode;
	mThumbColor = Color(63, 64, 86); // Base Color
	mThumbInnerHighlight = Color(80, 81, 108);
	mThumbInnerHighlight2 = Color(84, 85, 113); // Intersecting Inner Highlight
	mThumbInnerHighlightShadow = Color(44, 45, 59); // Intersecting Inner Highlight and Inner Shadow
	mThumbInnerShadow = Color(40, 41, 54);
	mThumbInnerShadow2 = Color(34, 35, 46); // Intersecting Inner Shadow
	mThumbOuterShadow = Color(30, 28, 34);
	mThumbOuterShadow2 = Color(22, 19, 21); // Intersecting Outer Shadow
	mBackgroundColor = Color(152, 149, 188);
	mViewport = Rect();
	mThumbX = 0;
	mThumbY = 0;
	mThumbWidth = mWidth;
	mThumbHeight = mHeight;
	mScrollValue = 0;
	mScrollRange = 0;
	mDoFinger = true;
	mButtonNoDraw = true;
}

ScrollbarWidget::~ScrollbarWidget() {
	
}

void ScrollbarWidget::Update() {
	Widget::Update();

	if (mScrollbarMode == ScrollbarMode::VERTICAL)
	{
		mThumbX = 0;
		mThumbWidth = mWidth;
		mThumbHeight = (mViewport.mHeight / (mViewport.mHeight + mScrollRange)) * mHeight;
		mThumbY = mScrollValue / mScrollRange * (mHeight - mThumbHeight);

		if (isThumbDown()) {
			mScrollValue = max(0, min((mWidgetManager->mLastMouseY - mY - (mThumbHeight / 2.0f)) / (mHeight - mThumbHeight) * mScrollRange, mScrollRange));
		}
	}
	else if (mScrollbarMode == ScrollbarMode::HORIZONTAL)
	{
		mThumbY = 0;
		mThumbHeight = mHeight;
		mThumbWidth = (mViewport.mWidth / (mViewport.mWidth + mScrollRange)) * mWidth;
		mThumbX = mScrollValue / mScrollRange * (mWidth - mThumbWidth);

		if (isThumbDown()) {
			mScrollValue = max(0, min((mWidgetManager->mLastMouseX + mX + (mThumbWidth / 2.0f)) / (mWidth - mThumbWidth) * mScrollRange, mScrollRange));
		}
	}
}

void ScrollbarWidget::Draw(Graphics* g) {
	if (mButtonNoDraw)
		return;

	g->SetColorizeImages(true);

	DrawThumb(g);

	if (isThumbOver()) {
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(Color::White);
		g->mColor.mAlpha = 96;
		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		DrawThumb(g);
		g->PopState();
	}

	DrawScrollBackground(g);
	
	g->SetColorizeImages(false);
}

bool ScrollbarWidget::isThumbOver() {
	return !mDisabled && mIsOver;
}

bool ScrollbarWidget::isThumbDown() {
	return !mDisabled && mIsDown;
}

void ScrollbarWidget::DrawThumb(Graphics* g) {
	int aAlpha = g->mColor.mAlpha;

	g->PushState();

	g->SetColor(mThumbColor); // Base
	g->mColor.mAlpha = aAlpha;
	g->DrawLine(mThumbX, mThumbY, mThumbX+mThumbWidth-2, mThumbY); // Top Outer Line Highlight
	g->DrawLine(mThumbX, mThumbY+1, mThumbX, mThumbY+mThumbHeight-2); // Left Outer Line Highlight
	g->FillRect(mThumbX+2, mThumbY+2, mThumbWidth-4, mThumbHeight-3); // Inner Fill Highlight

	g->SetColor(mThumbInnerHighlight); // Inner Highlight
	g->mColor.mAlpha = aAlpha;
	g->DrawLine(mThumbX+2, mThumbY+1, mThumbX + mThumbWidth-3, mThumbY+1); // Top Inner Line Inner Highlight
	g->DrawLine(mThumbX+1, mThumbY+2, mThumbX+1, mThumbY+mThumbHeight-3); // Left Inner Line Inner Highlight

	g->SetColor(mThumbInnerHighlight2); // Top Left Blend Inner Highlight
	g->mColor.mAlpha = aAlpha;
	g->FillRect(mThumbX+1, mThumbY+1, 1, 1); // Top Left Fill Shadow

	g->SetColor(mThumbInnerHighlightShadow); // Blend Inner Highlight and Shadow
	g->mColor.mAlpha = aAlpha;
	g->FillRect(mThumbWidth-2, mThumbY+1, 1, 1); // Top Right Fill Highlight and Shadow
	g->FillRect(mThumbX+1, mThumbY+mThumbHeight-2, 1, 1); // Bottom Left Fill Highlight and Shadow

	g->SetColor(mThumbInnerShadow); // Inner Shadow
	g->mColor.mAlpha = aAlpha;
	g->DrawLine(mThumbX+mThumbWidth-2, mThumbY+1, mThumbX+mThumbWidth-2, mThumbY+mThumbHeight-3); // Right Inner Shadow
	g->DrawLine(mThumbX+1, mThumbY+mThumbHeight-2, mThumbX+mThumbWidth-3, mThumbY+mThumbHeight-2); // Bottom  Inner Shadow

	g->SetColor(mThumbInnerShadow2); // Bottom Right Blend Inner Shadow 
	g->mColor.mAlpha = aAlpha;
	g->FillRect(mThumbX+mThumbWidth-2, mThumbY+mThumbHeight-2, 1, 1); // Bottom Right Inner Shadow
	
	g->SetColor(mThumbOuterShadow); // Shadows
	g->mColor.mAlpha = aAlpha;
	g->DrawLine(mThumbX+mThumbWidth-1, mThumbY, mThumbX+mThumbWidth-1, mThumbY+mThumbHeight-2); // Right Outer Line Shadow
	g->DrawLine(mThumbX, mThumbY+mThumbHeight-1, mThumbX+mThumbWidth-2, mThumbY+mThumbHeight-1); // Bottom Outer Line Shadow

	g->SetColor(mThumbOuterShadow2); // Bottom Right Blend Shadow
	g->mColor.mAlpha = aAlpha;
	g->FillRect(mThumbX+mThumbWidth-1, mThumbY+mThumbHeight-1, 1, 1); // Bottom Right Fill Shadow

	g->PopState();
}

void ScrollbarWidget::DrawScrollBackground(Graphics* g) {
	int aAlpha = g->mColor.mAlpha;
	g->PushState();
	g->SetColor(mBackgroundColor);
	g->mColor.mAlpha = aAlpha;
	if (mScrollbarMode == ScrollbarMode::VERTICAL)
	{
		g->FillRect(0, 0, mThumbWidth, mThumbY);
		g->FillRect(0, mThumbY+mThumbHeight, mThumbWidth, mHeight-mThumbY-mThumbHeight);
	}
	else if (mScrollbarMode == ScrollbarMode::HORIZONTAL)
	{
		g->FillRect(0, 0, mThumbX, mThumbHeight);
		g->FillRect(mThumbX+mThumbWidth, 0, mThumbWidth -mThumbX, mThumbHeight);
	}
	g->PopState();
}