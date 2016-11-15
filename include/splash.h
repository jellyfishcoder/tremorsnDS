#ifndef SPLASH_H
#define SPLASH_H

#include <nds.h>
#include <math.h>
#include "types.h"
#include "animatedSplash.h"

#define COLUMNS_PER_ROW 4
#define TOTAL_ROWS 4 

class Splash {
	protected:
		MathVector2D<int> position;	// Vector representing X and Y position
		int column;			// Column in animation
		int row;			// Row in animation
		u16* gfx_mem;			// Sprite graphics memory pointer
		u8* frame_gfx;			// Frame memory pointer
		int oamId;			// OAM id
		void init(const Splash & other);
	public:
		// Basic initialiser
		Splash(int oamId);
		void Animate(MathVector2D<int> _position, int times);
		void Suicide();
};

#endif
