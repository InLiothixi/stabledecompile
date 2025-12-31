#ifndef __ZOMBATARSCREEN_H__
#define __ZOMBATARSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "../Zombie.h"
#include "GameButton.h"

enum ZombatarNavigation
{
	SKINS = 0,
	HAIR = 1,
	FACIAL_HAIR = 2,
	TIDBITS = 3,
	EYEWEAR = 4,
	CLOTHES = 5,
	ACCESSORIES = 6,
	HATS = 7,
	BACKDROPS = 8,
	MAX_NAV = 9
};

class LawnApp;

using namespace Sexy;

class ZombatarWidget : public Widget, public ButtonListener 
{
private:
	enum {
		ZombatarScreen_Back
	};
public:
	LawnApp* mApp; 
	NewLawnButton* mBackButton;
	//int							mNavigationID;
	//NewLawnButton*				mFinishButton;
	Zombie* mZombie;

public:
	ZombatarWidget(LawnApp* theApp);
	virtual ~ZombatarWidget();
	virtual void                Update();
	virtual void                Draw(Graphics* g);
	virtual void                AddedToManager(WidgetManager* theWidgetManager);
	virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void                OrderInManagerChanged();
	virtual void                ButtonMouseEnter(int theId);
	virtual void                ButtonDepress(int theId);
	virtual void                ButtonPress(int theId, int theClickCount);
};
#endif