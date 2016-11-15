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
			vramSetBankD(VRAM_D_MAIN_BG_0x06000000);	// Map bank D to main engine background slot 0

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
		// 2D graphics on sub screen, 3D on main screen (usefull for cutsceans)
		case 2:
			// Setup the memory bank mapping
			vramSetBankA(VRAM_A_TEXTURE_SLOT0);	// Map bank A to 3d texture slot 0
			vramSetBankB(VRAM_B_TEXTURE_SLOT1);	// Map bank B to 3d texture slot 1
			vramSetBankC(VRAM_C_SUB_BG_0x06200000);	// Map bank C to sub engine background slot 0
			// Set the video modes
			videoSetMode(MODE_0_3D);
			videoSetModeSub(MODE_5_2D);
			break;
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
