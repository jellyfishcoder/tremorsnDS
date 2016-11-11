/* inits.cpp
 * Contains all initialisers and setup functions
 */

#include "inits.h"

void initVideo(int vidMode) {
	switch(vidMode) {
		// 2D graphics on both screen
		case 1:
			// Setup the memory bank mapping
			vramSetBankA(VRAM_A_MAIN_BG_0x06000000);	// Map bank A to main engine background slot 0
			vramSetBankB(VRAM_B_MAIN_BG_0x06020000);	// Map bank B to main engine background slot 1
			vramSetBankC(VRAM_C_SUB_BG_0x06200000);	// Map bank C to sub engine background slot 0
			// Set the video modes
			videoSetMode(MODE_5_2D);		// Mode 5 will work, but others might also
			videoSetModeSub(MODE_5_2D);
			// Check if it worked, if not die
			sassert(videoGetMode()==5, "Video mode did not properly set main when initVideo(1) was called.");
			sassert(videoGetModeSub()==5, "Video mode did not properly set sub when initVideo(1) was called.");
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
