#include "KeyCodes.h"

using namespace Sexy;

#define MAX_KEYNAME_LEN 12

typedef struct
{
	char mKeyName[MAX_KEYNAME_LEN];
	KeyCode mKeyCode;
} KeyNameEntry;

KeyNameEntry aKeyCodeArray[] =
{
	{"UNKNOWN", KEYCODE_UNKNOWN},
	{"LBUTTON", KEYCODE_LBUTTON},	
	{"RBUTTON", KEYCODE_RBUTTON},
	{"CANCEL", KEYCODE_CANCEL},
	{"MBUTTON", KEYCODE_MBUTTON},
	{"BACKSPACE", KEYCODE_BACK},
	{"TAB", KEYCODE_TAB},
	{"CLEAR", KEYCODE_CLEAR},
	{"RETURN", KEYCODE_RETURN},
	{"LEFT SHIFT", KEYCODE_SHIFT},
	{"LEFT CTRL", KEYCODE_CONTROL},
	{"MENU", KEYCODE_MENU},
	{"PAUSE", KEYCODE_PAUSE},
	{"CAPITAL", KEYCODE_CAPITAL},
	{"KANA", KEYCODE_KANA},
	{"HANGEUL", KEYCODE_HANGEUL},
	{"HANGUL", KEYCODE_HANGUL},
	{"JUNJA", KEYCODE_JUNJA},
	{"FINAL", KEYCODE_FINAL},
	{"HANJA", KEYCODE_HANJA},
	{"KANJI", KEYCODE_KANJI},
	{"ESCAPE", KEYCODE_ESCAPE},
	{"CONVERT", KEYCODE_CONVERT},
	{"NONCONVERT", KEYCODE_NONCONVERT},
	{"ACCEPT", KEYCODE_ACCEPT},
	{"MODECHANGE", KEYCODE_MODECHANGE},
	{"SPACE", KEYCODE_SPACE},
	{"PAGEUP", KEYCODE_PRIOR},
	{"PAGEDOWN", KEYCODE_NEXT},
	{"END", KEYCODE_END},
	{"HOME", KEYCODE_HOME},
	{"LEFT", KEYCODE_LEFT},
	{"UP", KEYCODE_UP},
	{"RIGHT", KEYCODE_RIGHT},
	{"DOWN", KEYCODE_DOWN},
	{"SELECT", KEYCODE_SELECT},
	{"PRINT", KEYCODE_PRINT},
	{"EXECUTE", KEYCODE_EXECUTE},
	{"SNAPSHOT", KEYCODE_SNAPSHOT},
	{"INSERT", KEYCODE_INSERT},
	{"DELETE", KEYCODE_DELETE},
	{"HELP", KEYCODE_HELP},
	{"LWIN", KEYCODE_LWIN},
	{"RWIN", KEYCODE_RWIN},
	{"APPS", KEYCODE_APPS},
	{"NUMPAD0", KEYCODE_NUMPAD0},
	{"NUMPAD1", KEYCODE_NUMPAD1},
	{"NUMPAD2", KEYCODE_NUMPAD2},
	{"NUMPAD3", KEYCODE_NUMPAD3},
	{"NUMPAD4", KEYCODE_NUMPAD4},
	{"NUMPAD5", KEYCODE_NUMPAD5},
	{"NUMPAD6", KEYCODE_NUMPAD6},
	{"NUMPAD7", KEYCODE_NUMPAD7},
	{"NUMPAD8", KEYCODE_NUMPAD8},
	{"NUMPAD9", KEYCODE_NUMPAD9},
	{"MULTIPLY", KEYCODE_MULTIPLY},
	{"Keypad +", KEYCODE_ADD},
	{"Keypad |", KEYCODE_SEPARATOR},
	{"Keypad -", KEYCODE_SUBTRACT},
	{"Keypad .", KEYCODE_DECIMAL},
	{"Keypad /", KEYCODE_DIVIDE},
	{"F1", KEYCODE_F1},
	{"F2", KEYCODE_F2},
	{"F3", KEYCODE_F3},
	{"F4", KEYCODE_F4},
	{"F5", KEYCODE_F5},
	{"F6", KEYCODE_F6},
	{"F7", KEYCODE_F7},
	{"F8", KEYCODE_F8},
	{"F9", KEYCODE_F9},
	{"F10", KEYCODE_F10},
	{"F11", KEYCODE_F11},
	{"F12", KEYCODE_F12},
	{"F13", KEYCODE_F13},
	{"F14", KEYCODE_F14},
	{"F15", KEYCODE_F15},
	{"F16", KEYCODE_F16},
	{"F17", KEYCODE_F17},
	{"F18", KEYCODE_F18},
	{"F19", KEYCODE_F19},
	{"F20", KEYCODE_F20},
	{"F21", KEYCODE_F21},
	{"F22", KEYCODE_F22},
	{"F23", KEYCODE_F23},
	{"F24", KEYCODE_F24},
	{"NUMLOCK", KEYCODE_NUMLOCK},
	{"SCROLL", KEYCODE_SCROLL},
	{"LEFT ALT", KEYCODE_MENU},
	{"RIGHT ALT", KEYCODE_MENU},
	{"RIGHT SHIFT", KEYCODE_SHIFT},
	{"RIGHT CTRL", KEYCODE_CONTROL}
};


typedef struct
{
	SDL_Keycode mSDLKey;
	KeyCodeSDL mKeyCode;
} KeyNameEntrySDL;

KeyNameEntrySDL aKeyCodeArraySDL[] = { {SDLK_UNKNOWN, KEYCODESDL_UNKNOWN},
								{SDLK_CANCEL, KEYCODESDL_CANCEL},
								{SDLK_BACKSPACE, KEYCODESDL_BACK},
								{SDLK_TAB, KEYCODESDL_TAB},
								{SDLK_CLEAR, KEYCODESDL_CLEAR},
								{SDLK_RETURN, KEYCODESDL_RETURN},
								{SDLK_LSHIFT, KEYCODESDL_SHIFT},
								{SDLK_RSHIFT, KEYCODESDL_SHIFT},
								{SDLK_LCTRL, KEYCODESDL_CONTROL},
								{SDLK_RCTRL, KEYCODESDL_CONTROL},
								{SDLK_MENU, KEYCODESDL_MENU},
								{SDLK_PAUSE, KEYCODESDL_PAUSE},
								{SDLK_CAPSLOCK, KEYCODESDL_CAPITAL},
								{SDLK_ESCAPE, KEYCODESDL_ESCAPE},
								{SDLK_SPACE, KEYCODESDL_SPACE},
								{SDLK_PAGEUP, KEYCODESDL_PAGEUP},
								{SDLK_PAGEDOWN, KEYCODESDL_PAGEDOWN},
								{SDLK_END, KEYCODESDL_END},
								{SDLK_HOME, KEYCODESDL_HOME},
								{SDLK_LEFT, KEYCODESDL_LEFT},
								{SDLK_UP, KEYCODESDL_UP},
								{SDLK_RIGHT, KEYCODESDL_RIGHT},
								{SDLK_DOWN, KEYCODESDL_DOWN},
								{SDLK_SELECT, KEYCODESDL_SELECT},
								{SDLK_EXECUTE, KEYCODESDL_EXECUTE},
								{SDLK_PRINTSCREEN, KEYCODESDL_SNAPSHOT},
								{SDLK_INSERT, KEYCODESDL_INSERT},
								{SDLK_DELETE, KEYCODESDL_DELETE},
								{SDLK_HELP, KEYCODESDL_HELP},
								{SDLK_LGUI, KEYCODESDL_LWIN},
								{SDLK_RGUI, KEYCODESDL_RWIN},
								{SDLK_APPLICATION, KEYCODESDL_APPS},
								{SDLK_KP_0, KEYCODESDL_NUMPAD0},
								{SDLK_KP_1, KEYCODESDL_NUMPAD1},
								{SDLK_KP_2, KEYCODESDL_NUMPAD2},
								{SDLK_KP_3, KEYCODESDL_NUMPAD3},
								{SDLK_KP_4, KEYCODESDL_NUMPAD4},
								{SDLK_KP_5, KEYCODESDL_NUMPAD5},
								{SDLK_KP_6, KEYCODESDL_NUMPAD6},
								{SDLK_KP_7, KEYCODESDL_NUMPAD7},
								{SDLK_KP_8, KEYCODESDL_NUMPAD8},
								{SDLK_KP_9, KEYCODESDL_NUMPAD9},
								{SDLK_KP_MULTIPLY, KEYCODESDL_MULTIPLY},
								{SDLK_KP_PLUS, KEYCODESDL_ADD},
								{SDLK_KP_DECIMAL, KEYCODESDL_SEPARATOR},
								{SDLK_KP_MINUS, KEYCODESDL_SUBTRACT},
								{SDLK_KP_DECIMAL, KEYCODESDL_DECIMAL},
								{SDLK_KP_DIVIDE, KEYCODESDL_DIVIDE},
								{SDLK_F1, KEYCODESDL_F1},
								{SDLK_F2, KEYCODESDL_F2},
								{SDLK_F3, KEYCODESDL_F3},
								{SDLK_F4, KEYCODESDL_F4},
								{SDLK_F5, KEYCODESDL_F5},
								{SDLK_F6, KEYCODESDL_F6},
								{SDLK_F7, KEYCODESDL_F7},
								{SDLK_F8, KEYCODESDL_F8},
								{SDLK_F9, KEYCODESDL_F9},
								{SDLK_F10, KEYCODESDL_F10},
								{SDLK_F11, KEYCODESDL_F11},
								{SDLK_F12, KEYCODESDL_F12},
								{SDLK_F13, KEYCODESDL_F13},
								{SDLK_F14, KEYCODESDL_F14},
								{SDLK_F15, KEYCODESDL_F15},
								{SDLK_F16, KEYCODESDL_F16},
								{SDLK_F17, KEYCODESDL_F17},
								{SDLK_F18, KEYCODESDL_F18},
								{SDLK_F19, KEYCODESDL_F19},
								{SDLK_F20, KEYCODESDL_F20},
								{SDLK_F21, KEYCODESDL_F21},
								{SDLK_F22, KEYCODESDL_F22},
								{SDLK_F23, KEYCODESDL_F23},
								{SDLK_F24, KEYCODESDL_F24},
								{SDLK_NUMLOCKCLEAR, KEYCODESDL_NUMLOCK},
								{SDLK_SCROLLLOCK, KEYCODESDL_SCROLL},
								{SDLK_LALT, KEYCODESDL_LALT},
								{SDLK_RALT, KEYCODESDL_RALT},
								{SDLK_RSHIFT, KEYCODESDL_RSHIFT},
								{SDLK_RCTRL, KEYCODESDL_RCTRL},
};

KeyCode Sexy::GetKeyCodeFromCodeSDL(const SDL_Keycode key)
{
	return GetKeyCodeFromNameSDL(SDL_GetKeyName(key));
}

KeyCode Sexy::GetKeyCodeFromNameSDL(const std::string& theKeyName)
{
	if (theKeyName.length() >= MAX_KEYNAME_LEN - 1)
		return KEYCODE_UNKNOWN;

	if (theKeyName.length() == 1)
	{
		unsigned char aKeyNameChar = theKeyName[0];

		if ((aKeyNameChar >= KEYCODESDL_ASCIIBEGIN) && (aKeyNameChar <= KEYCODESDL_ASCIIEND))
			return KeyCodeSDLToKeyCode((KeyCodeSDL)aKeyNameChar);
	}

	for (int i = 0; i < sizeof(aKeyCodeArraySDL) / sizeof(aKeyCodeArraySDL[0]); i++)
	{
		std::string keyName = SDL_GetKeyName(aKeyCodeArraySDL[i].mSDLKey);
		if (strcmpi(theKeyName.c_str(), keyName.c_str()) == 0)
			return KeyCodeSDLToKeyCode(aKeyCodeArraySDL[i].mKeyCode);
	}

	return KEYCODE_UNKNOWN;
}

KeyCode Sexy::KeyCodeSDLToKeyCode(KeyCodeSDL theKeyCode) {
	if (((KeyCode)theKeyCode >= KEYCODE_ASCIIBEGIN) && ((KeyCode)theKeyCode <= KEYCODE_ASCIIEND))
    {
        return (KeyCode)theKeyCode;
    }
	if (((KeyCode)theKeyCode >= 0x5a) && ((KeyCode)theKeyCode <= 0x7a))
	{
		return (KeyCode)((KeyCode)theKeyCode + KEYCODE_ASCIIBEGIN2);
	}

    for (int i = 0; i < sizeof(aKeyCodeArraySDL) / sizeof(aKeyCodeArraySDL[0]); i++)
    {
        if (aKeyCodeArraySDL[i].mKeyCode == theKeyCode)
        {
            const char* sdlName = SDL_GetKeyName(aKeyCodeArraySDL[i].mSDLKey);
            return GetKeyCodeFromName(sdlName);
        }
    }

    return KEYCODE_UNKNOWN;
}

KeyCode	Sexy::GetKeyCodeFromName(const std::string& theKeyName)
{
	char aKeyName[MAX_KEYNAME_LEN];

	if (theKeyName.length() >= MAX_KEYNAME_LEN-1 || theKeyName.empty())
		return KEYCODE_UNKNOWN;

	strcpy(aKeyName, theKeyName.c_str());
	strupr(aKeyName);

	if (theKeyName.length() == 1)
	{
		unsigned char aKeyNameChar = aKeyName[0];

		if ((aKeyNameChar >= (unsigned char) KEYCODE_ASCIIBEGIN) && (aKeyNameChar <= (unsigned char) KEYCODE_ASCIIEND))
			return (KeyCode) aKeyNameChar;

		if ((aKeyNameChar >= ((unsigned char) KEYCODE_ASCIIBEGIN2) - 0x80) && (aKeyNameChar <= ((unsigned char) KEYCODE_ASCIIEND2) - 0x80))
			return (KeyCode) (aKeyNameChar + 0x80);
	}	

	for (int i = 0; i < sizeof(aKeyCodeArray)/sizeof(aKeyCodeArray[0]); i++)	
		if (strcmpi(aKeyName, aKeyCodeArray[i].mKeyName) == 0)
			return aKeyCodeArray[i].mKeyCode;	

	return KEYCODE_UNKNOWN;
}

const std::string Sexy::GetKeyNameFromCode(const KeyCode& theKeyCode)
{
	if ((theKeyCode >= KEYCODE_ASCIIBEGIN) && (theKeyCode <= KEYCODE_ASCIIEND))
	{
		char aStr[2] = {(char) theKeyCode, 0};
		return aStr;
	}

	if ((theKeyCode >= KEYCODE_ASCIIBEGIN2) && (theKeyCode <= KEYCODE_ASCIIEND2))
	{
		char aStr[2] = {((unsigned char) theKeyCode) - 0x80, 0};
		return aStr;
	}

	for (int i = 0; i < sizeof(aKeyCodeArray)/sizeof(aKeyCodeArray[0]); i++)	
		if (theKeyCode == aKeyCodeArray[i].mKeyCode)
			return aKeyCodeArray[i].mKeyName;	

	return "UNKNOWN";
}