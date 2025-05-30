#ifndef __REANIMATORCACHE_H__
#define __REANIMATORCACHE_H__

#include "../../ConstEnums.h"
#include "../../Sexy.TodLib/TodList.h"
namespace Sexy
{
    class Graphics;
    class MemoryImage;
};
using namespace Sexy;

class LawnApp;
class ReanimCacheImageVariation
{
public:
    SeedType                mSeedType;
    DrawVariation           mDrawVariation;
    FilterVariation         mFilterVariation;
    MemoryImage*            mImage;
};
typedef TodList<ReanimCacheImageVariation> ImageVariationList;

class Reanimation;
class ReanimatorCache
{
public:
	MemoryImage*			mPlantImages[SeedType::NUM_SEED_TYPES];
    ImageVariationList      mImageVariationList;
    MemoryImage*            mLawnMowers[LawnMowerType::NUM_MOWER_TYPES];
    MemoryImage*            mZombieImages[ZombieType::NUM_CACHED_ZOMBIE_TYPES];
    LawnApp*                mApp;

public:
    //ReanimatorCache() { ReanimatorCacheInitialize(); }
    //~ReanimatorCache() { ReanimatorCacheDispose(); }

    void                    ReanimatorCacheInitialize();
    void                    ReanimatorCacheDispose();
    void                    DrawCachedPlant(Graphics* g, float thePosX, float thePosY, SeedType theSeedType, DrawVariation theDrawVariation, bool isIZombieLevel = false, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
    void                    DrawCachedMower(Graphics* g, float thePosX, float thePosY, LawnMowerType theMowerType, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
    void                    DrawCachedZombie(Graphics* g, float thePosX, float thePosY, ZombieType theZombieType, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
    MemoryImage*            MakeBlankMemoryImage(int theWidth, int theHeight);
    MemoryImage*            MakeCachedPlantFrame(SeedType theSeedType, DrawVariation theDrawVariation, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
    MemoryImage*            MakeCachedMowerFrame(LawnMowerType theMowerType);
    MemoryImage*            MakeCachedZombieFrame(ZombieType theZombieType);
    /*inline*/ void         GetPlantImageSize(SeedType theSeedType, int& theOffsetX, int& theOffsetY, int& theWidth, int& theHeight);
    void                    DrawReanimatorFrame(Graphics* g, float thePosX, float thePosY, ReanimationType theReanimationType, const char* theTrackName, DrawVariation theDrawVariation, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
    void                    UpdateReanimationForVariation(Reanimation* theReanim, DrawVariation theDrawVariation, FilterVariation theFilterVariation = FilterVariation::FILTERVARIATION_NONE);
};

#endif
