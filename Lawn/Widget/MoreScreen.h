#ifndef __MORESCREEN_H__
#define __MORESCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "GameButton.h"

class LawnApp;

using namespace Sexy;

class MoreWidget : public Widget, public ButtonListener {
private:
	enum
	{
		More_Back,
		More_Quickplay
	};
public:
	LawnApp* mApp;
	NewLawnButton*				mBackButton;
	NewLawnButton*				mQuickplayButton;

	MoreWidget(LawnApp* theApp);
	virtual ~MoreWidget();

	virtual void                Update();
	virtual void                Draw(Graphics* g);
	virtual void                MouseDown(int x, int y, int theClickCount);
	virtual void                AddedToManager(WidgetManager* theWidgetManager);
	virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void                OrderInManagerChanged();
	virtual void                ButtonMouseEnter(int theId);
	virtual void                ButtonPress(int theId, int theClickCount);
	virtual void                ButtonDepress(int theId);
	void						DisableButtons(bool isDisabled);
};

#endif