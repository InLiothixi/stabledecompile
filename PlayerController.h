#ifndef __PLAYERCONTROLLER_H__
#define __PLAYERCONTROLLER_H__

// @InLiothixie implemented
enum ControllerType {
	CONTROLLER_NONE = -1,
	CONTROLLER_MOUSE = 0,
	CONTROLLER_KEYBOARD = 1,
};

class PlayerController {
public:
	ControllerType mControllerType;

	unsigned char mKeyPause;
	unsigned char mKeyMenu;

	//Exclusive Player Controlls
	unsigned char mKeyJoyLeftButton; // Snaps 1 tile each move
	unsigned char mKeyJoyUpButton; //
	unsigned char mKeyJoyDownButton; // 
	unsigned char mKeyJoyRightButton; //

	unsigned char mKeyAButton; // Confirm
	unsigned char mKeyBButton; // Cancel or Shovel
	unsigned char mKeyXButton; // Butter or Mallet in Whack a Zombie
	unsigned char mKeyYButton; // Initiate Buttons like Last Stand

	unsigned char mKeyLBumperButton; // Select Seedpackets to the Left
	unsigned char mKeyRBumperButton; // Select Seedpackets to the Right

	unsigned char mKeyStartButton;

	//Exclusive Mouse Controlls
	unsigned char mKeySeedSlot1; // Traverse Seedpackets 1-10
	unsigned char mKeySeedSlot2;
	unsigned char mKeySeedSlot3;
	unsigned char mKeySeedSlot4;
	unsigned char mKeySeedSlot5;
	unsigned char mKeySeedSlot6;
	unsigned char mKeySeedSlot7;
	unsigned char mKeySeedSlot8;
	unsigned char mKeySeedSlot9;
	unsigned char mKeySeedSlot10;
	unsigned char mKeyShovel;	// Use Shovel

public:
	PlayerController();
};
#endif
