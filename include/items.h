#ifndef ITEMS_H
#define ITEMS_H

#include <nds/ndstypes.h>
#include <map>
#include "types.h"

// Contact damage/protection, Ranged ', Nova ', Compression ', Health Recovery, Armor Recovery
enum Type {CONTACT, RANGED, NOVA, COMPRESSION, H_RECOVERY, A_RECOVERY};

union Stat {
	unsigned int damage;
	unsigned int armor;
	unsigned int recovery;
	unsigned int energy;
	~Stat() {}
};

class Item {
	private:
		// Because an item can only have damage or defense, a union can be used
		Stat stats;
		Type type;
		unsigned short ID;
		
		MathVector2D<unsigned short> pos;		// Posistion in inventory
		
		const void** tile_src;				// Image source for dmaCopyHalfWords()
		uint32 tile_len;
		
		void* pal_src;
		uint32 pal_len;
		
		u16* gfx_mem;
		u8* frame_gfx;


		int oamId;
		void init(const Item & other);
	public:
		Item(Stat _stats, Type _type, unsigned short ID);
		void putInOam(const void* _img_src, void* _pal_src, uint32 _tile_len, uint32 _pal_len, int _oamId);
		void putInInv(MathVector2D<unsigned short> _pos);
};

#endif
