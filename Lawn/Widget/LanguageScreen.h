#ifndef __LANGUAGESCREEN_H__
#define __LANGUAGESCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "GameButton.h"

class LawnApp;

using namespace Sexy;

class LanguageWidget : public Widget, public ButtonListener
{
private:
	enum
	{
		Langauge_Back,
		Language_English,
		Language_Filipino,
		NUM_LANGUAGES
	};
public:
	LawnApp*			mApp;
	NewLawnButton*		mBackButton;
	NewLawnButton*		mLanguageButtons[NUM_LANGUAGES-1];

public:
	LanguageWidget(LawnApp* theApp);
	virtual ~LanguageWidget();
	virtual void Draw(Graphics* g);
	virtual void Update();
	virtual void AddedToManager(WidgetManager* theManager);
	virtual void RemovedFromManager(WidgetManager* theManager);
	virtual void ButtonDepress(int theId);
};
#endif