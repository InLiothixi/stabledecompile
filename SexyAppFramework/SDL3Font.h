#ifndef __SDL3FONT_H__
#define __SDL3FONT_H__

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include "../LawnApp.h"
#include "Font.h"

namespace Sexy
{
	class SexyAppBase;

	class SDL3Font : public Font
	{
	public:
		static std::vector<SDL3Font*> gSDLFonts;

		static void RebuildFonts(float scale);

	public:
		TTF_Font* mFont;
		std::string mPathFile;
		SexyAppBase* mApp;

		bool mItalic;
		bool mBold;
		bool mUnderline;

		int mPointSize;
		float mDefaultScale = 1.0f;
		float mScaleOffset = 0.0f;

		bool mInitializedScale = false;
		float mScale = 1.0f;

		std::unordered_map<SexyChar, SDL_Texture*> mGlyphCache;
		std::unordered_map<SexyChar, int> mGlyphWidth;
		std::unordered_map<SexyChar, int> mGlyphHeight;

		void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, bool bold, bool italics, bool underline);
		void CacheGlyph(SexyChar c, const Color& color);

	public:
		SDL3Font(const std::string& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
		SDL3Font(SexyAppBase* theApp, const std::string& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
		virtual ~SDL3Font();

		virtual int StringWidth(const SexyString& theString);
		virtual void DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

		virtual SDL3Font* Duplicate();

		virtual int GetAscent();
		virtual int GetAscentPadding();
		virtual int GetDescent();
		virtual int GetHeight();
		virtual int GetLineSpacingOffset();
		virtual int GetLineSpacing();

		virtual int CharWidth(SexyChar theChar);
		virtual int CharWidthKern(SexyChar theChar, SexyChar thePrevChar);

		void		Rebuild();
		float		GetRelativeScale();
	};

}

#endif