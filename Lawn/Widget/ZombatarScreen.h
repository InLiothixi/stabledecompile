#ifndef __ZOMBATARSCREEN_H__
#define __ZOMBATARSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "../Zombie.h"
#include "GameButton.h"

#define NUM_SKIN_COLOR_PALLETES 12
#define NUM_COLOR_PALLETES 17

class LawnApp;

using namespace Sexy;

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

class ZombatarDefinition {
public:
	ZombatarItem mZombatarItem;
	Image** mOutlineImage;
	Image** mImage;
	ZombatarPage mPage;
	int mColumn;
	int mRow;
	Color* mColorGroup;
};
extern ZombatarDefinition gZombatarDefinitions[NUM_ZOMBATAR_ITEMS];
ZombatarDefinition& GetZombatarDefinition(ZombatarItem theItem);

class ZombatarWidget : public Widget, public ButtonListener 
{
private:
	enum {
		ZombatarScreen_Back,
		ZombatarScreen_Finish,
		ZombatarScreen_Skin,
		ZombatarScreen_Hair,
		ZombatarScreen_FacialHair,
		ZombatarScreen_Tidbits,
		ZombatarScreen_EyeWear,
		ZombatarScreen_Clothes,
		ZombatarScreen_Acessory,
		ZombatarScreen_Hats,
		ZombatarScreen_Backdrops,
		ZombatarScreen_ClearPick,
		ZombatarScreen_ClearPallete,
		ZombatarScreen_Palletes,
		ZombatarScreen_Items = ZombatarScreen_Palletes + NUM_COLOR_PALLETES + 1,
	};

public:

	LawnApp* mApp; 
	NewLawnButton* mBackButton;
	NewLawnButton* mFinishButton;
	NewLawnButton* mSkinButton;
	NewLawnButton* mHairButton;
	NewLawnButton* mFacialHairButton;
	NewLawnButton* mTidbitsButton;
	NewLawnButton* mEyeWearButton;
	NewLawnButton* mClothesButton;
	NewLawnButton* mAccessoryButton;
	NewLawnButton* mHatsButton;
	NewLawnButton* mBackdropsButton;
	NewLawnButton* mClearPickButton;
	NewLawnButton* mClearPalleteButton;
	ZombatarPage mPage;
	int mCurSkinPallete;
	int mCurHair;
	int mCurHairPallete;
	int mCurBackground;
	int mCurBackgroundPallete;
	NewLawnButton* mZombatarItems[NUM_ZOMBATAR_ITEMS];
	NewLawnButton* mColorPalletes[NUM_COLOR_PALLETES];

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
	void						SetZombatarRef(int* theTarget, int theValue);
	void						DrawColorPalletes(Graphics* g);
	void						DrawZombiePortrait(Graphics* g);
	void						DrawZombieAvatar(Graphics* g);
	void						DrawZombatarItems(Graphics* g);
	void						DrawZombatarItem(Graphics* g, NewLawnButton* button, ZombatarItem theItem, int* theTargetItem, ZombatarDefinition* aDef);
	void						DrawClearItem(Graphics* g, NewLawnButton* button, int* theTargetItem);
	void						UpdatePalletes();
	void						UpdateItems();
	void						UpdateZombieAvatar();
	void						GetOutlineOffset(ZombatarItem theItem, float* offsetX, float* offsetY);
	void						GetZombatarItemOffset(ZombatarItem theItem, float* offsetX, float* offsetY);
	void						GetZombatarItemScale(ZombatarItem theItem, float* scaleX, float* scaleY);
	void						GetZombatarPortraitOffset(ZombatarItem theItem, float* offsetX, float* offsetY);
	void						DrawClearPallete(Graphics* g, NewLawnButton* button, int* theTargetPallete);
};

extern Color gZombatarSkinPalletes[NUM_SKIN_COLOR_PALLETES];
extern Color gZombatarDimPalletes[NUM_COLOR_PALLETES];
extern Color gZombatarBrightPalletes[NUM_COLOR_PALLETES];
#endif