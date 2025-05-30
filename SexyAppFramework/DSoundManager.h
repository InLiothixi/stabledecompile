#ifndef __DSOUNDMANAGER_H__
#define __DSOUNDMANAGER_H__

#include "dsoundversion.h"
#include "SoundManager.h"

namespace Sexy
{

class DSoundInstance;

class DSoundManager : public SoundManager
{
	friend class DSoundInstance;
	friend class DSoundMusicInterface;

protected:
	LPDIRECTSOUNDBUFFER		mSourceSounds[MAX_SOURCE_SOUNDS];
	SexyString				mSourceFileNames[MAX_SOURCE_SOUNDS];
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;
	ulong					mSourceDataSizes[MAX_SOURCE_SOUNDS];
	double					mBaseVolumes[MAX_SOURCE_SOUNDS];
	int						mBasePans[MAX_SOURCE_SOUNDS];
	DSoundInstance*			mPlayingSounds[MAX_CHANNELS];	
	double					mMasterVolume;
	DWORD					mLastReleaseTick;

protected:
	int						FindFreeChannel();
	int						VolumeToDB(double theVolume);
	bool					LoadOGGSound(unsigned int theSfxID, const SexyString& theFilename);
	bool					LoadFModSound(unsigned int theSfxID, const SexyString& theFilename);
	bool					LoadWAVSound(unsigned int theSfxID, const SexyString& theFilename);
	bool					LoadAUSound(unsigned int theSfxID, const SexyString& theFilename);
	bool					WriteWAV(unsigned int theSfxID, const SexyString& theFilename, const SexyString& theDepFile);
	bool					GetTheFileTime(const SexyString& theDepFile, FILETIME* theFileTime);
	void					ReleaseFreeChannels();

public:
	LPDIRECTSOUND			mDirectSound;
	bool					mHaveFMod;

	DSoundManager(HWND theHWnd, bool haveFMod);
	virtual ~DSoundManager();

	virtual bool			Initialized();
	
	virtual bool			LoadSound(unsigned int theSfxID, const SexyString& theFilename);
	virtual int				LoadSound(const SexyString& theFilename);
	virtual void			ReleaseSound(unsigned int theSfxID);	

	virtual void			SetVolume(double theVolume);
	virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
	virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan);

	virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID);

	virtual void			ReleaseSounds();
	virtual void			ReleaseChannels();		

	virtual double			GetMasterVolume();
	virtual void			SetMasterVolume(double theVolume);

	virtual void			Flush();

	virtual void			SetCooperativeWindow(HWND theHWnd, bool isWindowed);
	virtual void			StopAllSounds();
	virtual int				GetFreeSoundId();
	virtual int				GetNumSounds();
};

}

#endif //__DSOUNDMANAGER_H__