#include "../../GameConstants.h"
#ifdef _HAS_ZOMBATAR
#include "ZombatarScreen.h"
#include "../../Resources.h"
#include "../../LawnApp.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "GameSelector.h"
#include "GameButton.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../SexyAppFramework/MemoryImage.h"
#include "../../GameConstants.h"
#include "../../Sexy.TodLib/Reanimator.h"
#include "../Zombie.h"
#include "../../Sexy.TodLib/Attachment.h"
#include "../../SexyAppFramework/Font.h"
#include "../../Sexy.TodLib/TodStringFile.h"

ZombatarDefinition gZombatarDefinitions[] = {
	{ZombatarItem::ZOMBATAR_BACKGROUND_CRAZYDAVE,	nullptr,						&Sexy::IMAGE_ZOMBATAR_BACKGROUND_CRAZYDAVE,	ZombatarCategory::ZombatarPage_Backdrops, 0, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_MENU,	    nullptr,						&Sexy::IMAGE_ZOMBATAR_BACKGROUND_MENU,		ZombatarCategory::ZombatarPage_Backdrops, 1, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_MENU_DOS,    nullptr,						&Sexy::IMAGE_ZOMBATAR_BACKGROUND_MENU_DOS,  ZombatarCategory::ZombatarPage_Backdrops, 2, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_ROOF,	    nullptr,						&Sexy::IMAGE_ZOMBATAR_BACKGROUND_ROOF,		ZombatarCategory::ZombatarPage_Backdrops, 3, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_BLANK,		nullptr,						&Sexy::IMAGE_ZOMBATAR_BACKGROUND_BLANK,		ZombatarCategory::ZombatarPage_Backdrops, 4, 0, gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_1,					&Sexy::IMAGE_ZOMBATAR_HAIR_1,	&Sexy::IMAGE_ZOMBATAR_HAIR_1_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  0, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_2,					&Sexy::IMAGE_ZOMBATAR_HAIR_2,	&Sexy::IMAGE_ZOMBATAR_HAIR_2_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  1, 0, gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_3,					&Sexy::IMAGE_ZOMBATAR_HAIR_3,	nullptr,									ZombatarCategory::ZombatarPage_Hairs,	  2, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_HAIR_4,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_4,				ZombatarCategory::ZombatarPage_Hairs,	  3, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_5,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_5,				ZombatarCategory::ZombatarPage_Hairs,	  4, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_6,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_6,				ZombatarCategory::ZombatarPage_Hairs,	  5, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_7,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_7,				ZombatarCategory::ZombatarPage_Hairs,	  0, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_8,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_8,				ZombatarCategory::ZombatarPage_Hairs,	  1, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_9,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_9,				ZombatarCategory::ZombatarPage_Hairs,	  2, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_10,				nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_10,				ZombatarCategory::ZombatarPage_Hairs,	  3, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_11,				&Sexy::IMAGE_ZOMBATAR_HAIR_11,	&Sexy::IMAGE_ZOMBATAR_HAIR_11_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  4, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_12,				&Sexy::IMAGE_ZOMBATAR_HAIR_12,	&Sexy::IMAGE_ZOMBATAR_HAIR_12_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  5, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_13,				&Sexy::IMAGE_ZOMBATAR_HAIR_13,	&Sexy::IMAGE_ZOMBATAR_HAIR_13_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  0, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_14,				&Sexy::IMAGE_ZOMBATAR_HAIR_14,	&Sexy::IMAGE_ZOMBATAR_HAIR_14_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  1, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_15,				&Sexy::IMAGE_ZOMBATAR_HAIR_15,	&Sexy::IMAGE_ZOMBATAR_HAIR_15_MASK,			ZombatarCategory::ZombatarPage_Hairs,	  2, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_16,				nullptr,						&Sexy::IMAGE_ZOMBATAR_HAIR_16,				ZombatarCategory::ZombatarPage_Hairs,	  3, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_CLOTHE_1,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_1,			ZombatarCategory::ZombatarPage_Clothes,	  0, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_2,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_2,			ZombatarCategory::ZombatarPage_Clothes,	  1, 0, nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_3,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_3,			ZombatarCategory::ZombatarPage_Clothes,	  2, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_4,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_4,			ZombatarCategory::ZombatarPage_Clothes,	  3, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_5,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_5,			ZombatarCategory::ZombatarPage_Clothes,	  4, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_6,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_6,			ZombatarCategory::ZombatarPage_Clothes,	  5, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_7,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_7,			ZombatarCategory::ZombatarPage_Clothes,	  0, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_8,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_8,			ZombatarCategory::ZombatarPage_Clothes,	  1, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_9,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_9,			ZombatarCategory::ZombatarPage_Clothes,	  2, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_10,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_10,			ZombatarCategory::ZombatarPage_Clothes,	  3, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_11,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_11,			ZombatarCategory::ZombatarPage_Clothes,	  4, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_CLOTHE_12,				nullptr,						&Sexy::IMAGE_ZOMBATAR_CLOTHES_12,			ZombatarCategory::ZombatarPage_Clothes,	  5, 1,	nullptr},
	{ZombatarItem::ZOMBATAR_HAT_1,					&Sexy::IMAGE_ZOMBATAR_HATS_1,	&Sexy::IMAGE_ZOMBATAR_HATS_1_MASK,			ZombatarCategory::ZombatarPage_Hats,	  0, 0,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_2,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_2,				ZombatarCategory::ZombatarPage_Hats,	  1, 0, gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_3,					&Sexy::IMAGE_ZOMBATAR_HATS_3,	&Sexy::IMAGE_ZOMBATAR_HATS_3_MASK,			ZombatarCategory::ZombatarPage_Hats,	  2, 0,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_4,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_4,				ZombatarCategory::ZombatarPage_Hats,	  3, 0,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_5,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_5,				ZombatarCategory::ZombatarPage_Hats,	  4, 0,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_6,					&Sexy::IMAGE_ZOMBATAR_HATS_6,	&Sexy::IMAGE_ZOMBATAR_HATS_6_MASK,			ZombatarCategory::ZombatarPage_Hats,	  5, 0,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_7,					&Sexy::IMAGE_ZOMBATAR_HATS_7,	&Sexy::IMAGE_ZOMBATAR_HATS_7_MASK,			ZombatarCategory::ZombatarPage_Hats,	  0, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_8,					&Sexy::IMAGE_ZOMBATAR_HATS_8,	&Sexy::IMAGE_ZOMBATAR_HATS_8_MASK,			ZombatarCategory::ZombatarPage_Hats,	  1, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_9,					&Sexy::IMAGE_ZOMBATAR_HATS_9,	&Sexy::IMAGE_ZOMBATAR_HATS_9_MASK,			ZombatarCategory::ZombatarPage_Hats,	  2, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_10,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_10,				ZombatarCategory::ZombatarPage_Hats,	  3, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_11,					&Sexy::IMAGE_ZOMBATAR_HATS_11,	&Sexy::IMAGE_ZOMBATAR_HATS_11_MASK,			ZombatarCategory::ZombatarPage_Hats,	  4, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_12,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_12,				ZombatarCategory::ZombatarPage_Hats,	  5, 1,	gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAT_13,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_13,				ZombatarCategory::ZombatarPage_Hats,	  0, 2,	nullptr},
	{ZombatarItem::ZOMBATAR_HAT_14,					nullptr,						&Sexy::IMAGE_ZOMBATAR_HATS_14,				ZombatarCategory::ZombatarPage_Hats,	  1, 2,	gZombatarBrightPalletes},

};

Color gZombatarSkinPalletes[] = {
	Color(134, 147, 122),
	Color(79, 135, 94),
	Color(127, 135, 94),
	Color(120, 130, 50),
	Color(156, 163, 105),
	Color(96, 151, 11),
	Color(147, 184, 77),
	Color(82, 143, 54),
	Color(121, 168, 99),
	Color(65, 156, 74),
	Color(107, 178, 114),
	Color(104, 121, 90)
};

Color gZombatarDimPalletes[] = {
	Color(151, 33, 33),
	Color(199, 53, 53),
	Color(220, 112, 47),
	Color(251, 251, 172),
	Color(240, 210, 87),
	Color(165, 126, 65),
	Color(106, 72, 32),
	Color(72, 35, 5),
	Color(50, 56, 61),
	Color(0, 0, 10),
	Color(197, 239, 239),
	Color(63, 109, 242),
	Color(13, 202, 151),
	Color(158, 183, 19),
	Color(30, 210, 64),
	Color(225, 65, 230),
	Color(128, 47, 204)
};

Color gZombatarBrightPalletes[] = {
	Color(238, 19, 24),
	Color(247, 89, 215),
	Color(239, 198, 253),
	Color(160, 56, 241),
	Color(86, 74, 241),
	Color(74, 160, 241),
	Color(199, 244, 251),
	Color(49, 238, 237),
	Color(16, 194, 66),
	Color(112, 192, 33),
	Color(16, 145, 52),
	Color(248, 247, 41),
	Color(227, 180, 20),
	Color(241, 115, 25),
	Color(248, 247, 175),
	Color(103, 85, 54),
	Color(159, 17, 20)
};

// GOTY @Inliothixi
ZombatarWidget::ZombatarWidget(LawnApp* theApp) {
	TodLoadResources("DelayLoad_Zombatar");
	mApp = theApp;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;
	TodLoadResources("DelayLoad_Almanac");

	mBackButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Back,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_BLANK,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT,
		Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT
	);
	mBackButton->Resize(278, 528.5f, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_HIGHLIGHT->mHeight);
	mBackButton->mClip = false;
	mBackButton->mTranslateX = 0;
	mBackButton->mTranslateY = 0;

	mFinishButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Finish,
		this,
		"",
		nullptr,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT,
		Sexy::IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT
	);
	mFinishButton->Resize(445, 472, IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT->mWidth, IMAGE_ZOMBATAR_FINISHED_BUTTON_HIGHLIGHT->mHeight);
	mFinishButton->mClip = false;
	mFinishButton->mTranslateX = 0;
	mFinishButton->mTranslateY = 0;

	mSkinButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Skin,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_SKIN_BUTTON,
		Sexy::IMAGE_ZOMBATAR_SKIN_BUTTON,
		Sexy::IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT
	);
	mSkinButton->Resize(58, 128, Sexy::IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT->mHeight);
	mSkinButton->mClip = false;
	mSkinButton->mTranslateX = 0;
	mSkinButton->mTranslateY = 0;

	mHairButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Hair,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_HAIR_BUTTON,
		Sexy::IMAGE_ZOMBATAR_HAIR_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT
	);
	mHairButton->Resize(58, 164, Sexy::IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT->mHeight);
	mHairButton->mClip = false;
	mHairButton->mTranslateX = 0;
	mHairButton->mTranslateY = 0;

	mFacialHairButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_FacialHair,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON,
		Sexy::IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT
	);
	mFacialHairButton->Resize(58, 200, Sexy::IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT->mHeight);
	mFacialHairButton->mClip = false;
	mFacialHairButton->mTranslateX = 0;
	mFacialHairButton->mTranslateY = 0;

	mTidbitsButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Tidbits,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_TIDBITS_BUTTON,
		Sexy::IMAGE_ZOMBATAR_TIDBITS_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT
	);
	mTidbitsButton->Resize(58, 236, Sexy::IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT->mHeight);
	mTidbitsButton->mClip = false;
	mTidbitsButton->mTranslateX = 0;
	mTidbitsButton->mTranslateY = 0;

	mEyeWearButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_EyeWear,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_EYEWEAR_BUTTON,
		Sexy::IMAGE_ZOMBATAR_EYEWEAR_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT
	);
	mEyeWearButton->Resize(58, 272, Sexy::IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT->mHeight);
	mEyeWearButton->mClip = false;
	mEyeWearButton->mTranslateX = 0;
	mEyeWearButton->mTranslateY = 0;

	mClothesButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Clothes,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_CLOTHES_BUTTON,
		Sexy::IMAGE_ZOMBATAR_CLOTHES_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT
	);
	mClothesButton->Resize(58, 308, Sexy::IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT->mHeight);
	mClothesButton->mClip = false;
	mClothesButton->mTranslateX = 0;
	mClothesButton->mTranslateY = 0;

	mAccessoryButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Acessory,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_ACCESSORY_BUTTON,
		Sexy::IMAGE_ZOMBATAR_ACCESSORY_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT
	);
	mAccessoryButton->Resize(58, 344, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT->mHeight);
	mAccessoryButton->mClip = false;
	mAccessoryButton->mTranslateX = 0;
	mAccessoryButton->mTranslateY = 0;

	mHatsButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Hats,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_HATS_BUTTON,
		Sexy::IMAGE_ZOMBATAR_HATS_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT
	);
	mHatsButton->Resize(58, 380, Sexy::IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT->mHeight);
	mHatsButton->mClip = false;
	mHatsButton->mTranslateX = 0;
	mHatsButton->mTranslateY = 0;

	mBackdropsButton = MakeNewButton(
		ZombatarWidget::ZombatarScreen_Backdrops,
		this,
		_S(""),
		nullptr,
		Sexy::IMAGE_ZOMBATAR_BACKDROPS_BUTTON,
		Sexy::IMAGE_ZOMBATAR_BACKDROPS_BUTTON_OVER,
		Sexy::IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT
	);
	mBackdropsButton->Resize(58, 416, Sexy::IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT->mWidth, Sexy::IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT->mHeight);
	mBackdropsButton->mClip = false;
	mBackdropsButton->mTranslateX = 0;
	mBackdropsButton->mTranslateY = 0;

	for (int i = 0; i < (int)ZombatarItem::NUM_ZOMBATAR_ITEMS; i++) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);

		NewLawnButton* aZombatarItem = MakeNewButton(
			ZombatarWidget::ZombatarScreen_Items + i,
			this,
			_S(""),
			nullptr,
			Sexy::IMAGE_BLANK,
			Sexy::IMAGE_BLANK,
			Sexy::IMAGE_BLANK
		);
		aZombatarItem->Resize(166 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth - 4) * aDef.mColumn, 138 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight - 4) * aDef.mRow, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
		aZombatarItem->mClip = false;
		aZombatarItem->mTranslateX = 0;
		aZombatarItem->mTranslateY = 0;
		mZombatarItems[i] = aZombatarItem;
	}

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 2; y++) {
			NewLawnButton* mColorPallete = MakeNewButton(
				ZombatarWidget::ZombatarScreen_Palletes + x + y * 9,
				this,
				_S(""),
				nullptr,
				Sexy::IMAGE_BLANK,
				Sexy::IMAGE_BLANK,
				Sexy::IMAGE_BLANK
			);
			mColorPallete->Resize(238 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth) * x, 367 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight) * y, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
			mColorPallete->mClip = false;
			mColorPallete->mTranslateX = 0;
			mColorPallete->mTranslateY = 0;
			mColorPalletes[x + y * 9] = mColorPallete;
		}
	}

	mClearPickButton = MakeNewButton(ZombatarWidget::ZombatarScreen_ClearPick, this, _S(""), nullptr, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mClearPickButton->Resize(0, 0, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
	mClearPickButton->mClip = false;
	mClearPickButton->mTranslateX = 0;
	mClearPickButton->mTranslateY = 0;

	mClearPalleteButton = MakeNewButton(ZombatarWidget::ZombatarScreen_ClearPallete, this, _S(""), nullptr, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mClearPalleteButton->Resize(0, 0, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
	mClearPalleteButton->mClip = false;
	mClearPalleteButton->mTranslateX = 0;
	mClearPalleteButton->mTranslateY = 0;

	CreateZombatarClothes();
	mZombie = nullptr;
	ResetZombatar();
}

void ZombatarWidget::SetCategory(ZombatarCategory theCategory) {
	mCurCategory = theCategory;

	UpdateItems();
	UpdatePalletes();

	mSkinButton->mButtonImage = theCategory == ZombatarPage_Skin ? IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_SKIN_BUTTON;
	mSkinButton->mOverImage = theCategory == ZombatarPage_Skin ? IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_SKIN_BUTTON;
	mHairButton->mButtonImage = theCategory == ZombatarPage_Hairs ? IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HAIR_BUTTON;
	mHairButton->mOverImage = theCategory == ZombatarPage_Hairs ? IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HAIR_BUTTON_OVER;
	mFacialHairButton->mButtonImage = theCategory == ZombatarPage_FacialHair ? IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON;
	mFacialHairButton->mOverImage = theCategory == ZombatarPage_FacialHair ? IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_OVER;
	mTidbitsButton->mButtonImage = theCategory == ZombatarPage_Tidbits ? IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_TIDBITS_BUTTON;
	mTidbitsButton->mOverImage = theCategory == ZombatarPage_Tidbits ? IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_TIDBITS_BUTTON_OVER;
	mEyeWearButton->mButtonImage = theCategory == ZombatarPage_EyeWear ? IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_EYEWEAR_BUTTON;
	mEyeWearButton->mOverImage = theCategory == ZombatarPage_EyeWear ? IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_EYEWEAR_BUTTON_OVER;
	mClothesButton->mButtonImage = theCategory == ZombatarPage_Clothes ? IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_CLOTHES_BUTTON;
	mClothesButton->mOverImage = theCategory == ZombatarPage_Clothes ? IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_CLOTHES_BUTTON_OVER;
	mAccessoryButton->mButtonImage = theCategory == ZombatarPage_Acessory ? IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BUTTON;
	mAccessoryButton->mOverImage = theCategory == ZombatarPage_Acessory ? IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BUTTON_OVER;
	mHatsButton->mButtonImage = theCategory == ZombatarPage_Hats ? IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HATS_BUTTON;
	mHatsButton->mOverImage = theCategory == ZombatarPage_Hats ? IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HATS_BUTTON_OVER;
	mBackdropsButton->mButtonImage = theCategory == ZombatarPage_Backdrops ? IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_BACKDROPS_BUTTON;
	mBackdropsButton->mOverImage = theCategory == ZombatarPage_Backdrops ? IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_BACKDROPS_BUTTON_OVER;

	mClearPickButton->SetDisabled(true);
	mClearPalleteButton->SetDisabled(true);

	if (theCategory == ZombatarPage_Hairs) {
		mClearPickButton->SetDisabled(false);
		mClearPickButton->Resize(166 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth - 4) * 4, 138 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight - 4) * 2, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
	} else if (theCategory == ZombatarPage_Clothes) {
		mClearPickButton->SetDisabled(false);
		mClearPickButton->Resize(166, 138 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight - 4) * 2, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
	} else if (theCategory == ZombatarPage_Hats) {
		mClearPickButton->SetDisabled(false);
		mClearPickButton->Resize(166 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth - 4) * 2, 138 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight - 4) * 2, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
	}

	if (theCategory == ZombatarCategory::ZombatarPage_Skin) {
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 2; y++) {
				NewLawnButton* mColorPallete = mColorPalletes[x + y * 6];
				mColorPallete->Resize(274 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth) * x, 362 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight) * y, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
			}
		}
	}
	else {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 2; y++) {
				if (x + y * 9 == 17) break; // we don't have the clear in the array
				NewLawnButton* mColorPallete = mColorPalletes[x + y * 9];
				mColorPallete->Resize(238 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth) * x, 367 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight) * y, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
			}
		}

		mClearPalleteButton->SetDisabled(false);
		mClearPalleteButton->Resize(238 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth) * 8, 367 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight), Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
	}
}

void ZombatarWidget::SetZombatarRef(int* theTarget, int theValue) {
	*theTarget = theValue;
}

void ZombatarWidget::ResetZombatar() {
	SetCategory(ZombatarCategory::ZombatarPage_Skin);
	if (mZombie)
	{
		mZombie->DieNoLoot();
		delete mZombie;
		mZombie = nullptr;
	}
	mCurSkinPallete = 0;
	mCurBackground = ZombatarItem::ZOMBATAR_BACKGROUND_BLANK;
	mCurBackgroundPallete = -1;
	mCurHair = -1;
	mCurHairPallete = -1;
	mCurClothe = -1;
	mCurHat = -1;
	mCurHatPallete = -1;
	SetupZombie();
	UpdateZombieAvatar();
}

void ZombatarWidget::SetupZombie() {
	if (!mZombie)
	{
		mZombie = new Zombie();
		mZombie->mBoard = nullptr;
		mZombie->ZombieInitialize(0, ZombieType::ZOMBIE_FLAG, false, nullptr, Zombie::ZOMBIE_WAVE_UI);
		float aRanimRate = RandRangeFloat(12.0f, 24.0f);
		mZombie->mX = mZombie->mPosX = 641;
		mZombie->mY = mZombie->mPosY = 351;

		Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mZombie->mBodyReanimID);
		aBodyReanim->GetTrackInstanceByName("anim_head1")->mImageOverride = Sexy::IMAGE_BLANK;
		aBodyReanim->GetTrackInstanceByName("anim_head2")->mImageOverride = Sexy::IMAGE_BLANK;
		aBodyReanim->GetTrackInstanceByName("anim_hair")->mRenderGroup = RENDER_GROUP_HIDDEN;

		{
			Reanimation* aZombatar = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZOMBATAR);
			aZombatar->PlayReanim("anim_head1", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
			for (int i = 0; i < aZombatar->mDefinition->mTracks.count; i++)
			{
				aZombatar->mTrackInstances[i].mRenderGroup = RENDER_GROUP_HIDDEN;
			}
			aZombatar->GetTrackInstanceByName("anim_head1")->mRenderGroup = RENDER_GROUP_NORMAL;
			aZombatar->GetTrackInstanceByName("anim_head2")->mRenderGroup = RENDER_GROUP_NORMAL;
			ReanimatorTrackInstance* aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
			AttachEffect* aAttachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatar, 0, 0);
			aBodyReanim->mFrameBasePose = 0;
			TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -21.25f, 0.0f, 0.2f, 1.0f, 1.0f);
			//TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -13.0f, -11.0f, 0.0f, 1.0f, 1.0f);
			mZombie->mZombatarHairID = mApp->ReanimationGetID(aZombatar);
		}

		{
			Reanimation* aZombatarOutline = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZOMBATAR);
			aZombatarOutline->PlayReanim("anim_head1", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
			for (int i = 0; i < aZombatarOutline->mDefinition->mTracks.count; i++)
			{
				aZombatarOutline->mTrackInstances[i].mRenderGroup = RENDER_GROUP_HIDDEN;
			}
			ReanimatorTrackInstance* aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
			AttachEffect* aAttachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatarOutline, 0, 0);
			aBodyReanim->mFrameBasePose = 0;
			TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -21.25f, 0.0f, 0.2f, 1.0f, 1.0f);
			//TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -13.0f, -11.0f, 0.0f, 1.0f, 1.0f);
			mZombie->mZombatarHairLineID = mApp->ReanimationGetID(aZombatarOutline);
		}

		{
			Reanimation* aZombatar = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZOMBATAR);
			aZombatar->PlayReanim("anim_head1", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
			for (int i = 0; i < aZombatar->mDefinition->mTracks.count; i++)
			{
				aZombatar->mTrackInstances[i].mRenderGroup = RENDER_GROUP_HIDDEN;
			}
			ReanimatorTrackInstance* aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
			AttachEffect* aAttachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatar, 0, 0);
			aBodyReanim->mFrameBasePose = 0;
			TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -21.25f, 0.0f, 0.2f, 1.0f, 1.0f);
			//TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -13.0f, -11.0f, 0.0f, 1.0f, 1.0f);
			mZombie->mZombatarHatID = mApp->ReanimationGetID(aZombatar);
		}

		{
			Reanimation* aZombatarOutline = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZOMBATAR);
			aZombatarOutline->PlayReanim("anim_head1", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
			for (int i = 0; i < aZombatarOutline->mDefinition->mTracks.count; i++)
			{
				aZombatarOutline->mTrackInstances[i].mRenderGroup = RENDER_GROUP_HIDDEN;
			}
			ReanimatorTrackInstance* aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
			AttachEffect* aAttachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatarOutline, 0, 0);
			aBodyReanim->mFrameBasePose = 0;
			TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -21.25f, 0.0f, 0.2f, 1.0f, 1.0f);
			//TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -13.0f, -11.0f, 0.0f, 1.0f, 1.0f);
			mZombie->mZombatarHatLineID = mApp->ReanimationGetID(aZombatarOutline);
		}
	}
}

ZombatarWidget::~ZombatarWidget() {
	if (mBackButton) delete mBackButton;
	if (mFinishButton) delete mFinishButton;
	if (mSkinButton) delete mSkinButton;
	if (mHairButton) delete mHairButton;
	if (mFacialHairButton) delete mFacialHairButton;
	if (mTidbitsButton) delete mTidbitsButton;
	if (mEyeWearButton) delete mEyeWearButton;
	if (mClothesButton) delete mClothesButton;
	if (mAccessoryButton) delete mAccessoryButton;
	if (mHatsButton) delete mHatsButton;
	if (mBackdropsButton) delete mBackdropsButton;
	if (mClearPickButton) delete mClearPickButton;
	if (mClearPalleteButton) delete mClearPalleteButton;
	for (NewLawnButton* pallete : mColorPalletes) {
		delete pallete;
	}

	for (NewLawnButton* item : mZombatarItems) {
		delete item;
	}

	if (mZombie)
	{
		mZombie->DieNoLoot();
		delete mZombie;
		mZombie = nullptr;
	}
}


bool mOnBackBtn = false;

void ZombatarWidget::Update() {
	mBackButton->MarkDirty();
	mFinishButton->MarkDirty();
	mSkinButton->MarkDirty();
	mHairButton->MarkDirty();
	mFacialHairButton->MarkDirty();
	mTidbitsButton->MarkDirty();
	mEyeWearButton->MarkDirty();
	mClothesButton->MarkDirty();
	mAccessoryButton->MarkDirty();
	mHatsButton->MarkDirty();
	mBackdropsButton->MarkDirty();
	mClearPickButton->MarkDirty();
	mClearPalleteButton->MarkDirty();
	if (mZombie) mZombie->Update();
}

void ZombatarWidget::Draw(Graphics* g) {
	g->PushState();
	g->SetLinearBlend(true);
	g->DrawImage(IMAGE_ZOMBATAR_MAIN_BG, 0, 0);

	Graphics leafG(*g);
	leafG.mTransX -= BOARD_WIDTH;
	for (int i = 0; i < 3; i++)
	{
		mApp->ReanimationGet(mApp->mGameSelector->mFlowerReanimID[i])->Draw(&leafG);
	}

	g->DrawImageF(IMAGE_ZOMBATAR_DAY_GRAVE, 8.55f, 432.05f);

	g->DrawImageF(IMAGE_ZOMBATAR_WIDGET_BG, 26, 25);
	DrawZombiePortrait(g);
	DrawZombatarItems(g);
	DrawColorPalletes(g);
	DrawZombieAvatar(g);
}

void ZombatarWidget::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	AddWidget(mFinishButton);
	AddWidget(mSkinButton);
	AddWidget(mHairButton);
	AddWidget(mFacialHairButton);
	AddWidget(mTidbitsButton);
	AddWidget(mEyeWearButton);
	AddWidget(mClothesButton);
	AddWidget(mAccessoryButton);
	AddWidget(mHatsButton);
	AddWidget(mBackdropsButton);
	AddWidget(mClearPickButton);
	AddWidget(mClearPalleteButton);
	for (NewLawnButton* pallete : mColorPalletes) {
		AddWidget(pallete);
	}

	for (NewLawnButton* item : mZombatarItems) {
		AddWidget(item);
	}
}

//0x44BCA0
void ZombatarWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	RemoveWidget(mFinishButton);
	RemoveWidget(mSkinButton);
	RemoveWidget(mHairButton);
	RemoveWidget(mFacialHairButton);
	RemoveWidget(mTidbitsButton);
	RemoveWidget(mEyeWearButton);
	RemoveWidget(mClothesButton);
	RemoveWidget(mAccessoryButton);
	RemoveWidget(mHatsButton);
	RemoveWidget(mBackdropsButton);
	RemoveWidget(mClearPickButton);
	RemoveWidget(mClearPalleteButton);
	for (NewLawnButton* pallete : mColorPalletes) {
		RemoveWidget(pallete);
	}

	for (NewLawnButton* item : mZombatarItems) {
		RemoveWidget(item);
	}
}

//0x44BD80
void ZombatarWidget::OrderInManagerChanged()
{
	PutInfront(mBackButton, this);
	PutInfront(mFinishButton, this);
	PutInfront(mSkinButton, this);
	PutInfront(mHairButton, this);
	PutInfront(mFacialHairButton, this);
	PutInfront(mTidbitsButton, this);
	PutInfront(mEyeWearButton, this);
	PutInfront(mClothesButton, this);
	PutInfront(mAccessoryButton, this);
	PutInfront(mHatsButton, this);
	PutInfront(mBackdropsButton, this);

	for (NewLawnButton* pallete : mColorPalletes) {
		PutInfront(pallete, this);
	}

	for (NewLawnButton* items : mZombatarItems) {
		PutInfront(items, this);
	}

	PutInfront(mClearPickButton, this);
	PutInfront(mClearPalleteButton, this);
	PutBehind(mApp->mGameSelector->mOverlayWidget, this);
}

void ZombatarWidget::ButtonDepress(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;


	if (theId >= ZombatarWidget::ZombatarScreen_Skin && theId <= ZombatarWidget::ZombatarScreen_Backdrops) {
		ZombatarCategory aPage = (ZombatarCategory)(theId - (int)ZombatarWidget::ZombatarScreen_Skin);
		if (aPage != mCurCategory)
		{
			SetCategory(aPage);
			mApp->PlaySample(Sexy::SOUND_TAP);
		}

		return;
	}
	
	if (theId >= ZombatarWidget::ZombatarScreen_Palletes && theId <= ZombatarWidget::ZombatarScreen_Palletes + NUM_COLOR_PALLETES) {
		int aPallete = theId - ZombatarWidget::ZombatarScreen_Palletes;
		int* aTargetPallete = nullptr;

		if (mCurCategory == ZombatarCategory::ZombatarPage_Skin) aTargetPallete = &mCurSkinPallete;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) aTargetPallete = &mCurHairPallete;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Backdrops) aTargetPallete = &mCurBackgroundPallete;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) aTargetPallete = &mCurHatPallete;

		if (aTargetPallete && aPallete != *aTargetPallete)
		{
			SetZombatarRef(aTargetPallete, aPallete);
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
		return;
	}

	if (theId >= ZombatarWidget::ZombatarScreen_Items && theId <= ZombatarWidget::ZombatarScreen_Items + NUM_ZOMBATAR_ITEMS) {
		int aItem = theId - ZombatarWidget::ZombatarWidget::ZombatarScreen_Items;
		int* aTargetItem = nullptr;

		if (mCurCategory == ZombatarCategory::ZombatarPage_Backdrops) aTargetItem = &mCurBackground;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) aTargetItem = &mCurHair; 
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Clothes) aTargetItem = &mCurClothe;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) aTargetItem = &mCurHat;

		if (aTargetItem && aItem != *aTargetItem)
		{
			SetZombatarRef(aTargetItem, aItem);
			UpdatePalletes();
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
		return;
	}

	if (theId == ZombatarWidget::ZombatarScreen_ClearPick) {
		int aItem = -1;
		int* aTargetItem = nullptr;

		if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) aTargetItem = &mCurHair;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Clothes) aTargetItem = &mCurClothe;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) aTargetItem = &mCurHat;

		if (aTargetItem && aItem != *aTargetItem)
		{
			SetZombatarRef(aTargetItem, aItem);
			UpdatePalletes();
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
	}

	if (theId == ZombatarWidget::ZombatarScreen_ClearPallete) {
		int aPallete = -1;
		int* aTargetPallete = nullptr;

		if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) aTargetPallete = &mCurHairPallete;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Backdrops) aTargetPallete = &mCurBackgroundPallete;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) aTargetPallete = &mCurHatPallete;

		if (aTargetPallete && aPallete != *aTargetPallete)
		{
			SetZombatarRef(aTargetPallete, aPallete);
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
		return;
	}

	switch (theId)
	{
		case ZombatarWidget::ZombatarScreen_Back:
		{
			mBackButton->SetDisabled(true);
			mBackButton->mButtonImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mBackButton->mDownImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mBackButton->mOverImage = Sexy::IMAGE_ZOMBATAR_MAINMENUBACK_PRESSED;
			mApp->mGameSelector->SlideTo(0, 0);
			mApp->mGameSelector->mWidgetManager->SetFocus(mApp->mGameSelector);
			mApp->mGameSelector->mAdventureButton->SetDisabled(false);
			mApp->mGameSelector->mMinigameButton->SetDisabled(false);
			mApp->mGameSelector->mPuzzleButton->SetDisabled(false);
			mApp->mGameSelector->mOptionsButton->SetDisabled(false);
			mApp->mGameSelector->mQuitButton->SetDisabled(false);
			mApp->mGameSelector->mHelpButton->SetDisabled(false);
			mApp->mGameSelector->mChangeUserButton->SetDisabled(false);
			mApp->mGameSelector->mStoreButton->SetDisabled(false);
			mApp->mGameSelector->mAlmanacButton->SetDisabled(false);
			mApp->mGameSelector->mSurvivalButton->SetDisabled(false);
			mApp->mGameSelector->mZenGardenButton->SetDisabled(false);
#ifdef _HAS_ZOMBATAR
			mApp->mGameSelector->mZombatarButton->SetDisabled(false);
#endif
#ifdef _HAS_ACHIEVEMENTS
			mApp->mGameSelector->mAchievementsButton->SetDisabled(false);
#endif
#ifdef _HAS_MORESCREEN 
			mApp->mGameSelector->mQuickPlayButton->SetDisabled(false);
#endif
			break;
		}
	}

	mApp->PlaySample(Sexy::SOUND_TAP);
}

void ZombatarWidget::ButtonMouseEnter(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;

	if (theId == (int)ZombatarWidget::ZombatarScreen_Back)
	{
		mApp->PlayFoley(FoleyType::FOLEY_BLEEP);
	}
}

void ZombatarWidget::ButtonPress(int theId, int theClickCount)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;
}

void ZombatarWidget::DrawColorPalletes(Graphics* g)
{
	int* aTargetItem = nullptr;
	int* aTargetPallete = nullptr;
	Color* curPalletes = nullptr;
	int palleteCount = 0;


	if (mCurCategory == ZombatarCategory::ZombatarPage_Skin) {
		aTargetPallete = &mCurSkinPallete;
		curPalletes = gZombatarSkinPalletes;
		palleteCount = NUM_SKIN_COLOR_PALLETES;
	} else if (mCurCategory == ZombatarCategory::ZombatarPage_Backdrops) {
		aTargetPallete = &mCurBackgroundPallete;
		aTargetItem = &mCurBackground;
	}
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) {
		aTargetPallete = &mCurHairPallete;
		aTargetItem = &mCurHair;
	}
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Clothes) {
		aTargetItem = &mCurClothe;
	}
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) {
		aTargetPallete = &mCurHatPallete;
		aTargetItem = &mCurHat;
	}

	if (aTargetItem) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)*aTargetItem);
		curPalletes = aDef.mColorGroup;
		if (aDef.mColorGroup != nullptr)
		{
			palleteCount = aDef.mPage != ZombatarCategory::ZombatarPage_Skin ? NUM_COLOR_PALLETES : NUM_SKIN_COLOR_PALLETES;
		}
	}

	if (palleteCount == 12) {
		g->DrawImageF(IMAGE_ZOMBATAR_COLORS_BG_SMALL, 243, 325);
	}
	else {
		g->DrawImageF(IMAGE_ZOMBATAR_COLORS_BG, 221.5f, 335);
	}

	if (palleteCount == 0)
	{
		std::string aLabel = _S("[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
		if (aTargetItem) {
			ZombatarDefinition& aDef = gZombatarDefinitions[*aTargetItem];
			if (aDef.mColorGroup == nullptr) aLabel = _S("[ZOMBATAR_COLOR_NOT_APPLICABLE]");
		}
		TodDrawString(g, aLabel, 221.5f + IMAGE_ZOMBATAR_COLORS_BG->GetWidth() / 2, 395, Sexy::FONT_BRIANNETOD12, Color::White, DrawStringJustification::DS_ALIGN_CENTER);
	}
	else
	{
		for (size_t i = 0; i < palleteCount; i++) {
			NewLawnButton* aColorPallete = mColorPalletes[i];
			if (!aColorPallete || aColorPallete->mDisabled) {
				continue;
			}

			g->PushState();
			g->SetColorizeImages(true);
			g->SetColor(curPalletes[i]);
			bool isSelected = aTargetPallete  && *aTargetPallete == i;
			g->mColor.mAlpha = isSelected ? 255 : aColorPallete->mIsOver ? 128 : 64;
			if (isSelected) {
				g->DrawImageF(IMAGE_ZOMBATAR_COLORPICKER_HIGHLIGHT, aColorPallete->mX - 2.0f, aColorPallete->mY - 2.5f);
			}
			g->DrawImageF(IMAGE_ZOMBATAR_COLORPICKER, aColorPallete->mX, aColorPallete->mY);
			g->PopState();
		}

		if (!mClearPalleteButton->mDisabled) {
			DrawClearPallete(g, mClearPalleteButton, aTargetPallete);
		}
	}
}

void ZombatarWidget::DrawZombiePortrait(Graphics* g) {
	g->PushState();
	g->SetClipRect(596, 116, 180, 180);
	{
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)(mCurBackground));
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(mCurBackgroundPallete == -1 || aDef.mColorGroup == nullptr ? Color::White : aDef.mColorGroup[mCurBackgroundPallete]);
		if (aDef.mImage)
			g->DrawImageF(*aDef.mImage, 596, 116);
		g->SetColor(Color::White);
		if (aDef.mOutlineImage)
			g->DrawImageF(*aDef.mOutlineImage, 596, 116);
		g->PopState();
	}

	{
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(gZombatarSkinPalletes[mCurSkinPallete]);
		g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK_SKIN, 630.5f, 155);
		g->PopState();
		g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK, 630.5f, 155);
	}

	if (mCurHair != -1)
	{
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)(mCurHair));
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(mCurHairPallete == -1 || aDef.mColorGroup == nullptr ? Color::White : aDef.mColorGroup[mCurHairPallete]);
		float posX = 630.5f;
		float posY = 155.0f;
		float offsetX = 0;
		float offsetY = 0;
		float outlineX = 0;
		float outlineY = 0;
		GetZombatarPortraitOffset((ZombatarItem)(mCurHair), &offsetX, &offsetY);
		GetOutlineOffset((ZombatarItem)(mCurHair), &outlineX, &outlineY);
		if (aDef.mImage)
			g->DrawImageF(*aDef.mImage, posX + offsetX - outlineX - 1.5f, posY + offsetY - outlineY - 0.5f);
		g->SetColor(Color::White);
		if (aDef.mOutlineImage)
			g->DrawImageF(*aDef.mOutlineImage, posX + offsetX, posY + offsetY);
		g->PopState();
	}

	if (mCurClothe != -1)
	{
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)(mCurClothe));
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(mCurClothe == -1 || aDef.mColorGroup == nullptr ? Color::White : aDef.mColorGroup[mCurHairPallete]);
		float posX = 630.5f;
		float posY = 155.0f;
		float offsetX = 0;
		float offsetY = 0;
		float outlineX = 0;
		float outlineY = 0;
		GetZombatarPortraitOffset((ZombatarItem)(mCurClothe), &offsetX, &offsetY);
		GetOutlineOffset((ZombatarItem)(mCurClothe), &outlineX, &outlineY);
		if (aDef.mImage)
			g->DrawImageF(*aDef.mImage, posX + offsetX - outlineX, posY + offsetY - outlineY);
		g->SetColor(Color::White);
		if (aDef.mOutlineImage)
			g->DrawImageF(*aDef.mOutlineImage, posX + offsetX, posY + offsetY);
		g->PopState();
	}

	if (mCurHat != -1)
	{
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)(mCurHat));
		g->PushState();
		g->SetColorizeImages(true);
		g->SetColor(mCurHatPallete == -1 || aDef.mColorGroup == nullptr ? Color::White : aDef.mColorGroup[mCurHatPallete]);
		float posX = 630.5f;
		float posY = 155.0f;
		float offsetX = 0;
		float offsetY = 0;
		float outlineX = 0;
		float outlineY = 0;
		GetZombatarPortraitOffset((ZombatarItem)(mCurHat), &offsetX, &offsetY);
		GetOutlineOffset((ZombatarItem)(mCurHat), &outlineX, &outlineY);
		if (aDef.mImage)
			g->DrawImageF(*aDef.mImage, posX + offsetX - outlineX, posY + offsetY - outlineY);
		g->SetColor(Color::White);
		if (aDef.mOutlineImage)
			g->DrawImageF(*aDef.mOutlineImage, posX + offsetX, posY + offsetY);
		g->PopState();
	}
	g->PopState();
}

ZombatarDefinition& GetZombatarDefinition(ZombatarItem theItem) {
	return gZombatarDefinitions[theItem];
}

void ZombatarWidget::DrawZombieAvatar(Graphics* g) {
	g->PushState();
	g->SetClipRect(599, 300, 176, 200);
	g->DrawImageF(IMAGE_ALMANAC_GROUNDDAY, 599.5f, 300);
	if (mZombie)
	{
		if (mZombie->BeginDraw(g))
		{
			mZombie->DrawShadow(g);
			mZombie->Draw(g);
			mZombie->EndDraw(g);
		}
	}
	g->PopState();
	g->DrawImageF(IMAGE_ZOMBATAR_DISPLAY_WINDOW, 5, 0);
	g->PopState();
}

void ZombatarWidget::DrawZombatarItems(Graphics* g)
{
	g->DrawImageF(IMAGE_ZOMBATAR_WIDGET_INNER_BG, 152, 125);

	if (mCurCategory == ZombatarCategory::ZombatarPage_Skin)
	{
		TodDrawStringWrapped(g, TodStringTranslate(_S("[ZOMBATAR_START_TEXT]")), Rect(142.5f, 180, IMAGE_ZOMBATAR_WIDGET_INNER_BG->GetWidth() + 18, 175), Sexy::FONT_DWARVENTODCRAFT15, Color(208, 190, 44, 192), DrawStringJustification::DS_ALIGN_CENTER);
	}
	else
	{
		for (int i = 0; i < (int)ZombatarItem::NUM_ZOMBATAR_ITEMS; i++) {
			ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
			NewLawnButton* aZombatarItem = mZombatarItems[i];
			int* aTargetItem = nullptr;
			if (aDef.mPage == ZombatarCategory::ZombatarPage_Backdrops) aTargetItem = &mCurBackground;
			else if (aDef.mPage == ZombatarCategory::ZombatarPage_Hairs) aTargetItem = &mCurHair;
			else if (aDef.mPage == ZombatarCategory::ZombatarPage_Clothes) aTargetItem = &mCurClothe;
			else if (aDef.mPage == ZombatarCategory::ZombatarPage_Hats) aTargetItem = &mCurHat;

			if (aTargetItem && aDef.mPage == mCurCategory && !aZombatarItem->mDisabled) {
				DrawZombatarItem(g, aZombatarItem, (ZombatarItem)i, aTargetItem, &aDef);
			}
		}

		int* aTargetItem = nullptr;
		if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) aTargetItem = &mCurHair;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Clothes) aTargetItem = &mCurClothe;
		else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) aTargetItem = &mCurHat;
		if (aTargetItem)
		{
			DrawClearItem(g, mClearPickButton, aTargetItem);
		}
	}
}

void ZombatarWidget::GetOutlineOffset(ZombatarItem theItem, float* offsetX, float* offsetY) {
	switch (theItem) {
	case ZombatarItem::ZOMBATAR_HAIR_1:
		*offsetX = -9.0f;
		*offsetY = -2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_2:
		*offsetX = -2.0f; 
		*offsetY = -4.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_11:
		*offsetX = -2.0f;
		*offsetY = -2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = -1.0f; 
		*offsetY = -3.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_13:
		*offsetX = -2.0f; 
		*offsetY = -1.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_14:
		*offsetX = -2.0f; 
		*offsetY = -5.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_15:
		*offsetX = -1.0f; 
		break;
	case ZombatarItem::ZOMBATAR_HAT_1:
		*offsetX = -2.0f; 
		*offsetY = -1.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_3:
		*offsetX = -15.0f;
		*offsetY = 1.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_6:
		*offsetX = -4.0f;
		*offsetY = 2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_7:
		*offsetX = 1.0f;
		*offsetY = -15.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_8:
	case ZombatarItem::ZOMBATAR_HAT_9:
		*offsetX = 2.0f;
		*offsetY = 2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_11:
		*offsetX = -1.0f;
		*offsetY = -14.0f;
		break;
	}
}

void ZombatarWidget::GetZombatarItemScale(ZombatarItem theItem, float* scaleX, float* scaleY) {
	switch (theItem) {
		case ZombatarItem::ZOMBATAR_HAIR_14:
			*scaleX = 0.2875f;
			*scaleY = 0.2875f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_10:
			*scaleX = 0.3f;
			*scaleY = 0.3f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_2:
		case ZombatarItem::ZOMBATAR_HAIR_4:
			*scaleX = 0.325f;
			*scaleY = 0.325f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_1:
		case ZombatarItem::ZOMBATAR_HAIR_3:
		case ZombatarItem::ZOMBATAR_HAIR_8:
		case ZombatarItem::ZOMBATAR_HAIR_13:
		case ZombatarItem::ZOMBATAR_HAIR_15:
		case ZombatarItem::ZOMBATAR_HAIR_16:
		case ZombatarItem::ZOMBATAR_HAIR_12:
			*scaleX = 0.35f;
			*scaleY = 0.35f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_11:
			*scaleX = 0.375f;
			*scaleY = 0.375f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_5:
			*scaleX = 0.4f;
			*scaleY = 0.4f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_6:
			*scaleX = 0.425f;
			*scaleY = 0.425f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_7:
			*scaleX = 0.5f;
			*scaleY = 0.5f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_9:
			*scaleX = 1.4f;
			*scaleY = 0.9f;
			break;
		case ZombatarItem::ZOMBATAR_CLOTHE_1:
		case ZombatarItem::ZOMBATAR_CLOTHE_2:
		case ZombatarItem::ZOMBATAR_CLOTHE_3:
		case ZombatarItem::ZOMBATAR_CLOTHE_4:
		case ZombatarItem::ZOMBATAR_CLOTHE_5:
		case ZombatarItem::ZOMBATAR_CLOTHE_6:
		case ZombatarItem::ZOMBATAR_CLOTHE_7:
		case ZombatarItem::ZOMBATAR_CLOTHE_8:
		case ZombatarItem::ZOMBATAR_CLOTHE_9:
		case ZombatarItem::ZOMBATAR_CLOTHE_10:
		case ZombatarItem::ZOMBATAR_CLOTHE_11:
		case ZombatarItem::ZOMBATAR_CLOTHE_12:
			*scaleX = 0.475f;
			*scaleY = 0.475f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_8:
			*scaleX = 0.275f;
			*scaleY = 0.275f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_6:
			*scaleX = 0.3f;
			*scaleY = 0.3f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_13:
			*scaleX = 0.3025f;
			*scaleY = 0.3025f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_14:
			*scaleX = 0.345f;
			*scaleY = 0.345f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_10:
			*scaleX = 0.35f;
			*scaleY = 0.35f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_1:
		case ZombatarItem::ZOMBATAR_HAT_2:
		case ZombatarItem::ZOMBATAR_HAT_4:
			*scaleX = 0.375f;
			*scaleY = 0.375f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_12:
			*scaleX = 0.39f;
			*scaleY = 0.39f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_9:
			*scaleX = 0.43f;
			*scaleY = 0.43f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_5:
			*scaleX = 0.44f;
			*scaleY = 0.44f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_11:
			*scaleX = 0.455f;
			*scaleY = 0.35f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_3:
			*scaleX = 0.465f;
			*scaleY = 0.465f;
			break;
		case ZombatarItem::ZOMBATAR_HAT_7:
			*scaleX = 0.565f;
			*scaleY = 0.565f;
			break;
	}
}

void ZombatarWidget::GetZombatarItemOffset(ZombatarItem theItem, float* offsetX, float* offsetY) {
	switch (theItem) {
	case ZombatarItem::ZOMBATAR_HAIR_1:
		*offsetX = 0.5f;
		*offsetY = 5.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_2:
	case ZombatarItem::ZOMBATAR_HAIR_7:
		*offsetX = 0.5f;
		*offsetY = 7.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_3:
		*offsetY = 15.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_4:
		*offsetY = 2.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_5:
		*offsetX = -3.5f;
		*offsetY = 8.75f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_6:
		*offsetX = 0.5f;
		*offsetY = 2.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_8:
		*offsetX = 0.5f;
		*offsetY = 7.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_9:
		*offsetX = 2.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_10:
		*offsetX = 1.5f;
		*offsetY = 11.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_11:
		*offsetX = 0.5f;
		*offsetY = 1.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = 1.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_13:
		*offsetX = 0.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_14:
		*offsetX = 0.5f;
		*offsetY = 8.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_16:
		*offsetX = 0.5f;
		*offsetY = 0.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_1:
		*offsetX = 1.5f;
		*offsetY = 10.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_2:
		*offsetY = 10.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_3:
		*offsetX = 6.5f;
		*offsetY = 12.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_4:
		*offsetX = 0.5f;
		*offsetY = 11.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_5:
		*offsetX = 0.5f;
		*offsetY = 10.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_6:
		*offsetX = 2.0f;
		*offsetY = 11.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_7:
		*offsetX = 0.5f;
		*offsetY = 8.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_8:
		*offsetX = 0.5f;
		*offsetY = 0.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_10:
		*offsetX = 0.5f;
		*offsetY = 17.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_11:
		*offsetX = 0.5f;
		*offsetY = 2.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_12:
		*offsetX = 0.5f;
		*offsetY = 3.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_13:
		*offsetY = 11.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_14:
		*offsetY = 10.0f;
		break;
	}
}

void ZombatarWidget::GetZombatarPortraitOffset(ZombatarItem theItem, float* offsetX, float* offsetY) {
	switch (theItem) {
	case ZombatarItem::ZOMBATAR_HAIR_1:
		*offsetX = -15.0f;
		*offsetY = -40.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_2:
		*offsetX = -15.0f;
		*offsetY = -15.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_3:
		*offsetX = -15.0f;
		*offsetY = -10.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_4:
		*offsetX = -8.0f;
		*offsetY = -25.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_8:
		*offsetX = -10.0f;
		*offsetY = -25.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_11:
		*offsetX = -13.0f;
		*offsetY = -21.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_13:
		*offsetX = -5.0f;
		*offsetY = -27.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_14:
		*offsetX = -29.0f;
		*offsetY = -42.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_15:
		*offsetX = 7.0f;
		*offsetY = -36.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_16:
		*offsetX = -12.0f;
		*offsetY = -20.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_10:
		*offsetX = -15.0f;
		*offsetY = -8.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = 13.0f;
		*offsetY = -45.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_5:
		*offsetX = -2.0f;
		*offsetY = -3.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_6:
		*offsetX = 1.0f;
		*offsetY = -27.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_7:
		*offsetX = 13.0f;
		*offsetY = -18.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_9:
		*offsetX = 90.0f;
		*offsetY = 15.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_1:
		*offsetX = 49.0f;
		*offsetY = 69.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_2:
		*offsetX = 37.0f;
		*offsetY = 59.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_3:
		*offsetX = 48.0f;
		*offsetY = 70.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_4:
		*offsetX = 38.0f;
		*offsetY = 70.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_5:
		*offsetX = 52.0f;
		*offsetY = 74.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_6:
		*offsetX = 54.0f;
		*offsetY = 69.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_7:
		*offsetX = 39.0f;
		*offsetY = 64.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_8:
		*offsetX = 50.0f;
		*offsetY = 69.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_9:
		*offsetX = 51.0f;
		*offsetY = 61.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_10:
		*offsetX = 46.0f;
		*offsetY = 68.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_11:
		*offsetX = 46.0f;
		*offsetY = 70.0f;
		break;
	case ZombatarItem::ZOMBATAR_CLOTHE_12:
		*offsetX = 41.0f;
		*offsetY = 73.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_1:
		*offsetX = -10.0f;
		*offsetY = -35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_2:
		*offsetX = 9.0f;
		*offsetY = -28.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_3:
		*offsetX = -2.0f;
		*offsetY = -20.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_4:
		*offsetX = -27.0f;
		*offsetY = -30.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_5:
		*offsetX = 3.0f;
		*offsetY = -24.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_6:
		*offsetX = -20.0f;
		*offsetY = -37.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_7:
		*offsetX = 15.0f;
		*offsetY = -23.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_8:
		*offsetX = -35.0f;
		*offsetY = -40.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_9:
		*offsetY = -40.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_10:
		*offsetX = -25.0f;
		*offsetY = 5.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_11:
		*offsetX = 25.0f;
		*offsetY = -32.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_12:
		*offsetX = 5.0f;
		*offsetY = -25.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_13:
		*offsetX = -20.0f;
		*offsetY = -40.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAT_14:
		*offsetX = -15.0f;
		*offsetY = -35.0f;
		break;
	}
}

void ZombatarWidget::DrawZombatarItem(Graphics* g, NewLawnButton* button, ZombatarItem theItem, int* theTargetItem, ZombatarDefinition* aDef)
{
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(button->mIsOver || (int)theItem == *theTargetItem ? Color::White : Color(128, 128, 128, 128));
	g->DrawImageF((int)theItem ==*theTargetItem ? IMAGE_ZOMBATAR_ACCESSORY_BG_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BG, button->mX, button->mY);
	g->SetClipRect(button->mX + 8, button->mY + 8, button->mWidth - 17, button->mHeight - 17);
	
	float scaleX = 0.27f;
	float scaleY = 0.27f;
	GetZombatarItemScale(aDef->mZombatarItem, &scaleX, &scaleY);

	if (aDef->mPage == ZombatarCategory::ZombatarPage_Clothes) {
		TodDrawImageScaledF(g, gZombatarClothes[theItem - ZombatarItem::ZOMBATAR_CLOTHE_1], button->mX - 10.0f, button->mY - 10.0f, scaleX, scaleY);
		g->PopState();
		return;
	}

	float positionX = button->mX + 9.0f;
	float positionY = button->mY + 9.0f;

	float adjustmentX = 0.0f;
	float adjustmentY = 0.0f;
	GetZombatarItemOffset(aDef->mZombatarItem, &adjustmentX, &adjustmentY);
	positionX += adjustmentX;
	positionY += adjustmentY;

	if (aDef->mImage) {
		TodDrawImageScaledF(g, *aDef->mImage, positionX, positionY, scaleX, scaleY);
	}

	float offsetX = 0.0f;
	float offsetY = 0.0f;
	GetOutlineOffset(aDef->mZombatarItem, &offsetX, &offsetY);
	offsetX *= scaleX;
	offsetY *= scaleY;
	positionX += offsetX;
	positionY += offsetY;

	if (aDef->mOutlineImage) {
		TodDrawImageScaledF(g, *aDef->mOutlineImage, positionX, positionY, scaleX, scaleY);
	}
	g->PopState();
}

void ZombatarWidget::DrawClearItem(Graphics* g, NewLawnButton* button, int* theTargetItem)
{
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(button->mIsOver ? Color::White : Color(128, 128, 128, 128));
	g->DrawImageF(IMAGE_ZOMBATAR_ACCESSORY_BG, button->mX, button->mY);
	g->SetClipRect(button->mX + 9, button->mY + 9, button->mWidth - 18, button->mHeight - 18);
	g->DrawImageF(IMAGE_ZOMBATAR_ACCESSORY_BG_NONE, button->mX, button->mY);
	g->PopState();
}

void ZombatarWidget::DrawClearPallete(Graphics* g, NewLawnButton* button, int* theTargetItem)
{
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(Color::White);
	g->mColor.mAlpha = button->mIsOver ? 255 : 128;
	g->DrawImageF(IMAGE_ZOMBATAR_COLORPICKER_NONE, button->mX, button->mY);
	g->PopState();
}

void ZombatarWidget::UpdatePalletes() {
	int* aTargetItem = nullptr;
	int* aTargetPallete = nullptr;
	Color* curPalletes = nullptr;
	int palleteCount = 0;

	if (mCurCategory == ZombatarCategory::ZombatarPage_Skin) {
		aTargetPallete = &mCurSkinPallete;
		curPalletes = gZombatarSkinPalletes;
		palleteCount = NUM_SKIN_COLOR_PALLETES;
	}
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Backdrops) {
		aTargetItem = &mCurBackground;
		aTargetPallete = &mCurBackgroundPallete;
		curPalletes = gZombatarBrightPalletes;
	} 
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Hairs) {
		aTargetPallete = &mCurHairPallete;
		aTargetItem = &mCurHair;
	}
	else if (mCurCategory == ZombatarCategory::ZombatarPage_Hats) {
		aTargetPallete = &mCurHatPallete;
		aTargetItem = &mCurHat;
	}

	if (aTargetItem) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)*aTargetItem);
		curPalletes = aDef.mColorGroup;

		if (aDef.mColorGroup != nullptr)
		{
			palleteCount = aDef.mPage != ZombatarCategory::ZombatarPage_Skin ? NUM_COLOR_PALLETES : NUM_SKIN_COLOR_PALLETES;
		}
	}

	for (NewLawnButton* aPallete : mColorPalletes) {
		aPallete->SetDisabled(true);
	}
	for (size_t i = 0; i < palleteCount; i++) {
		mColorPalletes[i]->SetDisabled(false);
	}
}

void ZombatarWidget::UpdateItems() {
	for (int i = 0; i < (int)ZombatarItem::NUM_ZOMBATAR_ITEMS; i++) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
		NewLawnButton* aZombatarItem = mZombatarItems[i];
		aZombatarItem->SetDisabled(aDef.mPage != mCurCategory);
	}
}

void ZombatarWidget::UpdateZombieAvatar() {
	if (!mZombie) return;

	{
		Reanimation* aZombatarHairReanim = mApp->ReanimationTryToGet(mZombie->mZombatarHairID);
		aZombatarHairReanim->AssignRenderGroupToTrack("anim_hair", mCurHair != -1 ? RENDER_GROUP_HIDDEN : RENDER_GROUP_NORMAL);
		if (aZombatarHairReanim)
		{
			for (int i = ZombatarItem::ZOMBATAR_HAIR_1; i <= ZombatarItem::ZOMBATAR_HAIR_16; i++) {
				ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
				int hairNum = i - ZombatarItem::ZOMBATAR_HAIR_1;
				if (aZombatarHairReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) aZombatarHairReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", hairNum).c_str(), RENDER_GROUP_HIDDEN);
				if (aZombatarHairReanim->TrackExists(StrFormat("hair_%02d_line", hairNum).c_str())) aZombatarHairReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", hairNum).c_str(), RENDER_GROUP_HIDDEN);

				if (aZombatarHairReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) {
					ReanimatorTrackInstance* aHairTrack = aZombatarHairReanim->GetTrackInstanceByName(StrFormat("hair_%02d", hairNum).c_str());
					aHairTrack->mTrackColor = mCurHairPallete == -1 ? Color::White : aDef.mColorGroup[mCurHairPallete];
				}
			}

			int theHair = mCurHair - ZombatarItem::ZOMBATAR_HAIR_1;
			if (mCurHair != -1) {
				aZombatarHairReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", theHair).c_str(), RENDER_GROUP_NORMAL);
			}
		}

		Reanimation* aZombatarHairLineReanim = mApp->ReanimationTryToGet(mZombie->mZombatarHairLineID);
		if (aZombatarHairLineReanim)
		{
			for (int i = ZombatarItem::ZOMBATAR_HAIR_1; i <= ZombatarItem::ZOMBATAR_HAIR_16; i++) {
				int hairNum = i - ZombatarItem::ZOMBATAR_HAIR_1;
				if (aZombatarHairReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) aZombatarHairLineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", hairNum).c_str(), RENDER_GROUP_HIDDEN);
				if (aZombatarHairReanim->TrackExists(StrFormat("hair_%02d_line", hairNum).c_str())) aZombatarHairLineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", hairNum).c_str(), RENDER_GROUP_HIDDEN);
			}

			int theHair = mCurHair - ZombatarItem::ZOMBATAR_HAIR_1;
			if (mCurHair != -1 && aZombatarHairReanim->TrackExists(StrFormat("hair_%02d_line", theHair).c_str())) {
				aZombatarHairLineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", theHair).c_str(), RENDER_GROUP_NORMAL);
			}
		}
	}
	{
		Reanimation* aZombatarHatReanim = mApp->ReanimationTryToGet(mZombie->mZombatarHatID);
		aZombatarHatReanim->AssignRenderGroupToTrack("anim_hair", mCurHair != -1 ? RENDER_GROUP_HIDDEN : RENDER_GROUP_NORMAL);
		if (aZombatarHatReanim)
		{
			for (int i = ZombatarItem::ZOMBATAR_HAT_1; i <= ZombatarItem::ZOMBATAR_HAT_14; i++) {
				ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
				int hatNum = i - ZombatarItem::ZOMBATAR_HAT_1;
				if (aZombatarHatReanim->TrackExists(StrFormat("hats_%02d", hatNum).c_str())) aZombatarHatReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d", hatNum).c_str(), RENDER_GROUP_HIDDEN);
				if (aZombatarHatReanim->TrackExists(StrFormat("hats_%02d_line", hatNum).c_str())) aZombatarHatReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d_line", hatNum).c_str(), RENDER_GROUP_HIDDEN);

				if (aZombatarHatReanim->TrackExists(StrFormat("hats_%02d", hatNum).c_str())) {
					ReanimatorTrackInstance* aHairTrack = aZombatarHatReanim->GetTrackInstanceByName(StrFormat("hats_%02d", hatNum).c_str());
					aHairTrack->mTrackColor = mCurHatPallete == -1 ? Color::White : aDef.mColorGroup[mCurHatPallete];
				}
			}

			int theHat = mCurHat - ZombatarItem::ZOMBATAR_HAT_1;
			if (mCurHat != -1) {
				aZombatarHatReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d", theHat).c_str(), RENDER_GROUP_NORMAL);
			}
		}

		Reanimation* aZombatarHatLineReanim = mApp->ReanimationTryToGet(mZombie->mZombatarHatLineID);
		if (aZombatarHatLineReanim)
		{
			for (int i = ZombatarItem::ZOMBATAR_HAT_1; i <= ZombatarItem::ZOMBATAR_HAT_14; i++) {
				ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
				int hatNum = i - ZombatarItem::ZOMBATAR_HAT_1;
				if (aZombatarHatReanim->TrackExists(StrFormat("hats_%02d", hatNum).c_str())) aZombatarHatLineReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d", hatNum).c_str(), RENDER_GROUP_HIDDEN);
				if (aZombatarHatReanim->TrackExists(StrFormat("hats_%02d_line", hatNum).c_str())) aZombatarHatLineReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d_line", hatNum).c_str(), RENDER_GROUP_HIDDEN);
			}

			int theHat = mCurHat - ZombatarItem::ZOMBATAR_HAT_1;
			if (mCurHat != -1 && aZombatarHatReanim->TrackExists(StrFormat("hats_%02d_line", theHat).c_str())) {
				aZombatarHatLineReanim->AssignRenderGroupToTrack(StrFormat("hats_%02d_line", theHat).c_str(), RENDER_GROUP_NORMAL);
			}
		}
	}
}

MemoryImage* gZombatarClothes[NUM_CLOTHES];

void ZombatarWidget::CreateZombatarClothes() {
	for (int i = ZombatarItem::ZOMBATAR_CLOTHE_1; i <= ZombatarItem::ZOMBATAR_CLOTHE_12; i++) {
		int clotheNum = i - ZombatarItem::ZOMBATAR_CLOTHE_1;

		MemoryImage* aImage = new MemoryImage();
		aImage->mWidth = 147;
		aImage->mHeight = 146;
		int aNumBits = 147 * 146;
		aImage->mBits = new unsigned long[aNumBits + 1];
		aImage->mHasTrans = true;
		aImage->mHasAlpha = true;
		memset(aImage->mBits, 0, aNumBits * 4);
		aImage->mBits[aNumBits] = Sexy::MEMORYCHECK_ID;

		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.SetLinearBlend(true);
		aMemoryGraphics.SetFastStretch(false);
		aMemoryGraphics.PushState();
		aMemoryGraphics.SetColorizeImages(true);
		aMemoryGraphics.SetColor(Color(134, 147, 122));
		aMemoryGraphics.DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK_SKIN, 0, 0);
		aMemoryGraphics.PopState();
		aMemoryGraphics.DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK, 0, 0);

		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
		aMemoryGraphics.PushState();
		aMemoryGraphics.SetColorizeImages(true);
		aMemoryGraphics.SetColor(Color::White);
		float offsetX = 0;
		float offsetY = 0;
		float outlineX = 0;
		float outlineY = 0;
		GetZombatarPortraitOffset((ZombatarItem)i, &offsetX, &offsetY);
		GetOutlineOffset((ZombatarItem)i, &outlineX, &outlineY);
		if (aDef.mImage)
			aMemoryGraphics.DrawImageF(*aDef.mImage, offsetX - outlineX, offsetY - outlineY);
		aMemoryGraphics.SetColor(Color::White);
		if (aDef.mOutlineImage)
			aMemoryGraphics.DrawImageF(*aDef.mOutlineImage, offsetX, offsetY);
		aMemoryGraphics.PopState();

		aImage->mBitsChangedCount++;
		aImage->mNumCols = 0;
		aImage->mNumRows = 0;
		gZombatarClothes[clotheNum] = aImage;
	}
}

void DisposeZombatarClothesCache() {
	for (MemoryImage* aImage : gZombatarClothes) {
		delete aImage;
	}
}
#endif