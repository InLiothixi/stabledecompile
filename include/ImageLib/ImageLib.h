#ifndef __IMAGELIB_H__
#define __IMAGELIB_H__

#include <string>
#include "../../SexyAppFramework/Common.h"

namespace ImageLib
{

class Image
{
public:
	int						mWidth;
	int						mHeight;
	unsigned long*			mBits;

public:
	Image();
	virtual ~Image();

	int						GetWidth();
	int						GetHeight();
	unsigned long*			GetBits();
};

bool WriteJPEGImage(const SexyString& theFileName, Image* theImage);
bool WritePNGImage(const SexyString& theFileName, Image* theImage);
bool WriteTGAImage(const SexyString& theFileName, Image* theImage);
bool WriteBMPImage(const SexyString& theFileName, Image* theImage);
extern int gAlphaComposeColor;
extern bool gAutoLoadAlpha;
extern bool gIgnoreJPEG2000Alpha;  // I've noticed alpha in jpeg2000's that shouldn't have alpha so this defaults to true


Image* GetImage(const SexyString& theFileName, bool lookForAlphaImage = true);

void InitJPEG2000();
void CloseJPEG2000();
void SetJ2KCodecKey(const SexyString& theKey);

}

#endif //__IMAGELIB_H__