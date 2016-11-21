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
		void init(const Button & others);
	public:
		// Sadly, the scale must be private because the interupt timer
		// only allows pure void functions, not object::void functions
		// and to allow the void Pop(Button* _this) function to modify
		// the scale of the button and return it to normal, the scale
		// MathVector2D<float> MUST be public. Will try to do this
		// differently in the future, I just dont like public variables
		MathVector2D<float> scale;	// Float representation of the scale (automatically changed to 8 bit fixed)

		Button(int _oamId, int _affId, MathVector2D<int> _position, MathVector2D<float> _size);
		bool CheckTouch(touchPosition _touch);
		void Pop();
		void Update();
};

#endif
