#ifndef BUTTON_H
#define BUTTON_H

#include <nds.h>
#include <math.h>
#include "types.h"
#include "parchButton.h"

class Button {
	protected:
		MathVector2D<int> position;	// Position
		u16* gfx_mem;			// Sprite graphics memory pointer
		u8* frame_gfx;			// Frame graphics memory pointer
		int oamId;			// oamId
		int affId;			// affId (for affine transform matrix)
		MathVector2D<int> scale;	// Scale
		void init(const Button & other);
	public:
		Button(int _oamId, int _affId, MathVector2D<int> _position, MathVector2D<int> _scale);
		bool CheckTouch(touchPosition _touch);
		void Suicide();
		void Update();
};

#endif
