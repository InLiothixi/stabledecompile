#include "LawnApp.h"
#include "Resources.h"
#include "Sexy.TodLib/TodStringFile.h"

using namespace Sexy;

bool (*gAppCloseRequest)();				//[0x69E6A0]
bool (*gAppHasUsedCheatKeys)();			//[0x69E6A4]
SexyString (*gGetCurrentLevelName)();

//#include <ShellScalingApi.h>

//0x44E8F0
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	gHInstance = hInstance;

#ifdef _DEBUG
	/*AllocConsole();

	FILE* dummy;
	freopen_s(&dummy, "CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen_s(&dummy, "CONOUT$", "w", stderr);*/
#endif

	TodStringListSetColors(gLawnStringFormats, gLawnStringFormatCount);
	gGetCurrentLevelName = LawnGetCurrentLevelName;
	gAppCloseRequest = LawnGetCloseRequest;
	gAppHasUsedCheatKeys = LawnHasUsedCheatKeys;

	gLawnApp = new LawnApp();
	gLawnApp->mChangeDirTo = (!Sexy::FileExists(_S("properties\\resources.xml")) && Sexy::FileExists(_S("..\\properties\\resources.xml"))) ? _S("..") : _S(".");
	
	gLawnApp->Init();
	gLawnApp->Start();
	gLawnApp->Shutdown();
	if (gLawnApp)
		delete gLawnApp;

	return 0;
};