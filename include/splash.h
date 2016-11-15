#ifndef SPLASH_H
#define SPLASH_H

#include <nds.h>
#include <math.h>
#include "types.h"
#include "animatedSplash.h"
#define FRAMES_PER_ANIMATION 4

/*
template <class T>
struct MathVector2D {
	T x;
	T y;
};
*/

class Splash {
	protected:
		MathVector2D<int> position;	// Vector representing X and Y position
		int frame;			// Frame in animation
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
