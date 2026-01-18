#include "SDL3Font.h"

void SDL3Font::Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps)
{
	mApp = theApp;

	/*HDC aDC = ::GetDC(mApp->mHWnd);
	float scale = GetDeviceCaps(aDC, LOGPIXELSY) / 96.0f;
	int aHeight = -MulDiv(thePointSize, useDevCaps ? GetDeviceCaps(aDC, LOGPIXELSY) : 96, 72 * scale);

	mHFont = CreateFontA(aHeight, 0, 0, 0, bold ? FW_BOLD : FW_NORMAL, italics, underline,
		false, theScript, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, theFace.c_str());

	TEXTMETRIC aTextMetric;
	HFONT anOldFont = (HFONT)SelectObject(aDC, mHFont);
	GetTextMetrics(aDC, &aTextMetric);
	SelectObject(aDC, anOldFont);
	ReleaseDC(mApp->mHWnd, aDC);

	mHeight = aTextMetric.tmHeight;
	mAscent = aTextMetric.tmAscent;*/

	mDrawShadow = false;
	mSimulateBold = false;
}