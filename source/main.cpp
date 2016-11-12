// Include main header
#include "main.h"

touchPosition touch;
PrintConsole topScreen;
PrintConsole bottomScreen;

int main(void) {
	// Turn on 2D graphics core
	powerOn(POWER_ALL_2D);
	
	// Place the main screen on the bottom physical screen
	lcdMainOnBottom();
	// Create font for cClock
	//PrintConsole topScreen;
	//PrintConsole bottomScreen;

	// Display the main menu
	mainMenu();
	while(1) swiWaitForVBlank();
	return 0;
}

// MARK: Main Menu
void mainMenu(void) {
	/* * * * * * * * * * * * * * * * * * * * * *
	 * Set the main screen video mode and the  *
	 * sub screen video mode to have 2 text    *
	 * layers and 2 extended background        *
	 * layers                                  *
	 * * * * * * * * * * * * * * * * * * * * * */
	initVideo(1);
	// SUBMARK: Init Main Screen Background 3
	/* * * * * * * * * * * * * * * * * * * * * *
	 * Set up affine background 3 on the main  *
	 * screen as a 16 bit color bitmap type    *
	 * background with a size of 256x256.      *
	 * * * * * * * * * * * * * * * * * * * * * */
	REG_BG3CNT = BG_BMP16_256x256 |		// Set background type to 16 bit 256x256 bitmap
			BG_BMP_BASE(0) |	// Set the starting place in the memory to store the background
			BG_PRIORITY(3);		// Set the priority to 3 (lower num = higher priority)
	/* * * * * * * * * * * * * * * * * * * * * *
	 * Set up an affine transformation matrix  *
	 * for main bg 3. This matrix will be an   *
	 * identity matrix (diagnal of ones). An   *
	 * affine transformation matrix is used to *
	 * determine how to stretch, move, and     *
	 * rotate/flip the background. Because we  *
	 * do not want our background modified, we *
	 * use an identity matrix, doing nothing.  *
	 * * * * * * * * * * * * * * * * * * * * * */
	REG_BG3PA = 1 << 8;
	REG_BG3PB = 0;
	REG_BG3PC = 0;
	REG_BG3PD = 1 << 8;

	// Place main bg 3 at the origin, which is the upper left corner.
	REG_BG3X = 0;
	REG_BG3Y = 0;
       	
	// SUBMARK: Init Sub Screen Background 3
	REG_BG3CNT_SUB = BG_BMP16_256x256 |
				BG_BMP_BASE(0) |
				BG_PRIORITY(3);
	REG_BG3PA_SUB = 1 << 8;
	REG_BG3PB_SUB = 0;
	REG_BG3PC_SUB = 0;
	REG_BG3PD_SUB = 1 << 8;
	REG_BG3X_SUB = 0;
	REG_BG3Y_SUB = 0;

	// SUBMARK: Display Main Screen Background 3
	/* * * * * * * * * * * * * * * * * * * * * * *
	 * Use the direct memory access (DMA) copy   *
	 * half words function. This function copies *
	 * the the 2nd arg to the 3rd arg, and cuts  *
	 * the data off to a half word (2 bytes).    *
	 * * * * * * * * * * * * * * * * * * * * * * */
	dmaCopyHalfWords(3,				// Use DMA channel 3, the lowest priority one
			mmMainScreenBitmap,		// Variable generated by grit
			(uint16 *)BG_BMP_RAM(0),	// Address for main background 3
			mmMainScreenBitmapLen);		// Length in bytes generated by grit

	// SUBMARK: Display Sub Screen Background 3
	dmaCopyHalfWords(3,
			mmSubScreenBitmap,
			(uint16 *)BG_BMP_RAM_SUB(0),
			mmSubScreenBitmapLen);
	
	// Setup Clock
	consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	bool tBreak=false;
	while(!tBreak) {		// Wait for input
		// Update clock
		// showClock(true, &topScreen);
		
		// Check for input
		scanKeys();
		touchRead(&touch);
		// Save input
		int pressed = keysDown();

		// If a button is pressed
		if(pressed && pressed != KEY_TOUCH) {
			mmEffect(SFX_BUTTON_PUSH);
			tBreak=true;
		}
	}
	sassert(0, "You Won By Causing a Fatal Crash!");
}
