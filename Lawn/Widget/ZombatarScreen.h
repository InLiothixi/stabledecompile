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
		ZombatarScreen_Back,
		ZombatarScreen_Skin,
		ZombatarScreen_Hair,
		ZombatarScreen_FacialHair,
		ZombatarScreen_Tidbits,
		ZombatarScreen_EyeWear,
		ZombatarScreen_Clothes,
		ZombatarScreen_Acessory,
		ZombatarScreen_Hats,
		ZombatarScreen_Backdrops
	};

	enum ZombatarPage {
		ZombatarPage_Skin,
		ZombatarPage_Hair,
		ZombatarPage_FacialHair,
		ZombatarPage_Tidbits,
		ZombatarPage_EyeWear,
		ZombatarPage_Clothes,
		ZombatarPage_Acessory,
		ZombatarPage_Hats,
		ZombatarPage_Backdrops,
		MAX_ZOMBATAR_PAGES
	};
public:
	LawnApp* mApp; 
	NewLawnButton* mBackButton;
	NewLawnButton* mSkinButton;
	NewLawnButton* mHairButton;
	NewLawnButton* mFacialHairButton;
	NewLawnButton* mTidbitsButton;
	NewLawnButton* mEyeWearButton;
	NewLawnButton* mClothesButton;
	NewLawnButton* mAccessoryButton;
	NewLawnButton* mHatsButton;
	NewLawnButton* mBackdropsButton;
	ZombatarPage mPage;

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
	void						ResetZombatar();
	void						SetupZombie();
	void						SetPage(ZombatarPage thePage);
};
#endif