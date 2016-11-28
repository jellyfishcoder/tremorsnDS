#ifndef BUTTON_H
#define BUTTON_H

#include <nds.h>
#include <math.h>
#include "types.h"
#include "parchButton.h"

class Button {
	protected:
		MathVector2D<int> position;	// Upper left corner position
		u16* gfx_mem;			// Sprite graphics memory pointer
		u8* frame_gfx;			// Frame graphics memory pointer
		int oamId;			// oamId
		int affId;			// affId (for affine transform matrix)
		MathVector2D<float> scale;	// Float representation of the scale (automatically changed to 8 bit fixed)
		void init(const Button & other);
	public:
		Button(int _oamId, int _affId, MathVector2D<int> _position, MathVector2D<float> _size);
		bool CheckTouch(touchPosition _touch);
		void Suicide();
		void Update();
};

#endif
