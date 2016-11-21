#ifndef SPRITE_H
#define SPRITE_H

#include <nds.h>
//#include "splash.h"

#define NUM_SPRITES 128

typedef struct {
	int x,y;		// Screen coords
	int dx, dy;		// Velocity
	SpriteEntry* oam;	// Pointer to the sprite attribs in the OAM
	int gfxID;		// Graphics coords
}Sprite;

#endif
