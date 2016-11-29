// Include main header
#include "main.h"
#define NAME_ENTRY_MAX_LEN 16

// Variables to store touch positions
touchPosition touch;
int16 touchX, touchY;

PrintConsole* pcSub;
PrintConsole* pcMain; 

int nameEntryCurLen = 0;
bool nameEntryDone = false;
char nameEntry[NAME_ENTRY_MAX_LEN];

u32 inGameTime = 0;

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
			BgType_Bmp16,		// 16 colour bitmap
			BgSize_B16_256x256,	// Max size is bigger than screen
			2,			// Map base (16k offset)
			0);			// Tile base (unused 16k offset)

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
	REG_BG3Y = 2;				// Because the map base is 2, this should be 2
       	
	// SUBMARK: Init Sub Screen Background 3
	int bg3sub = bgInitSub(3,		// Layer (or priority) 3
			BgType_Bmp16,		// 16 colour bitmap
			BgSize_B16_256x256,
			2,			// Map base (16k offset)
			0);			// Tile base (unused 16k offset)

	REG_BG3PA_SUB = 1 << 8;
	REG_BG3PB_SUB = 0;
	REG_BG3PC_SUB = 0;
	REG_BG3PD_SUB = 1 << 8;
	
	REG_BG3X_SUB = 0;
	REG_BG3Y_SUB = 2;

	bgUpdate();

	// SUBMARK: Display Main Screen Background 3
	/* * * * * * * * * * * * * * * * * * * * * * *
	 * Use the direct memory access (DMA) copy   *
	 * half words function. This function copies *
	 * the the 2nd arg to the 3rd arg, and cuts  *
	 * the data off to a half word (2 bytes).    *
	 * * * * * * * * * * * * * * * * * * * * * * */
	dmaCopyHalfWords(3,				// Use DMA channel 3, the lowest priority one
			mmMainScreenBitmap,		// Variable generated by grit
			bgGetGfxPtr(bg3),		// Address for main background 3
			mmMainScreenBitmapLen);		// Length in bytes generated by grit

	// SUBMARK: Display Sub Screen Background 3
	dmaCopyHalfWords(3,
			mmSubScreenBitmap,
			bgGetGfxPtr(bg3sub),
			mmSubScreenBitmapLen);

	// SUBMARK: Setup Sprites and Interaction
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	// Initilaise a new splash
	Splash touchSplash(0);

	// Variables to store touches
	touchPosition touch;
	MathVector2D<int> tPos;
	int16 sTouchX, sTouchY;

	bool tBreak=false;
	while(tBreak==false) {				// Wait for input
		// Update clock
		// showClock(true, &topScreen);
		// Read the button states
		scanKeys();

		// If the screen was touched
		if(keysDown() & KEY_TOUCH) {
			touchRead(&touch);
			sTouchX = touch.px;		// Save X coord
			sTouchY = touch.py;		// Save Y coord
			mmEffectEx(&buttonpush);	// Play button push sound effect
			tBreak=true;			// Exit next loop
		}
	}
	tPos.x = sTouchX;
	tPos.y = sTouchY;
	touchSplash.Animate(tPos, 2);			// Loop splash animation two times

	// SUBMARK: Have a button because we can... but we couldnt make the button say anything... because we cant
	MathVector2D<int> b1Pos;
	b1Pos.x = 128;
	b1Pos.y = 96;
	MathVector2D<float> b1Sca;
	b1Pos.x = 1.0; 
	b1Pos.y = 1.0;

	Button startB(1,				// oamId
			1,				// Affine Tranform ID
			b1Pos,				// Position
			b1Sca);				// Scale
	swiWaitForVBlank();
	oamUpdate(&oamMain);

	// SUBMARK: Wait
	bool start = false;
	touchPosition atouch;
	while(start == false) {
		scanKeys();
		if(keysDown() && KEY_TOUCH) {
			touchRead(&atouch);
			tPos.x = atouch.px;
			tPos.y = atouch.py;
			touchSplash.Animate(tPos, 1);
			start = startB.CheckTouch(atouch);	// Clean this up to accept MathVector2D<int> rather than touchPosition
		}
	}

	// Destroy 2D sprites (splash will be recreated later)
	startB.Suicide();
	touchSplash.Suicide();

	// Update screen
	swiWaitForVBlank();
	oamUpdate(&oamMain);

	// Scale the main screen background to fit keyboard
	bgHide(bg3);
	swiWaitForVBlank();
	bgUpdate();

	// Change top screen to blank parchament
	dmaCopyHalfWords(3,				// Use DMA channel 3
			mmMainScreenBitmap,		// Variable generated by grit
			bgGetGfxPtr(bg3sub),		// Address for main background 3
			mmMainScreenBitmapLen);		// Length in bytes generated by grit
	
	// SUBMARK: Get the title
	consoleSelect(pcMain);
	consoleInit(pcMain, 0, BgType_Text4bpp, BgSize_T_256x256, 7, 3, true, true);

	consoleSelect(pcSub);
	consoleInit(pcSub,			// Initialise the subscreen printconsole
			0,			// Background layer 0
			BgType_Text4bpp,	// Background type
			BgSize_T_256x256,	// Background size for mem bank allocation
			1,			// Map base
			0,			// Tile base
			false,			// On subscreen
			true);			// Load graphics

	iprintf("Please input desired name or name used in previous save");
	consoleSelect(pcMain);

	// Create the keyboard
	Keyboard* kb = keyboardInit(NULL,
			1,						// Place above background, which is layer 3, so this is layer 2
			BgType_Text4bpp,				// 4bpp tiled text background
			BgSize_T_256x256,				// Full screen max size
			1,						// Map base
			1,						// Tile base
			true,						// On main display
			true);						// Load graphics

	kb->OnKeyReleased = keyPress;					// Set the on key released action
	swiWaitForVBlank();						// Wait until changes take place or weird stuff will show up

	keyboardShow();
	// Get a name for save file
	getSaveName();
	// Hide keyboard
	keyboardHide();
	// Turn on all (previously just 2D was on)
	powerOn(POWER_ALL);
	// Change memory buffer mapping
	initVideo(2);
	startGame(nameEntry);
}

void startGame(const char* save) {
	// Create new or load save file
	SaveData saveFile(save);
	
	initGL();
	// Start time system
	//timerStart(0,				// Timer 0
	//		ClockDivider_1024,	// 327,284.98 ticks per second
	//		327285,			// About one overflow per second
	//		incrementTime);	// Increment timer
	
	sassert(true == false, "Worked, just this is all");
}

// MARK: Increment the time
void incrementTime() {
	if(inGameTime == 4294967294) {
		inGameTime = 0;
	} else {
		inGameTime++;
	}
	updateGameTime();
}

// MARK: Update "sun" position
void updateGameTime() {
	if((inGameTime >= 0) && (inGameTime <= 2147483647)) {
		int mapAngle = pi*(inGameTime/2147483647);
		float mapAngleCos = -1.0f * cos(mapAngle);
		float mapAngleSin = -1.0f * sin(mapAngle);
		// Update the sun light
		glLight(0,
			RGB15(31,31,31),	// 31 is max with 5 bits
			floattov10(0.0f),	// X component is always 0
			floattov10(-1.0f * mapAngleCos),
			floattov10(-1.0f * mapAngleSin));
	} else {
		glLight(0,
			RGB15(0,0,0),
			floattov10(0.0f),floattov10(0.0f),floattov10(0.0f));
	}
}

// MARK: Get pressed key from name keyboard into char nameEntry[16]
void keyPress(int c) {
	consoleSelect(pcMain);
	switch(c) {
		case NOKEY:			// Null char
			break;
		case DVK_BACKSPACE:		// Backspace
			nameEntryCurLen--;
			nameEntry[nameEntryCurLen] = 0;
			consoleClear();
			break;
		case DVK_ENTER:			// Entre
			nameEntryDone = true;
			break;
		case DVK_TAB:			// Kinda like entre
			nameEntryDone = true;
			break;
		default:
			if(nameEntryCurLen < NAME_ENTRY_MAX_LEN) {
				nameEntry[nameEntryCurLen] = c;
				nameEntryCurLen++;
			} else {
				nameEntryCurLen--;
				nameEntry[nameEntryCurLen] = c;
			}
	}
	consoleClear();
	iprintf("%s",&nameEntry);
}

// MARK: Useless Function which should be integrated into main code later
void getSaveName() {
	while(nameEntryDone == false) {
		keyboardUpdate();
		swiWaitForVBlank();
	}
}
