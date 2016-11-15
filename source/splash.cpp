#include <nds.h>
#include <math.h>

#include "splash.h"

// Basic Object Initialiser
Splash::Splash(int _oamId) {

	this->position.x = (int)0;				// Set the X position, making sure it is an int or really bad things happen
	this->position.y = (int)0;				// Set the Y position, making sure it is an int or really bad things happen

	this->oamId = _oamId;					// Set the oamId, so we can modify the object later and have it suicide

	this->gfx_mem = oamAllocateGfx(&oamMain,			// Allocate graphics memory
		       	SpriteSize_32x32,			// Size, in this->case it is exact, but sometimes it may have to be next largest option
			SpriteColorFormat_256Color);		// Color format, if it is under 256 it looks very strange in this->case
	this->frame_gfx = (u8*)animatedSplashTiles;		// Im not sure exactly what this is for yet... I believe it is to tell where the gfx memory for a specific frame is, but I thought they were in the same place, maybe an offset of some sort... got it from the tut

	// Copy palette for 256 color
	dmaCopy(animatedSplashPal, SPRITE_PALETTE, 512);

	oamSet(&oamMain,					// Will always be on touch screen
		       	this->oamId,				// oamId
			this->position.x,			// X Coords
			this->position.y,			// Y Coords
			0,					// Priority
			0,					// Palette Alpha
			SpriteSize_32x32,			// Size
			SpriteColorFormat_256Color,		// Color format
			this->gfx_mem,				// Graphics memory
			-1,					// No rotation
			false,					// Not doubled
			false,					// Hide sprite until animation
			false, false,				// Dont flip sprite V or H
			false);					// Dont use mosaic
	swiWaitForVBlank();
	oamUpdate(&oamMain); 
}

// MARK: Animate (Put sprite at _position and loop full animation _times)
void Splash::Animate(MathVector2D<int> _position, int _times) {
	this->position.x = _position.x;						// X Coords
	this->position.y = _position.y;						// Y Coords

	oamSetXY(&oamMain, this->oamId, this->position.x, this->position.y);	// Move sprite to specified coords before showing it
	oamSetHidden(&oamMain, this->oamId, false);				// Unhide sprite
	
	//swiWaitForVBlank();
	//oamUpdate(&oamMain);							// Update the OAM to move and show sprite
	long startTick;
	long currentTick;

	timerStart(0, ClockDivider_1, 1024, NULL);				// Start timer 0 at 32.7284 ticks a millasec, and
	for(int i = 0; i <= _times; i++) {
		for(this->row = 0; this -> row < TOTAL_ROWS; this->row++) {
			for(this->column = 0; this->column < COLUMNS_PER_ROW; this->column++) {
				startTick = timerTick(0);
				// Copy frame to gfx memory on demand
				u8* offset = this->frame_gfx + this->column * 32*32 + this->row * COLUMNS_PER_ROW * 32*32;
				dmaCopy(offset, this->gfx_mem, 32*32);

				swiWaitForVBlank();
				oamUpdate(&oamMain);
				currentTick = timerTick(0);
				while(currentTick - startTick >= 128)  {		// 10 ms wait between frames
					// Pass time
					currentTick = timerTick(0);
				}
			}
		}
	}
	timerStop(0);
	oamSetHidden(&oamMain, this->oamId, true);				// Go back in your hiding hold
}


void Splash::Suicide() {
	oamFreeGfx(&oamMain, gfx_mem);	// Free the gfx memory allocated with oamAllocateGfx
	delete this;			// Very dangerous... Object suicide is never the answer according to all the C++ forums, but... it seems to work 1 out of 34 times
}
