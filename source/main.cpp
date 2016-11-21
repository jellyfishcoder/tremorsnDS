// Include main header
#include "main.h"

// Variables to store touch positions
touchPosition touch;
int16 touchX, touchY;

PrintConsole topScreen;
PrintConsole bottomScreen;

int main(void) {
	// Turn on 2D graphics core
	powerOn(POWER_ALL_2D);
	
	// Place the main screen on the bottom physical screen
	lcdMainOnBottom();

	// Enable sound
	soundEnable();
	initSoundbank();

	// Display the main menu
	mainMenu();
	
	while(1) swiWaitForVBlank();
	return 0;
}

// MARK: Main Menu
void mainMenu(void) {
	// Load sound effects
	mm_sound_effect buttonpush = {
		{ SFX_BUTTONPUSH },		// ID
		0,				// Handle
		255,				// Volume
		255,				// Panning
	};
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
	int bg3 = bgInit(3,			// Layer 3
			BgType_Bmp16,
			BgSize_B16_256x256,
			0,
			0);
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

	/* SUBMARK: Init Window Background 2
	int bg2 = bgInit(2,			// Layer 2
			BgType_Bmp16,
			BgSize_B16_256x256,
			8,			// Offset
			0);			// Tile offset

	*/
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

	oamInit(&oamMain, SpriteMapping_1D_128, false);

	// SUBMARK: Setup Sprites and Interaction	
	// Initilaise a new splash
	Splash touchSplash(0);
	// Variables to store touches
	touchPosition touch;
	int16 sTouchX, sTouchY;

	bool tBreak=false;
	while(tBreak==false) {			// Wait for input
		// Update clock
		// showClock(true, &topScreen);
		// Read the button states
		scanKeys();

		// If the screen was touched
		if(keysDown() & KEY_TOUCH) {
			touchRead(&touch);
			sTouchX = touch.px;	// Save X coord
			sTouchY = touch.py;	// Save Y coord
			mmEffectEx(&buttonpush);// Play button push sound effect
			tBreak=true;		// Exit next loop
		}
	}
	MathVector2D<int> tPos;
	tPos.x = sTouchX;
	tPos.y = sTouchY;
	touchSplash.Animate(tPos, 2);		// Loop splash animation two times

	// SUBMARK: Ask for save slot
	MathVector2D<int> b1Pos;
	b1Pos.x = 128;
	b1Pos.y = 96;
	MathVector2D<float> b1Sca;
	b1Sca.x = 1.0;
	b1Sca.y = 1.0;
	Button startB(1,				// oamId
			1,			// Affine Tranform ID
			b1Pos,			// Position
			b1Sca);			// Scale
	
	swiWaitForVBlank(); oamUpdate(&oamMain);
	bool start = false;
	touchPosition atouch;
	while(start == false) {
		scanKeys();
		if(keysDown() && KEY_TOUCH) {
			touchRead(&atouch);
			start = startB.CheckTouch(atouch);
		}
	}

	// SUBMARK: Input Name and load/create coresponding save
	Keyboard *kbd = keyboardInit(NULL, 3, BgType_Bmp16, BgSize_B16_256x256, 20, 0, true, true);	// Init keyboard
	keyboardShow();

	char entreNm[128];			// Up to 128 chars, thats a long name
	int entreNmI = 0;
	bool finEntreNm = false;		// Not finished entering name yet
	while(!finEntreNm) {
		int key = keyboardUpdate();
		if(key > 0) {
			entreNm[entreNmI] = key;
			consoleClear();
			for(int i = 0; i <= entreNmI; i++) {
				iprintf("%c", entreNm[i]);
			}
		}
		swiWaitForVBlank();
	}
} 
