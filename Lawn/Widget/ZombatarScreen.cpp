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
	{ZombatarItem::ZOMBATAR_BACKGROUND_CRAZYDAVE,	nullptr,									&Sexy::IMAGE_ZOMBATAR_BACKGROUND_CRAZYDAVE,	ZombatarPage::ZombatarPage_Backdrops, 0, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_MENU,	    nullptr,									&Sexy::IMAGE_ZOMBATAR_BACKGROUND_MENU,		ZombatarPage::ZombatarPage_Backdrops, 1, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_MENU_DOS,    nullptr,									&Sexy::IMAGE_ZOMBATAR_BACKGROUND_MENU_DOS,  ZombatarPage::ZombatarPage_Backdrops, 2, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_ROOF,	    nullptr,									&Sexy::IMAGE_ZOMBATAR_BACKGROUND_ROOF,		ZombatarPage::ZombatarPage_Backdrops, 3, 0, nullptr},
	{ZombatarItem::ZOMBATAR_BACKGROUND_BLANK,		nullptr,									&Sexy::IMAGE_ZOMBATAR_BACKGROUND_BLANK,		ZombatarPage::ZombatarPage_Backdrops, 4, 0, gZombatarBrightPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_1,					&Sexy::IMAGE_ZOMBATAR_HAIR_1,				&Sexy::IMAGE_ZOMBATAR_HAIR_1_MASK,			ZombatarPage::ZombatarPage_Hair,	  0, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_2,					&Sexy::IMAGE_ZOMBATAR_HAIR_2,				&Sexy::IMAGE_ZOMBATAR_HAIR_2_MASK,			ZombatarPage::ZombatarPage_Hair,	  1, 0, gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_3,					&Sexy::IMAGE_ZOMBATAR_HAIR_3,				nullptr,									ZombatarPage::ZombatarPage_Hair,	  2, 0,	nullptr},
	{ZombatarItem::ZOMBATAR_HAIR_4,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_4,				ZombatarPage::ZombatarPage_Hair,	  3, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_5,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_5,				ZombatarPage::ZombatarPage_Hair,	  4, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_6,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_6,				ZombatarPage::ZombatarPage_Hair,	  5, 0,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_7,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_7,				ZombatarPage::ZombatarPage_Hair,	  0, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_8,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_8,				ZombatarPage::ZombatarPage_Hair,	  1, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_9,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_9,				ZombatarPage::ZombatarPage_Hair,	  2, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_10,				nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_10,				ZombatarPage::ZombatarPage_Hair,	  3, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_11,				&Sexy::IMAGE_ZOMBATAR_HAIR_11,				&Sexy::IMAGE_ZOMBATAR_HAIR_11_MASK,			ZombatarPage::ZombatarPage_Hair,	  4, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_12,				&Sexy::IMAGE_ZOMBATAR_HAIR_12,				&Sexy::IMAGE_ZOMBATAR_HAIR_12_MASK,			ZombatarPage::ZombatarPage_Hair,	  5, 1,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_13,				&Sexy::IMAGE_ZOMBATAR_HAIR_13,				&Sexy::IMAGE_ZOMBATAR_HAIR_13_MASK,			ZombatarPage::ZombatarPage_Hair,	  0, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_14,				&Sexy::IMAGE_ZOMBATAR_HAIR_14,				&Sexy::IMAGE_ZOMBATAR_HAIR_14_MASK,			ZombatarPage::ZombatarPage_Hair,	  1, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_15,				&Sexy::IMAGE_ZOMBATAR_HAIR_15,				&Sexy::IMAGE_ZOMBATAR_HAIR_15_MASK,			ZombatarPage::ZombatarPage_Hair,	  2, 2,	gZombatarDimPalletes},
	{ZombatarItem::ZOMBATAR_HAIR_16,				nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_16,				ZombatarPage::ZombatarPage_Hair,	  3, 2,	gZombatarDimPalletes},
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
	Color(128, 47, 204),
	Color(255, 255, 255)
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
	Color(159, 17, 20),
	Color(255, 255, 255)
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

	mZombie = nullptr;
	ResetZombatar();
}

void ZombatarWidget::SetPage(ZombatarPage thePage) {
	mPage = thePage;

	UpdateItems();
	UpdatePalletes();

	mSkinButton->mButtonImage = thePage == ZombatarPage_Skin ? IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_SKIN_BUTTON;
	mSkinButton->mOverImage = thePage == ZombatarPage_Skin ? IMAGE_ZOMBATAR_SKIN_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_SKIN_BUTTON;
	mHairButton->mButtonImage = thePage == ZombatarPage_Hair ? IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HAIR_BUTTON;
	mHairButton->mOverImage = thePage == ZombatarPage_Hair ? IMAGE_ZOMBATAR_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HAIR_BUTTON_OVER;
	mFacialHairButton->mButtonImage = thePage == ZombatarPage_FacialHair ? IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON;
	mFacialHairButton->mOverImage = thePage == ZombatarPage_FacialHair ? IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_FACIAL_HAIR_BUTTON_OVER;
	mTidbitsButton->mButtonImage = thePage == ZombatarPage_Tidbits ? IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_TIDBITS_BUTTON;
	mTidbitsButton->mOverImage = thePage == ZombatarPage_Tidbits ? IMAGE_ZOMBATAR_TIDBITS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_TIDBITS_BUTTON_OVER;
	mEyeWearButton->mButtonImage = thePage == ZombatarPage_EyeWear ? IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_EYEWEAR_BUTTON;
	mEyeWearButton->mOverImage = thePage == ZombatarPage_EyeWear ? IMAGE_ZOMBATAR_EYEWEAR_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_EYEWEAR_BUTTON_OVER;
	mClothesButton->mButtonImage = thePage == ZombatarPage_Clothes ? IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_CLOTHES_BUTTON;
	mClothesButton->mOverImage = thePage == ZombatarPage_Clothes ? IMAGE_ZOMBATAR_CLOTHES_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_CLOTHES_BUTTON_OVER;
	mAccessoryButton->mButtonImage = thePage == ZombatarPage_Acessory ? IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BUTTON;
	mAccessoryButton->mOverImage = thePage == ZombatarPage_Acessory ? IMAGE_ZOMBATAR_ACCESSORY_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BUTTON_OVER;
	mHatsButton->mButtonImage = thePage == ZombatarPage_Hats ? IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HATS_BUTTON;
	mHatsButton->mOverImage = thePage == ZombatarPage_Hats ? IMAGE_ZOMBATAR_HATS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_HATS_BUTTON_OVER;
	mBackdropsButton->mButtonImage = thePage == ZombatarPage_Backdrops ? IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_BACKDROPS_BUTTON;
	mBackdropsButton->mOverImage = thePage == ZombatarPage_Backdrops ? IMAGE_ZOMBATAR_BACKDROPS_BUTTON_HIGHLIGHT : IMAGE_ZOMBATAR_BACKDROPS_BUTTON_OVER;

	mClearPickButton->SetDisabled(true);
	if (thePage == ZombatarPage_Hair) {
		mClearPickButton->SetDisabled(false);
		mClearPickButton->Resize(166 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth - 4) * 4, 138 + (Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight - 4) * 2, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth, Sexy::IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight);
	}

	if (thePage == ZombatarPage::ZombatarPage_Skin) {
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
				NewLawnButton* mColorPallete = mColorPalletes[x + y * 9];
				mColorPallete->Resize(238 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth) * x, 367 + (4 + Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight) * y, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mWidth, Sexy::IMAGE_ZOMBATAR_COLORPICKER->mHeight);
			}
		}
	}
}

void ZombatarWidget::SetZombatarRef(int* theTarget, int theValue) {
	*theTarget = theValue;
}

void ZombatarWidget::ResetZombatar() {
	SetPage(ZombatarPage::ZombatarPage_Skin);
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
			mZombie->mZombatarID = mApp->ReanimationGetID(aZombatar);
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
			mZombie->mZombatarOutlineID = mApp->ReanimationGetID(aZombatarOutline);
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

	PutBehind(mApp->mGameSelector->mOverlayWidget, this);
}

void ZombatarWidget::ButtonDepress(int theId)
{
	if (mApp->mGameSelector->mSlideCounter > 0)
		return;


	if (theId >= ZombatarWidget::ZombatarScreen_Skin && theId <= ZombatarWidget::ZombatarScreen_Backdrops) {
		ZombatarPage aPage = (ZombatarPage)(theId - (int)ZombatarWidget::ZombatarScreen_Skin);
		if (aPage != mPage)
		{
			SetPage(aPage);
			mApp->PlaySample(Sexy::SOUND_TAP);
		}

		return;
	}
	
	if (theId >= ZombatarWidget::ZombatarScreen_Palletes && theId <= ZombatarWidget::ZombatarScreen_Palletes + NUM_COLOR_PALLETES) {
		int aPallete = theId - ZombatarWidget::ZombatarScreen_Palletes;
		int* aTargetPallete = nullptr;

		if (mPage == ZombatarPage::ZombatarPage_Skin) aTargetPallete = &mCurSkinPallete;
		else if (mPage == ZombatarPage::ZombatarPage_Hair) aTargetPallete = &mCurHairPallete;
		else if (mPage == ZombatarPage::ZombatarPage_Backdrops) aTargetPallete = &mCurBackgroundPallete;

		if (aTargetPallete && aPallete != *aTargetPallete)
		{
			if (aPallete == NUM_COLOR_PALLETES - 1) {
				aPallete = -1;
			}
			SetZombatarRef(aTargetPallete, aPallete);
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
		return;
	}

	if (theId >= ZombatarWidget::ZombatarScreen_Items && theId <= ZombatarWidget::ZombatarScreen_Items + NUM_ZOMBATAR_ITEMS) {
		int aItem = theId - ZombatarWidget::ZombatarWidget::ZombatarScreen_Items;
		int* aTargetItem = nullptr;

		if (mPage == ZombatarPage::ZombatarPage_Backdrops) aTargetItem = &mCurBackground;
		else if (mPage == ZombatarPage::ZombatarPage_Hair) aTargetItem = &mCurHair; 
		

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

		if (mPage == ZombatarPage::ZombatarPage_Hair) aTargetItem = &mCurHair;


		if (aTargetItem && aItem != *aTargetItem)
		{
			SetZombatarRef(aTargetItem, aItem);
			UpdatePalletes();
			mApp->PlaySample(Sexy::SOUND_TAP);
			UpdateZombieAvatar();
		}
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


	if (mPage == ZombatarPage::ZombatarPage_Skin) {
		aTargetPallete = &mCurSkinPallete;
		curPalletes = gZombatarSkinPalletes;
		palleteCount = NUM_SKIN_COLOR_PALLETES;
	} else if (mPage == ZombatarPage::ZombatarPage_Backdrops) {
		aTargetPallete = &mCurBackgroundPallete;
		aTargetItem = &mCurBackground;
	}
	else if (mPage == ZombatarPage::ZombatarPage_Hair) {
		aTargetPallete = &mCurHairPallete;
		aTargetItem = &mCurHair;
	}

	if (aTargetItem) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)*aTargetItem);
		curPalletes = aDef.mColorGroup;
		if (aDef.mColorGroup != nullptr)
		{
			palleteCount = aDef.mPage != ZombatarPage::ZombatarPage_Skin ? NUM_COLOR_PALLETES : NUM_SKIN_COLOR_PALLETES;
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
			bool isSelected = *aTargetPallete == i;
			g->mColor.mAlpha = isSelected || aColorPallete->mIsOver ? 255 : 128;
			if (isSelected && i != 17) {
				g->DrawImageF(IMAGE_ZOMBATAR_COLORPICKER_HIGHLIGHT, aColorPallete->mX - 2.0f, aColorPallete->mY - 2.5f);
			}
			g->DrawImageF(
				i == 17 ? IMAGE_ZOMBATAR_COLORPICKER_NONE :
				IMAGE_ZOMBATAR_COLORPICKER
				, aColorPallete->mX, aColorPallete->mY);
			g->PopState();
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

	if (mPage == ZombatarPage::ZombatarPage_Skin)
	{
		TodDrawStringWrapped(g, TodStringTranslate(_S("[ZOMBATAR_START_TEXT]")), Rect(142.5f, 180, IMAGE_ZOMBATAR_WIDGET_INNER_BG->GetWidth() + 18, 175), Sexy::FONT_DWARVENTODCRAFT15, Color(208, 190, 44, 192), DrawStringJustification::DS_ALIGN_CENTER);
	}
	else
	{
		for (int i = 0; i < (int)ZombatarItem::NUM_ZOMBATAR_ITEMS; i++) {
			ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)i);
			NewLawnButton* aZombatarItem = mZombatarItems[i];
			int* aTargetItem = nullptr;
			if (aDef.mPage == ZombatarPage::ZombatarPage_Backdrops) aTargetItem = &mCurBackground;
			else if (aDef.mPage == ZombatarPage::ZombatarPage_Hair) aTargetItem = &mCurHair;

			if (aDef.mPage == mPage && !aZombatarItem->mDisabled)
				DrawZombatarItem(g, aZombatarItem, (ZombatarItem)i, aTargetItem, &aDef);
		}

		int* aTargetItem = nullptr;
		if (mPage == ZombatarPage::ZombatarPage_Hair) aTargetItem = &mCurHair;
		if (aTargetItem)
		{
			DrawClearItem(g, mClearPickButton, aTargetItem);
		}
	}
}

void ZombatarWidget::GetOutlineOffset(ZombatarItem theItem, float* offsetX, float* offsetY) {
	switch (theItem) {
	case ZombatarItem::ZOMBATAR_HAIR_1:
		*offsetX = -9.0f; // 8.0f
		*offsetY = -2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_2:
		*offsetX = -3.0f; // -3.0f
		*offsetY = -4.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_11:
		*offsetX = -3.0f; // 2.0f
		*offsetY = -2.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = -2.0f; // 1.0f
		*offsetY = -3.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_13:
		*offsetX = -3.0f; // 2.0f
		*offsetY = -1.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_14:
		*offsetX = -2.0f; // 1.0f
		*offsetY = -5.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_15:
		//*offsetX = -1.0f; 
		//*offsetY = -1.0f;
		break;
	}
}

void ZombatarWidget::GetZombatarItemScale(ZombatarItem theItem, float* scaleX, float* scaleY) {
	switch (theItem) {
		case ZombatarItem::ZOMBATAR_HAIR_1:
		case ZombatarItem::ZOMBATAR_HAIR_2:
		case ZombatarItem::ZOMBATAR_HAIR_3:
		case ZombatarItem::ZOMBATAR_HAIR_8:
		case ZombatarItem::ZOMBATAR_HAIR_11:
		case ZombatarItem::ZOMBATAR_HAIR_13:
		case ZombatarItem::ZOMBATAR_HAIR_15:
		case ZombatarItem::ZOMBATAR_HAIR_16:
			*scaleX = 0.35f;
			*scaleY = 0.35f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_12:
			*scaleX = 0.375f;
			*scaleY = 0.375f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_7:
			*scaleX = 0.5f;
			*scaleY = 0.5f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_9:
			*scaleX = 1.4f;
			*scaleY = 0.9f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_4:
			*scaleX = 0.325f;
			*scaleY = 0.325f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_14:

		case ZombatarItem::ZOMBATAR_HAIR_10:
			*scaleX = 0.3f;
			*scaleY = 0.3f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_5:
		case ZombatarItem::ZOMBATAR_HAIR_6:
			*scaleX = 0.45f;
			*scaleY = 0.45f;
			break;
	}
}

void ZombatarWidget::GetZombatarItemOffset(ZombatarItem theItem, float* offsetX, float* offsetY) {
	switch (theItem) {
	case ZombatarItem::ZOMBATAR_HAIR_1:
		*offsetX = 22.5f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_2:
		*offsetX = 20.0f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_3:
		*offsetX = 21.0f;
		*offsetY = 45.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_4:
		*offsetX = 15.0f;
		*offsetY = 20.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_8:
		*offsetX = 22.5f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_11:
		*offsetX = 25.0f;
		*offsetY = 27.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_13:
		*offsetX = 22.5f;
		*offsetY = 20.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_14:
		*offsetX = 8.5f;
		*offsetY = 27.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_15:
		*offsetX = 22.5f;
		*offsetY = 23.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_16:
		*offsetX = 22.5f;
		*offsetY = 37.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_10:
		*offsetX = 11.5f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = 25.0f;
		*offsetY = 30.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_5:
		*offsetX = 27.5f;
		*offsetY = 47.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_6:
		*offsetX = 35.0f;
		*offsetY = 37.5f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_7:
		*offsetX = 42.5f;
		*offsetY = 50.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_9:
		*offsetX = 75.0f;
		*offsetY = 65.0f;
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
	}
}

void ZombatarWidget::DrawZombatarItem(Graphics* g, NewLawnButton* button, ZombatarItem theItem, int* theTargetItem, ZombatarDefinition* aDef)
{
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(button->mIsOver || (int)theItem == *theTargetItem ? Color::White : Color(128, 128, 128, 128));
	g->DrawImageF((int)theItem ==*theTargetItem ? IMAGE_ZOMBATAR_ACCESSORY_BG_HIGHLIGHT : IMAGE_ZOMBATAR_ACCESSORY_BG, button->mX, button->mY);
	g->SetClipRect(button->mX + 9, button->mY + 9, button->mWidth - 18, button->mHeight - 18);

	float offsetX = 0.0f;
	float offsetY = 0.0f;
	float scaleX = 0.28f;
	float scaleY = 0.28f;

	GetZombatarItemScale(aDef->mZombatarItem, &scaleX, &scaleY);
	GetOutlineOffset(aDef->mZombatarItem, &offsetX, &offsetY);
	offsetX *= 1-scaleX;
	offsetY *= 1-scaleY;

	float positionX = button->mX;
	float positionY = button->mY;

	if (aDef->mImage) {
		positionX -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth + (*aDef->mImage)->mWidth * scaleX) / 2.0f;
		positionY -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight + (*aDef->mImage)->mHeight * scaleY) / 2.0f;
		
		float adjustmentX = 10 * scaleX;
		float adjustmentY = 10 * scaleY;
		GetZombatarItemOffset(aDef->mZombatarItem, &adjustmentX, &adjustmentY);
		positionX += adjustmentX;
		positionY += adjustmentY;

		TodDrawImageCenterScaledF(g, *aDef->mImage, positionX, positionY, scaleX, scaleY);
	}

	if (aDef->mOutlineImage) {
		if (!aDef->mImage) {
			positionX -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth + (*aDef->mOutlineImage)->mWidth * scaleX) / 2.0f;
			positionY -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight + (*aDef->mOutlineImage)->mHeight * scaleY) / 2.0f;

			float adjustmentX = 10 * scaleX;
			float adjustmentY = 10 * scaleY;
			GetZombatarItemOffset(aDef->mZombatarItem, &adjustmentX, &adjustmentY);
			positionX += adjustmentX;
			positionY += adjustmentY;
		}
		TodDrawImageCenterScaledF(g, *aDef->mOutlineImage, positionX + offsetX, positionY + offsetY, scaleX, scaleY);
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


void ZombatarWidget::UpdatePalletes() {
	int* aTargetItem = nullptr;
	int* aTargetPallete = nullptr;
	Color* curPalletes = nullptr;
	int palleteCount = 0;

	if (mPage == ZombatarPage::ZombatarPage_Skin) {
		aTargetPallete = &mCurSkinPallete;
		curPalletes = gZombatarSkinPalletes;
		palleteCount = NUM_SKIN_COLOR_PALLETES;
	}
	else if (mPage == ZombatarPage::ZombatarPage_Backdrops) {
		aTargetItem = &mCurBackground;
		aTargetPallete = &mCurBackgroundPallete;
		curPalletes = gZombatarBrightPalletes;
	} else if (mPage == ZombatarPage::ZombatarPage_Hair) {
		aTargetPallete = &mCurHairPallete;
		aTargetItem = &mCurHair;
	}

	if (aTargetItem) {
		ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)*aTargetItem);
		curPalletes = aDef.mColorGroup;

		if (aDef.mColorGroup != nullptr)
		{
			palleteCount = aDef.mPage != ZombatarPage::ZombatarPage_Skin ? NUM_COLOR_PALLETES : NUM_SKIN_COLOR_PALLETES;
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
		aZombatarItem->SetDisabled(aDef.mPage != mPage);
	}
}

void ZombatarWidget::UpdateZombieAvatar() {
	if (!mZombie) return;

	Reanimation* aZombatarReanim = mApp->ReanimationTryToGet(mZombie->mZombatarID);
	aZombatarReanim->AssignRenderGroupToTrack("anim_hair", mCurHair != -1 ? RENDER_GROUP_HIDDEN : RENDER_GROUP_NORMAL);
	if (aZombatarReanim)
	{
		for (int i = ZombatarItem::ZOMBATAR_HAIR_1; i <= ZombatarItem::ZOMBATAR_HAIR_16; i++) {
			int hairNum = i - ZombatarItem::ZOMBATAR_HAIR_1;
			if (aZombatarReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", hairNum).c_str(), RENDER_GROUP_HIDDEN);
			if (aZombatarReanim->TrackExists(StrFormat("hair_%02d_line", hairNum).c_str())) aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", hairNum).c_str(), RENDER_GROUP_HIDDEN);

			if (aZombatarReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) {
				ReanimatorTrackInstance* aHairTrack = aZombatarReanim->GetTrackInstanceByName(StrFormat("hair_%02d", hairNum).c_str());
				aHairTrack->mTrackColor = mCurHairPallete == -1 ? Color::White : gZombatarDimPalletes[mCurHairPallete];
			}
		}

		int theHair = mCurHair - ZombatarItem::ZOMBATAR_HAIR_1;
		if (mCurHair != -1) {
			aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", theHair).c_str(), RENDER_GROUP_NORMAL);
		}
	}
	Reanimation* aZombatarOutlineReanim = mApp->ReanimationTryToGet(mZombie->mZombatarOutlineID);
	if (aZombatarOutlineReanim)
	{
		for (int i = ZombatarItem::ZOMBATAR_HAIR_1; i <= ZombatarItem::ZOMBATAR_HAIR_16; i++) {
			int hairNum = i - ZombatarItem::ZOMBATAR_HAIR_1;
			if (aZombatarReanim->TrackExists(StrFormat("hair_%02d", hairNum).c_str())) aZombatarOutlineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", hairNum).c_str(), RENDER_GROUP_HIDDEN);
			if (aZombatarReanim->TrackExists(StrFormat("hair_%02d_line", hairNum).c_str())) aZombatarOutlineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", hairNum).c_str(), RENDER_GROUP_HIDDEN);
		}

		int theHair = mCurHair - ZombatarItem::ZOMBATAR_HAIR_1;
		if (mCurHair != -1 && aZombatarReanim->TrackExists(StrFormat("hair_%02d_line", theHair).c_str())) {
			aZombatarOutlineReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", theHair).c_str(), RENDER_GROUP_NORMAL);
		}
	}
}
#endif