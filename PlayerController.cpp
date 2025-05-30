#include "PlayerController.h"
#include "SexyAppFramework/KeyCodes.h"

PlayerController::PlayerController() {
	mControllerType = ControllerType::CONTROLLER_NONE;
	mKeyPause = Sexy::KEYCODE_SPACE;
	mKeyMenu = Sexy::KEYCODE_RETURN;
	mKeyJoyLeftButton = Sexy::KEYCODE_LEFT;
	mKeyJoyUpButton = Sexy::KEYCODE_UP;
	mKeyJoyDownButton = Sexy::KEYCODE_DOWN;
	mKeyJoyRightButton = Sexy::KEYCODE_RIGHT;
	mKeyAButton = Sexy::GetKeyCodeFromName("z");
	mKeyBButton = Sexy::GetKeyCodeFromName("x");
	mKeyXButton = Sexy::GetKeyCodeFromName("c");
	mKeyYButton = Sexy::GetKeyCodeFromName("y");
	mKeyLBumperButton = Sexy::GetKeyCodeFromName("z");
	mKeyRBumperButton = Sexy::GetKeyCodeFromName("z");
	mKeyStartButton = Sexy::KEYCODE_TAB;
	
	mKeySeedSlot1 = NULL;
	mKeySeedSlot2 = NULL;
	mKeySeedSlot3 = NULL;
	mKeySeedSlot4 = NULL;
	mKeySeedSlot5 = NULL;
	mKeySeedSlot6 = NULL;
	mKeySeedSlot7 = NULL;
	mKeySeedSlot8 = NULL;
	mKeySeedSlot9 = NULL;
	mKeySeedSlot10 = NULL;
	mKeyShovel = NULL;
}