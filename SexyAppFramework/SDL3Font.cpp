#include "SDL3Font.h"
#include "../LawnApp.h"

using namespace Sexy;

std::vector<SDL3Font*> SDL3Font::gSDLFonts;

void SDL3Font::RebuildFonts(float scale)
{
	float snappedScale = floor(scale * 4.0f) / 4.0f;

	for (SDL3Font* font : gSDLFonts) {
		if (font->mScale == snappedScale) continue;

		font->mScale = snappedScale;
		font->mScaleOffset = scale - snappedScale;
		font->Rebuild();
	}
}

void SDL3Font::Rebuild()
{
	for (auto& pair : mGlyphCache)
	{
		SDL_DestroyTexture(pair.second);
	}
	mGlyphCache.clear();
	mGlyphWidth.clear();
	mGlyphHeight.clear();
	if (mFont)
	{
		TTF_CloseFont(mFont);
		mFont = nullptr;
	}
	Init(mApp, mPathFile, mPointSize, mBold, mItalic, mUnderline);
}

void SDL3Font::Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, bool bold, bool italics, bool underline)
{
	if (mInitializedScale) {
		mInitializedScale = true;
		float scale = 1.0f;
		int pw, ph;
		SDL_GetWindowSizeInPixels(LawnApp::mSDLWindow, &pw, &ph);
		float gScale = max(static_cast<float>(pw) / 800.0f, static_cast<float>(ph) / 600.0f);
		if (pw >= 800 || ph >= 600) scale = max(floor(gScale * 4.0f) / 4.0f, 1.0f);
		mScale = scale;
		mScaleOffset = gScale - scale;
	}

	mApp = theApp;
	mPointSize = thePointSize;
	mPathFile = theFace;
	mFont = TTF_OpenFont(mPathFile.c_str(), int(floor(thePointSize * (mScale * mDefaultScale))));

	int style = TTF_STYLE_NORMAL;
	if (bold) style |= TTF_STYLE_BOLD;
	if (italics) style |= TTF_STYLE_ITALIC;
	if (underline) style |= TTF_STYLE_UNDERLINE;
	TTF_SetFontStyle(mFont, style);

	TTF_SetFontHinting(mFont, TTF_HINTING_LIGHT_SUBPIXEL);
	TTF_SetFontKerning(mFont, true);

	mBold = bold;
	mItalic = italics;
	mUnderline = underline;

	Color defaultColor(255, 255, 255, 255);
	for (char c = 32; c < 127; ++c)
		CacheGlyph(c, defaultColor);
}

void SDL3Font::CacheGlyph(SexyChar c, const Color& color)
{
	if (!mFont || mGlyphCache.find(c) != mGlyphCache.end()) return;

	SDL_Color sdlColor = { Uint8(color.mRed), Uint8(color.mGreen), Uint8(color.mBlue), Uint8(color.mAlpha) };
	SDL_Surface* surface = TTF_RenderGlyph_Blended(mFont, c, sdlColor);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(LawnApp::mSDLRenderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	mGlyphCache[c] = texture;
	mGlyphWidth[c] = surface->w;
	mGlyphHeight[c] = surface->h;

	SDL_DestroySurface(surface);
}

SDL3Font::SDL3Font(const std::string& theFace, int thePointSize, bool bold, bool italics, bool underline)
{
	Init(gSexyAppBase, theFace, thePointSize, bold, italics, underline);
	auto it = std::find(gSDLFonts.begin(), gSDLFonts.end(), this);
	if (it == gSDLFonts.end())
		gSDLFonts.push_back(this);
}

SDL3Font::SDL3Font(SexyAppBase* theApp, const std::string& theFace, int thePointSize, bool bold, bool italics, bool underline)
{
	Init(theApp, theFace, thePointSize, bold, italics, underline);
	auto it = std::find(gSDLFonts.begin(), gSDLFonts.end(), this);
	if (it == gSDLFonts.end())
		gSDLFonts.push_back(this);
}

SDL3Font::~SDL3Font()
{
	for (auto& pair : mGlyphCache)
		SDL_DestroyTexture(pair.second);
	mGlyphCache.clear();

	auto it = std::find(gSDLFonts.begin(), gSDLFonts.end(), this);
	if (it != gSDLFonts.end())
		gSDLFonts.erase(it);

	if (mFont)
	{
		TTF_CloseFont(mFont);
		mFont = nullptr;
	}
}

float SDL3Font::GetRelativeScale()
{
	return (mScale - mScaleOffset) * mDefaultScale;
}

int SDL3Font::StringWidth(const SexyString& theString)
{
	int w = 0;
	for (auto c : theString)
	{
		if (mGlyphWidth.find(c) != mGlyphWidth.end())
			w += mGlyphWidth[c];
		else
			w += TTF_GetGlyphImageForIndex(mFont, c, NULL) ? TTF_GetGlyphImageForIndex(mFont, c, NULL)->w : 0;
	}
	return w / GetRelativeScale();
}

void SDL3Font::DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect)
{
	if (!mFont) return;

	int x = theX;

	if (theClipRect.mWidth > 0 && theClipRect.mHeight > 0)
	{
		SDL_Rect clip = { theClipRect.mX, theClipRect.mY, theClipRect.mWidth, theClipRect.mHeight };
		SDL_SetRenderClipRect(LawnApp::mSDLRenderer, &clip);
	}

	int prevChar = 0;
	for (auto c : theString)
	{
		if (prevChar)
		{
			int kern = 0;
			TTF_GetGlyphKerning(mFont, prevChar, c, &kern);
			x += kern / GetRelativeScale();
		}

		if (mGlyphCache.find(c) == mGlyphCache.end())
			CacheGlyph(c, theColor);

		SDL_Texture* tex = mGlyphCache[c];
		if (tex)
		{
			SDL_FRect dst = { float(x), float(theY - GetAscent()), float(mGlyphWidth[c]) / GetRelativeScale(), float(mGlyphHeight[c]) / GetRelativeScale()};
			SDL_SetTextureColorMod(tex, theColor.mRed, theColor.mGreen, theColor.mBlue);
			SDL_SetTextureAlphaMod(tex, theColor.mAlpha);
			SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
			SDL_RenderTexture(LawnApp::mSDLRenderer, tex, nullptr, &dst);
			x += mGlyphWidth[c] / GetRelativeScale();
		}

		prevChar = c;
	}

	SDL_SetRenderClipRect(LawnApp::mSDLRenderer, nullptr);
}

SDL3Font* SDL3Font::Duplicate()
{
	SDL3Font* newFont = new SDL3Font(mApp, mPathFile, mPointSize, mBold, mItalic, mUnderline);
	auto it = std::find(gSDLFonts.begin(), gSDLFonts.end(), newFont);
	if (it == gSDLFonts.end())
		gSDLFonts.push_back(newFont);
	return newFont;
}

int	SDL3Font::GetAscent() { return TTF_GetFontAscent(mFont) / GetRelativeScale(); }
int	SDL3Font::GetAscentPadding() { return 0; }
int	SDL3Font::GetDescent() { return TTF_GetFontDescent(mFont) / GetRelativeScale(); }
int	SDL3Font::GetHeight() { return TTF_GetFontHeight(mFont) / GetRelativeScale(); }
int SDL3Font::GetLineSpacingOffset() { return GetHeight() + GetLineSpacing(); }
int SDL3Font::GetLineSpacing() { return TTF_GetFontLineSkip(mFont) / GetRelativeScale(); }
int SDL3Font::CharWidth(SexyChar theChar) { return mGlyphWidth[theChar] / GetRelativeScale(); }
int SDL3Font::CharWidthKern(SexyChar theChar, SexyChar thePrevChar) { int kern; TTF_GetGlyphKerning(mFont, thePrevChar, theChar, &kern); return kern / GetRelativeScale(); }
