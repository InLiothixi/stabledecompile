#ifndef __SDL3FONT_H__
#define __SDL3FONT_H__

#include <SDL3/SDL.h>
#include "../LawnApp.h"
#include "Font.h"

namespace Sexy
{
	class SexyAppBase;

	class SDL3Font : public Font
	{
	public:
		SexyAppBase*			mApp;
		bool					mDrawShadow;
		bool					mSimulateBold;

		void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);

	public:
		//SDL3Font(const std::string& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
		//SDL3Font(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
	};

}

#endif