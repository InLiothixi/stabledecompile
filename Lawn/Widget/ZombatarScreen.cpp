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
	{ZombatarItem::ZOMBATAR_HAIR_3,					nullptr,									&Sexy::IMAGE_ZOMBATAR_HAIR_3,				ZombatarPage::ZombatarPage_Hair,	  2, 0,	nullptr},
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

	mZombie = nullptr;
	SetPage(ZombatarPage::ZombatarPage_Skin);
	mCurSkinPallete = 0;
	mCurBackground = ZombatarItem::ZOMBATAR_BACKGROUND_BLANK;
	mCurBackgroundPallete = NONE_COLOR_PALLETE;
	mCurHair = -1;
	mCurHairPallete = NONE_COLOR_PALLETE;
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
	SetupZombie();
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
		Reanimation* aZombatar = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZOMBATAR);
		aZombatar->PlayReanim("anim_head1", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
		for (int i = 0; i < aZombatar->mDefinition->mTracks.count; i++)
		{
			aZombatar->mTrackInstances[i].mRenderGroup = /*stricmp(aZombatar->mDefinition->mTracks.tracks[i].mName, "hats_13") == 0 || stricmp(aZombatar->mDefinition->mTracks.tracks[i].mName, "hats_13_line") == 0 ?
				RENDER_GROUP_NORMAL :*/ RENDER_GROUP_HIDDEN;
				/*if (stricmp(aZombatar->mDefinition->mTracks.tracks[i].mName, "hats_13") == 0)
					aZombatar->mTrackInstances[i].mTrackColor = Color(186, 45, 211, 255);*/
		}
		ReanimatorTrackInstance* aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");

		//mZombie->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);

		AttachEffect* aAttachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatar, 0, 0);
		aBodyReanim->mFrameBasePose = 0;

		//TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -21.25f, 0.0f, 0.2f, 1.0f, 1.0f);
		TodScaleRotateTransformMatrix(aAttachEffect->mOffset, -13.0f, -11.0f, 0.0f, 1.0f, 1.0f);

		mZombie->mZombatarID = mApp->ReanimationGetID(aZombatar);
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
	this->AddWidget(mBackButton);
	this->AddWidget(mFinishButton);
	this->AddWidget(mSkinButton);
	this->AddWidget(mHairButton);
	this->AddWidget(mFacialHairButton);
	this->AddWidget(mTidbitsButton);
	this->AddWidget(mEyeWearButton);
	this->AddWidget(mClothesButton);
	this->AddWidget(mAccessoryButton);
	this->AddWidget(mHatsButton);
	this->AddWidget(mBackdropsButton);

	for (NewLawnButton* pallete : mColorPalletes) {
		this->AddWidget(pallete);
	}

	for (NewLawnButton* item : mZombatarItems) {
		this->AddWidget(item);
	}
}

//0x44BCA0
void ZombatarWidget::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	this->RemoveWidget(mBackButton);
	this->RemoveWidget(mFinishButton);
	this->RemoveWidget(mSkinButton);
	this->RemoveWidget(mHairButton);
	this->RemoveWidget(mFacialHairButton);
	this->RemoveWidget(mTidbitsButton);
	this->RemoveWidget(mEyeWearButton);
	this->RemoveWidget(mClothesButton);
	this->RemoveWidget(mAccessoryButton);
	this->RemoveWidget(mHatsButton);
	this->RemoveWidget(mBackdropsButton);

	for (NewLawnButton* pallete : mColorPalletes) {
		this->RemoveWidget(pallete);
	}

	for (NewLawnButton* item : mZombatarItems) {
		this->RemoveWidget(item);
	}
}

//0x44BD80
void ZombatarWidget::OrderInManagerChanged()
{
	this->PutInfront(mBackButton, this);
	this->PutInfront(mFinishButton, this);
	this->PutInfront(mSkinButton, this);
	this->PutInfront(mHairButton, this);
	this->PutInfront(mFacialHairButton, this);
	this->PutInfront(mTidbitsButton, this);
	this->PutInfront(mEyeWearButton, this);
	this->PutInfront(mClothesButton, this);
	this->PutInfront(mAccessoryButton, this);
	this->PutInfront(mHatsButton, this);
	this->PutInfront(mBackdropsButton, this);

	for (NewLawnButton* pallete : mColorPalletes) {
		this->PutInfront(pallete, this);
	}

	for (NewLawnButton* items : mZombatarItems) {
		this->PutInfront(items, this);
	}

	this->PutBehind(mApp->mGameSelector->mOverlayWidget, this);
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
	g->DrawImageF(IMAGE_ZOMBATAR_COLORS_BG, 221.5f, 335);

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
			g->mColor.mAlpha = *aTargetPallete == i ? 255 : aColorPallete->mIsOver ? 128 : 64;
			g->DrawImageF(
				g->mColor.mRed == 255 && g->mColor.mGreen == 255 && g->mColor.mBlue == 255 ? IMAGE_ZOMBATAR_COLORPICKER_NONE :
				IMAGE_ZOMBATAR_COLORPICKER
				, aColorPallete->mX, aColorPallete->mY);
			g->PopState();
		}
	}
}

void ZombatarWidget::DrawZombiePortrait(Graphics* g) {
	ZombatarDefinition& aDef = GetZombatarDefinition((ZombatarItem)(mCurBackground));

	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(gZombatarBrightPalletes[mCurBackgroundPallete]);
	if (aDef.mImage)
	g->DrawImageF(*aDef.mImage, 596, 116);
	g->SetColor(Color::White);
	if (aDef.mOutlineImage)
	g->DrawImageF(*aDef.mOutlineImage, 596, 116);
	g->PopState();
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(gZombatarSkinPalletes[mCurSkinPallete]);
	g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK_SKIN, 630.5f, 155);
	g->PopState();
	g->DrawImageF(IMAGE_ZOMBATAR_ZOMBIE_BLANK, 630.5f, 155);
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

void ZombatarWidget::GetZombatarItemScale(ZombatarItem theItem, float* scale) {
	switch (theItem) {
		case ZombatarItem::ZOMBATAR_HAIR_1:
		case ZombatarItem::ZOMBATAR_HAIR_2:
		case ZombatarItem::ZOMBATAR_HAIR_3:
		case ZombatarItem::ZOMBATAR_HAIR_4:
		case ZombatarItem::ZOMBATAR_HAIR_8:
		case ZombatarItem::ZOMBATAR_HAIR_10:
		case ZombatarItem::ZOMBATAR_HAIR_11:
		case ZombatarItem::ZOMBATAR_HAIR_12:
		case ZombatarItem::ZOMBATAR_HAIR_13:
		case ZombatarItem::ZOMBATAR_HAIR_14:
		case ZombatarItem::ZOMBATAR_HAIR_15:
		case ZombatarItem::ZOMBATAR_HAIR_16:
			*scale = 0.35f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_5:
		case ZombatarItem::ZOMBATAR_HAIR_6:
		case ZombatarItem::ZOMBATAR_HAIR_7:
			*scale = 0.5f;
			break;
		case ZombatarItem::ZOMBATAR_HAIR_9:
			*scale = 0.75f;
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
	case ZombatarItem::ZOMBATAR_HAIR_5:
	case ZombatarItem::ZOMBATAR_HAIR_6:
	case ZombatarItem::ZOMBATAR_HAIR_7:
		*offsetX = 20.0f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_3:
	case ZombatarItem::ZOMBATAR_HAIR_4:
	case ZombatarItem::ZOMBATAR_HAIR_8:
	case ZombatarItem::ZOMBATAR_HAIR_9:
	case ZombatarItem::ZOMBATAR_HAIR_10:
	case ZombatarItem::ZOMBATAR_HAIR_11:
	case ZombatarItem::ZOMBATAR_HAIR_13:
	case ZombatarItem::ZOMBATAR_HAIR_14:
	case ZombatarItem::ZOMBATAR_HAIR_15:
	case ZombatarItem::ZOMBATAR_HAIR_16:
		*offsetX = 25.0f;
		*offsetY = 35.0f;
		break;
	case ZombatarItem::ZOMBATAR_HAIR_12:
		*offsetX = 25.0f;
		*offsetY = 25.0f;
		break;
	}
}

void ZombatarWidget::DrawZombatarItem(Graphics* g, NewLawnButton* button, ZombatarItem theItem, int* theTargetItem, ZombatarDefinition* aDef)
{
	g->DrawImageF(IMAGE_ZOMBATAR_ACCESSORY_BG, button->mX, button->mY);
	g->PushState();
	g->SetColorizeImages(true);
	g->SetColor(Color::White);
	g->mColor.mAlpha = (int)theItem == *theTargetItem ? 255 : 128;
	g->SetClipRect(button->mX + 9, button->mY + 9, button->mWidth - 18, button->mHeight - 18);

	float offsetX = 0.0f;
	float offsetY = 0.0f;
	float scale = 0.28f;

	GetZombatarItemScale(aDef->mZombatarItem, &scale);
	GetOutlineOffset(aDef->mZombatarItem, &offsetX, &offsetY);
	offsetX *= 1-scale;
	offsetY *= 1-scale;

	float positionX = button->mX;
	float positionY = button->mY;

	if (aDef->mImage)
	{
		positionX -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mWidth + (*aDef->mImage)->mWidth * scale) / 2.0f;
		positionY -= (IMAGE_ZOMBATAR_ACCESSORY_BG->mHeight + (*aDef->mImage)->mHeight * scale) / 2.0f;
		
		float adjustmentX = 10 * scale;
		float adjustmentY = 10 * scale;
		GetZombatarItemOffset(aDef->mZombatarItem, &adjustmentX, &adjustmentY);
		positionX += adjustmentX;
		positionY += adjustmentY;

		TodDrawImageCenterScaledF(g, *aDef->mImage, positionX, positionY, scale, scale);
	}
	if (aDef->mOutlineImage)
	{
		TodDrawImageCenterScaledF(g, *aDef->mOutlineImage, positionX + offsetX, positionY + offsetY, scale, scale);
	}
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

	if (aTargetPallete && palleteCount == 0) {
		*aTargetPallete = 17;
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

	mZombie->ReanimShowPrefix("anim_hair", mCurHair != -1 ? RENDER_GROUP_HIDDEN : RENDER_GROUP_NORMAL);
	Reanimation* aZombatarReanim = mApp->ReanimationTryToGet(mZombie->mZombatarID);
	if (aZombatarReanim)
	{
		for (int i = 0; i < ZombatarItem::ZOMBATAR_HAIR_16; i++) {
			aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", i).c_str(), RENDER_GROUP_HIDDEN);
			aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", i).c_str(), RENDER_GROUP_HIDDEN);

			ReanimatorTrackInstance* aHairTrack = aZombatarReanim->GetTrackInstanceByName(StrFormat("hair_%02d", i).c_str());
			aHairTrack->mTrackColor = gZombatarDimPalletes[mCurHairPallete];
		}

		int theHair = mCurHair - ZombatarItem::ZOMBATAR_HAIR_1;
		if (mCurHair != -1) {
			aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d", theHair).c_str(), RENDER_GROUP_NORMAL);
			aZombatarReanim->AssignRenderGroupToTrack(StrFormat("hair_%02d_line", theHair).c_str(), RENDER_GROUP_NORMAL);
		}
	}
}
#endif