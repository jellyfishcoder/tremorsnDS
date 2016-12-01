/* inits.cpp
 * Contains all initialisers and setup functions
 */

#include "inits.h"

// MARK: Initialise Video
void initVideo(int vidMode) {
	switch(vidMode) {
		// 2D graphics on both screen
		case 1:
			// Setup the memory bank mapping
			vramSetBankA(VRAM_A_MAIN_SPRITE_0x06400000);	// Map bank A to main sprite graphics slot 0
			vramSetBankB(VRAM_B_MAIN_BG_0x06020000);	// Map bank B to main engine background slot 1
			vramSetBankC(VRAM_C_SUB_BG_0x06200000);		// Map bank C to sub engine background slot 0
			vramSetBankD(VRAM_D_MAIN_BG_0x06000000);	// Map bank D to main engine background slot 2

			// Set the video modes
			videoSetMode(MODE_5_2D |			// Mode 5 will work, but others also might
					DISPLAY_BG2_ACTIVE |		// Enable BG2
					DISPLAY_BG3_ACTIVE 		// Enable BG3
				);
			videoSetModeSub(MODE_5_2D |
					DISPLAY_BG3_ACTIVE
				);
			// Check if it worked, if not die
			sassert(videoGetMode()==MODE_5_2D, "Video mode did not properly set main when initVideo(1) was called.");
			sassert(videoGetModeSub()==MODE_5_2D, "Video mode did not properly set sub when initVideo(1) was called.");
			break;
		// 2D graphics on sub screen, 3D on main screen
		case 2:
			// Setup the memory bank mapping
			vramSetBankA(VRAM_A_TEXTURE_SLOT0);		// Map bank A to 3d texture slot 0
			vramSetBankB(VRAM_B_TEXTURE_SLOT1);		// Map bank B to 3d texture slot 1
			vramSetBankC(VRAM_C_SUB_BG_0x06200000);		// Map bank C to sub engine background slot 0
			vramSetBankD(VRAM_D_SUB_SPRITE);		// Map bank D to sub sprite graphics slot 0
			vramSetBankE(VRAM_E_MAIN_SPRITE);		// Map bank E to main sprite graphics slot 0 first part of first half
			vramSetBankF(VRAM_F_TEX_PALETTE_SLOT0);		// Map bank F to 3d texture palette slot 1
			vramSetBankG(VRAM_G_MAIN_SPRITE_0x06404000);	// Map bank G to main sprite graphics slot 0 second part of first half

			// Set the video modes
			videoSetMode(MODE_0_3D);
			videoSetModeSub(MODE_5_2D |
					DISPLAY_BG3_ACTIVE);
			break;
		/* 2D graphics on both screens with text layer
		case 3:
			vramSetBankA(VRAM_A_MAIN_SPRITE0x06400000);
			vramSetBankB(VRAM_B_MAIN_BG_0x06020000);        // Map bank B to main engine background slot 1
			vramSetBankC(VRAM_C_SUB_BG_0x06200000);         // Map bank C to sub engine background slot 0
			vramSetBankD(VRAM_D_MAIN_BG_0x06000000);        // Map bank D to main engine background slot 0

			// Set the video modes
			videoSetMode(MODE_0_2D |

		*/
		default:
			// Enter options next time...
			break;
	}
}

// MARK: Initialise Soundbank
void initSoundbank(void) {
	mmInitDefaultMem((mm_addr)soundbank_bin);
	// Load Sound Effects
	mmLoadEffect(SFX_BUTTONPUSH);
}

// MARK: Initialise eeprom
void initEeprom() {
	// Give the ARM9 proc access to the nDS cartridge
	sysSetBusOwners(true, true);
	// SUBMARK: Verify the cartridge is not encrypted
	static u8 cartCheck1[512];
	static u8 cartCheck2[512];
	cardReadHeader(cartCheck1);
	cardReadHeader(cartCheck2);
	sassert(memcmp(cartCheck1, cartCheck2, 32) == 0, "nDS Cartridge Encrypted, EEPROM Memory Unaccessable.");
}

// MARK: Initialise Map
void initMap(int mapNum) {
	switch(mapNum) {
		case 1:
			// Load initial level
			break;
		default:
			break;
	}
}

// MARK: Initialise GL
void initGL() {
	glInit();			// Initialise GL
	
	glEnable(GL_ANTIALIAS);		// Enable antialiasing
	glClearColor(0, 0, 0, 31);	// Opaque background so antialiasing works
	glClearPolyID(63);		// Unique background polyID so antialiasing works
	glClearDepth(0x7FFF);

	glViewport(0, 0, 255, 191);	// Take up whole screen

	glSetToonTableRange(0, 15, RGB15(8, 8, 8));		// First half lighting
	glSetToonTableRange(16, 31, RGB15(24, 24, 24));		// Second half lighting

	glMatrixMode(GL_PROJECTION);	// Set the projection matrix
	glLoadIdentity();
	gluPerspective(70,		// Vertical field of view (-32768 to 32767)
			256/192,	// Aspect ratio
			0.1,		// Near mask
			40);		// Far mask

	glLight(0, RGB15(16,16,16) , 0, floattov10(-1.0), 0);
	glLight(1, RGB15(16,16,16), floattov10(-1.0), 0, 0);

	gluLookAt(0.0, 0.0, -3.0,		// Camera position
			0.0, 0.0, 0.0,		// Look at
			0.0, -1.0, 0.0);	// Up
}

// MARK: Initialise Items
void initItems() {
	// SUBMARK: Basic Sword (id 1)
	Stat bsSwordStat;
	bsSwordStat.damage = 1;			// Really, its worse than flinging bs as a bioweapon at your enemy...
	Item bsSword(bsSwordStat, CONTACT, 1);
	// SUBMARK: Apple (id 2)
	Stat appleStat;
	appleStat.recovery = 10;		// Recovers 1/10 of starting health, decent but not too OP
	Item apple(appleStat, H_RECOVERY, 2);
	// SUBMARK: Mysterious Drink (id 3)
	Stat mysDrinkStat;
	mysDrinkStat.recovery = -75;		// What type of idiot drinks a mysterious drink in a clearly labeled bottle marked poisen
	Item mysDrink(mysDrinkStat, H_RECOVERY, 3);
	// SUBMARK: Stabby Knife (id 4)
	Stat stabbyKnifeStat;
	stabbyKnifeStat.damage = 5;		// Its a stabby knife, not a bs sword
	Item stabbyKnife(stabbyKnifeStat, CONTACT, 4);
	// SUBMARK: Infinite Bow (id 5) (only infinite until I decide to make it have an ammo system, but it doesnt even display yet so it doesnt matter)
	Stat infiniteBowStat;
	infiniteBowStat.damage = 3;		// Most basic ranged weapon, other than the hand cannon, which shoots bs in a flinging motion and is not even real
	Item infiniteBow(infiniteBowStat, RANGED, 5);
}
