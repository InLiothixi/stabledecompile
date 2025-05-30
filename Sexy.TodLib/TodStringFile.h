#ifndef __TODSTRINGFILE_H__
#define __TODSTRINGFILE_H__

#include "../SexyAppFramework/Graphics.h"
using namespace Sexy;

enum DrawStringJustification;
enum TodStringFormatFlag
{
    TOD_FORMAT_IGNORE_NEWLINES,
    TOD_FORMAT_HIDE_UNTIL_MAGNETSHROOM
};

class TodStringListFormat
{
public:
    const SexyChar* mFormatName;
    Font**          mNewFont;
    Color           mNewColor;
    int             mLineSpacingOffset;
    unsigned int    mFormatFlags;

public:
    TodStringListFormat();
    TodStringListFormat(const SexyChar* theFormatName, Font** theFont, const Color& theColor, int theLineSpacingOffset, unsigned int theFormatFlags);
};
extern int gTodStringFormatCount;               //[0x69DE4C]
extern TodStringListFormat* gTodStringFormats;  //[0x69DA34]

extern int gLawnStringFormatCount;
extern TodStringListFormat gLawnStringFormats[14];  //0x6A5010

void                TodStringListSetColors(TodStringListFormat* theFormats, int theCount);
void                TodWriteStringSetFormat(const SexyChar* theFormat, TodStringListFormat& theCurrentFormat);
bool                TodStringListReadName(const SexyChar*& thePtr, std::string& theName);
bool                TodStringListReadValue(const SexyChar*& thePtr, SexyString& theValue);
bool                TodStringListReadItems(const SexyChar* theFileText);
bool                TodStringListReadFile(const SexyChar* theFileName);
void                TodStringListLoad(const SexyChar* theFileName);
SexyString          TodStringListFind(const std::string& theName);
SexyString			TodStringTranslate(const SexyString& theString);
SexyString			TodStringTranslate(const SexyChar* theString);
bool                TodStringListExists(const std::string& theString);
void                TodStringRemoveReturnChars(SexyString& theString);
bool                CharIsSpaceInFormat(SexyChar theChar, const TodStringListFormat& theCurrentFormat);
int                 TodWriteString(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength);
/*inline*/ int      TodWriteWordWrappedHelper(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength, int theMaxChars);
int                 TodDrawStringWrappedHelper(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification, bool drawString, bool reuseFormat = false);
/*inline*/ void		TodDrawStringWrapped(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification, bool reuseFormat = false);

#endif  //__TODSTRINGFILE_H__