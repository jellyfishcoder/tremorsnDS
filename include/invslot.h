#ifndef INVSLOT_H
#define INVSLOT_H

#include <nds.h>
#include "types.h"
#include "inits.h"
#include "items.h"

class Invslot {
	private:
		MathVector2D<int> position;
		u16* gfx_mem;
		u8* frame_gfx;
		int oamId;
		Item item;
		void init(const Invslot & other);
	public:
		Invslot(int _oamId, Item _item, MathVector2D<int> _position);
		void Suicide();
		// Three ways to update depending on what needs to be updated, and a forth for good measure
		void Update(Item _item, MathVector2D<int> _position);
		void Update(Item _item);
		void Update(MathVector2D<int> _position);
		void Update();
};

#endif
