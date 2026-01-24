#include "ParticleScreen.h"
#include "../Lawn/Widget/GameButton.h"
#include "../LawnApp.h"
#include "../Sexy.TodLib/TodCommon.h"
#include "../Resources.h"
#include "../SexyAppFramework/ImageFont.h"
#include "../SexyAppFramework/WidgetManager.h"
#include "../SexyAppFramework/SysFont.h"
#include "../Sexy.TodLib/TodParticle.h"
#include "../Sexy.TodLib/Definition.h"
#include "../GameConstants.h"

extern "C" {
#include <tinyfiledialogs.h>
}

std::vector<TodParticleSystem*> gParticleTests;

ParticleScreen::ParticleScreen(LawnApp* theApp) {
	mApp = theApp;
	mWidth = mApp->mWidth;
	mHeight = mApp->mHeight;
	mFont = new SysFont("Arial Unicode MS", 10, false, false, false);
	mIsImported = false;
	mParticleEffect = ParticleEffect::PARTICLE_MELONSPLASH;
	InstantiateParticle(mParticleEffect);
	mIsDragging = false;
	mDownX = 0;
	mDownY = 0;
	mViewX = -mWidth / 6;
	mViewY = 0;
	mStartViewX = 0;
	mStartViewY = 0;

	mExportButton = MakeNewButton(EXPORT, this, _S("EXPORT"), mFont, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mExportButton->mColors[ButtonWidget::COLOR_LABEL] = Color::Black;
	mExportButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color::Black;
	mExportButton->mDoFinger = true;
	mExportButton->mButtonImage = Sexy::IMAGE_BLANK;
	mExportButton->mOverImage = Sexy::IMAGE_BLANK;
	mExportButton->mDownImage = Sexy::IMAGE_BLANK;
	mExportButton->Resize(mWidth - 90, 10, 80, 30);

	mImportButton = MakeNewButton(IMPORT, this, _S("IMPORT"), mFont, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK, Sexy::IMAGE_BLANK);
	mImportButton->mColors[ButtonWidget::COLOR_LABEL] = Color::Black;
	mImportButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color::Black;
	mImportButton->mDoFinger = true;
	mImportButton->mButtonImage = Sexy::IMAGE_BLANK;
	mImportButton->mOverImage = Sexy::IMAGE_BLANK;
	mImportButton->mDownImage = Sexy::IMAGE_BLANK;
	mImportButton->Resize(mExportButton->mX - 90, 10, 80, 30);
}

ParticleScreen::~ParticleScreen() {
	if (mFont) delete mFont;
	delete mImportButton;
	delete mExportButton;
	gParticleTests.clear();
}

void ParticleScreen::ResetParticle()
{
	for (TodParticleSystem* aParticle : gParticleTests) {
		aParticle->ParticleSystemDie();
	}
	gParticleTests.clear();
	InstantiateParticle(mParticleEffect);
}

void ParticleScreen::InstantiateParticle(ParticleEffect theParticleEffect)
{
	if (gParticleTests.size() >= 2) return;

	TodParticleSystem* aParticle = mApp->AddTodParticle(mWidth / 2, mHeight / 2, 0, theParticleEffect);
	for (TodListNode<ParticleEmitterID>* aNode = aParticle->mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext) {
		TodParticleEmitter* emitter = aParticle->mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		uint tempFlags = static_cast<uint>(emitter->mEmitterDef->mParticleFlags);
		SetBit(tempFlags, (unsigned int)ParticleFlags::PARTICLE_SOFTWARE_ONLY, false);
		SetBit(tempFlags, (unsigned int)ParticleFlags::PARTICLE_HARDWARE_ONLY, false);
		emitter->mEmitterDef->mParticleFlags = static_cast<int>(tempFlags);
	}

	gParticleTests.push_back(aParticle);
}

void ParticleScreen::Resize(int theX, int theY, int theWidth, int theHeight) {
	Widget::Resize(theX, theY, theWidth, theHeight);
}

void ParticleScreen::Update() {
	Widget::Update();
	MarkDirty();

	int aNewParticles = 0;

	for (TodParticleSystem* aParticle : gParticleTests) {
		aParticle->Update();

		if (aParticle->mDead)
		{
			aNewParticles++;
			auto it = std::find(gParticleTests.begin(), gParticleTests.end(), aParticle);
			if (it != gParticleTests.end())
				gParticleTests.erase(it);
		}
	}

	for (int i = 0; i < aNewParticles; i++) InstantiateParticle(mParticleEffect);

	if (mIsDown && mWidgetManager->mLastMouseX < mWidth / 2 + mWidth / 4)
	{
		int dx = mWidgetManager->mLastMouseX - mStartMouseX;
		int dy = mWidgetManager->mLastMouseY - mStartMouseY;
		int dragDistanceSquared = dx * dx + dy * dy;

		if (!mIsDragging && dragDistanceSquared > 16) 
		{
			mIsDragging = true;
			mApp->SetCursor(CURSOR_DRAGGING);
			mDownX = mWidgetManager->mLastMouseX;
			mDownY = mWidgetManager->mLastMouseY;
			mStartViewX = mViewX;
			mStartViewY = mViewY;
		}

		if (mIsDragging)
		{
			mViewX = mStartViewX + (mWidgetManager->mLastMouseX - mDownX);
			mViewY = mStartViewY + (mWidgetManager->mLastMouseY - mDownY);

			mViewX = max(-mWidth / 2, min(mViewX, mWidth / 4));
			mViewY = max(-mWidth + mHeight, min(mViewY, mWidth - mHeight));
		}
	}
	else if (mIsDragging)
	{
		mIsDragging = false;
		mApp->SetCursor(CURSOR_POINTER);
	}
}

void ParticleScreen::MouseUp(int x, int y, int theClickCount)
{
	Widget::MouseUp(x, y, theClickCount);
	
	mIsDragging = false;
	mApp->SetCursor(CURSOR_POINTER);
}

void ParticleScreen::MouseDown(int x, int y, int theClickCount)
{
	Widget::MouseDown(x, y, theClickCount);
	mStartMouseX = x;
	mStartMouseY = y;
}

void ParticleScreen::Draw(Graphics* g) {
	g->PushState();
	g->SetColor(Color::Black);
	g->FillRect(0, 0, mWidth, mHeight);
	int screenZeroX = mViewX + mWidth / 2;
	int screenZeroY = mViewY + mHeight / 2;
	int aExtraHeight = mWidth - mHeight;
	for (int y = 0; y < (aExtraHeight * 2 + mHeight) / 50 + 1; y++)
	{
		g->SetColor(Color(32, 32, 32));
		int theY = y * 50 + mViewY - aExtraHeight;
		g->DrawLine(0, theY, mWidth, theY);
	}
	for (int x = 0; x < (mWidth / 2 + mWidth) / 50 + 1; x++)
	{
		g->SetColor(Color(32, 32, 32));
		int theX = x * 50 - mWidth / 4 + mViewX ;
		g->DrawLine(theX, 0, theX, mHeight);
	}
	g->SetColor(Color(255, 0, 0));
	g->DrawLine(0, screenZeroY-1, mWidth, screenZeroY-1);
	g->DrawLine(0, screenZeroY, mWidth, screenZeroY);
	g->SetColor(Color(0, 255, 0));
	g->DrawLine(screenZeroX-1, 0, screenZeroX-1, mHeight);
	g->DrawLine(screenZeroX, 0, screenZeroX, mHeight);
	g->mTransX += mViewX;
	g->mTransY += mViewY;

	TodParticleSystem* aParticle;
	if (aParticle = gParticleTests[0])
	{
		for (TodListNode<ParticleEmitterID>* aNode = aParticle->mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
		{
			TodParticleEmitter* emitter = aParticle->mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
			TodEmitterDefinition* def = emitter->mEmitterDef;

			if (def->mEmitterType == EmitterType::EMITTER_CIRCLE ||
				def->mEmitterType == EmitterType::EMITTER_CIRCLE_PATH ||
				def->mEmitterType == EmitterType::EMITTER_CIRCLE_EVEN_SPACING)
			{
				g->SetColor(Color(255, 255, 255));
				float aRadius1 = FloatTrackEvaluate(def->mEmitterRadius, emitter->mSystemTimeValue, 1);
				g->DrawCircle(mWidth / 2, mHeight / 2, aRadius1, (int)(aRadius1));
			}
			else if (def->mEmitterType == EmitterType::EMITTER_BOX || def->mEmitterType == EmitterType::EMITTER_BOX_PATH)
			{
				g->SetColor(Color(255, 255, 255));
				g->DrawRect(FloatTrackEvaluate(def->mEmitterBoxX, emitter->mSystemTimeValue, 0) + mWidth / 2, FloatTrackEvaluate(def->mEmitterBoxY, emitter->mSystemTimeValue, 0) + mHeight / 2,
					-FloatTrackEvaluate(def->mEmitterBoxX, emitter->mSystemTimeValue, 0) + FloatTrackEvaluate(def->mEmitterBoxX, emitter->mSystemTimeValue, 1),
					-FloatTrackEvaluate(def->mEmitterBoxY, emitter->mSystemTimeValue, 0) + FloatTrackEvaluate(def->mEmitterBoxY, emitter->mSystemTimeValue, 1));
			}

			for (int i = 0; i < emitter->mEmitterDef->mParticleFieldCount; i++)
			{
				ParticleField* aParticleField = &emitter->mEmitterDef->mParticleFields[i];
				if (aParticleField->mFieldType == ParticleFieldType::FIELD_GROUND_CONSTRAINT) {
					float theY = FloatTrackEvaluate(aParticleField->mY, 0, i) + mHeight / 2;
					g->SetColor(Color(0, 0, 255));
					g->DrawLine(-mViewX, theY - 1, -mViewX + mWidth, theY - 1);
					g->DrawLine(-mViewX, theY, -mViewX + mWidth, theY);
				}
			}
		}
		aParticle->Draw(g);
	}
	
	g->PopState();
	g->PushState();
	g->SetColor(Color::White);
	g->FillRect(mWidth / 2 + mWidth / 4, 0, mWidth / 4, mHeight);
	g->PopState();

	int particles = 0;
	for (TodParticleSystem* aParticle : gParticleTests) {
		for (TodListNode<ParticleEmitterID>* aNode = aParticle->mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext) {
			TodParticleEmitter* emitter = aParticle->mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
			particles += emitter->mParticleList.mSize;
		}
	}
	TodDrawString(g, StrFormat("Active Particles: %d", particles).c_str(), 10, 20, mFont, Color(200, 200, 200, 32), DrawStringJustification::DS_ALIGN_LEFT);
	TodDrawString(g, "Particle Editor v1.0", 10, mHeight - 10, mFont, Color(200, 200, 200, 32), DrawStringJustification::DS_ALIGN_LEFT);
}

void ParticleScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mImportButton);
	AddWidget(mExportButton);
}

//0x42F6B0
void ParticleScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mImportButton);
	RemoveWidget(mExportButton);
}

void ParticleScreen::ButtonDepress(int theId)
{
	if (theId == ParticleScreen::IMPORT)
	{
		const char* filterPatterns[] = { "*.xml", "*xml.compiled" };

		const char* xmlPath = tinyfd_openFileDialog(
			"Open",
			NULL,
			1,
			filterPatterns,
			"XML File",
			0
		);
	}
}

void ParticleScreen::KeyDown(KeyCode theKey)
{
	Widget::KeyDown(theKey);

	ParticleEffect mPreviousParticleEffect = mParticleEffect;
	if (theKey == KeyCode::KEYCODE_NEXT)  mParticleEffect = (ParticleEffect)(mParticleEffect + 1);
	else if (theKey == KeyCode::KEYCODE_PRIOR) mParticleEffect = (ParticleEffect)(mParticleEffect - 1);
	if (mParticleEffect == ParticleEffect::PARTICLE_NONE) mParticleEffect = ParticleEffect::PARTICLE_KERNEL_SPLAT;
	if (mParticleEffect == ParticleEffect::NUM_PARTICLES) mParticleEffect = ParticleEffect::PARTICLE_MELONSPLASH;

	if (theKey == KeyCode::KEYCODE_NEXT || theKey == KeyCode::KEYCODE_PRIOR)
		ResetParticle();
}
