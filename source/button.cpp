#include "button.h"

Button::Button(int _oamId, int _affId, MathVector2D<int> _position, MathVector2D<float> _scale) {
	this->position.x = _position.x;		// Set X Coords
	this->position.y = _position.y;		// Set Y Coords
	this->scale.x = _scale.x;		// Set X scale
	this->scale.y = _scale.y;		// Set Y scale
	this->oamId = _oamId;			// Set oamId
	this->affId = _affId;			// Set affId

	// Memory allocation
	this->gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
	this->frame_gfx = (u8*) parchButtonTilesLen;

	dmaCopy(parchButtonPal, SPRITE_PALETTE, 512);
	dmaCopyHalfWords(3, parchButtonTiles, this->gfx_mem, parchButtonTilesLen);

	// Scale the sprite
	oamRotateScale(&oamMain,
			this->affId,		// Affine matrix ID
			0,			// No angular rotation
			//intToFixed(1, 8),
			//intToFixed(1, 8));
			((int)((this->scale.x) * (float)(1 << 8))),	// Create a fixed point x scale value from the float
			((int)((this->scale.y) * (float)(1 << 8))));	// Create a fixed point y scale value from the float

	// Copy palette
	//dmaCopy(parchButtonPal, SPRITE_PALETTE, 512);
	
	oamSet(&oamMain,			// Only on touch screen
		this->oamId,			// oamId
		this->position.x - 32,		// Left corner X position
		this->position.y - 16,		// Left corner Y position
		0,				// Priority 
		0,				// Alpha
		SpriteSize_64x32,		// Size
		SpriteColorFormat_16Color,	// Color
		this->gfx_mem,			// Graphics memory
		this->affId,			// Rotateable
		false,				// Not doubled
		false,				// Not hidden
		false, false,			// Dont flip X or Y
		false);				// Dont use mosaic

	// Wait for VBlank to update the sprite manager
	swiWaitForVBlank();
	oamUpdate(&oamMain);
}

bool Button::CheckTouch(touchPosition _touch) {
	// Save input before touch changes
	int touchx = _touch.px;
	int touchy = _touch.py;
	// Calculate button bounds
	int left = this->position.x - 32;
	int right = this->position.x + 32;// * this->scale.x;
	int up = this->position.y - 16;
	int down = this->position.y + 16;// * this->scale.y;
	
	// If touch is inside the button scale it down
	if((touchx >= left) && (touchx <= right) && (touchy <= down) && (touchy >= up)) {
		/* Temporarily disable button anims
		this->scale.x = this->scale.x/1.5;	// Scale down X axis
		this->scale.y = this->scale.y/1.5;	// Scale down Y axis
		
		this->Update();

		bool timerUp = false;
		while(!timerUp) {
			timerStart(1,				// Use timer 1, timer 0 used in main menu and game for other things
			      	ClockDivider_1024,	// ~32.7283 kHz, so overflow at 16364 cycles for 1/2 a sec
				16364,			// Overflow after 1/2 sec
				timerUp = true);		// Then run pop button up function
		}
		this->Pop();
		*/
		return(true);				// Button was clicked
	} else {
		return(false);				// Button was not clicked
	}
}
/* Temporarily disable button anims
void Button::Pop() {
	timerStop(1);					// Stop timer that started this

	this->scale.x = this->scale.x * 1.5;		// Scale up X axis
	this->scale.y = this->scale.y * 1.5;		// Scale up Y axis

	this->Update();
}*/

void Button::Update() {
	oamRotateScale(&oamMain,					// Main touchscreen
			this->affId,					// Affine matrix ID
			0,						// No rotation
			((int)((this->scale.x) * (float)(1 << 8))),	// Create a fixed point x scale value from the float
			((int)((this->scale.y) * (float)(1 << 8))));	// Create a fixed point y scale value from the float
	
	swiWaitForVBlank();						// Wait for VBlank to update sprite manager
	oamUpdate(&oamMain);						// Update main screen oam
}
