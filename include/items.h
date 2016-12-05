#include <nds/ndstypes.h>
#include <map>
#include "types.h" 
#include "invslot.h"
#include "main.h"

#include "lgDuoRod.h"

#ifndef ITEMS_H
#define ITEMS_H 

union Stat {
	unsigned int damage;		// Does damage
	unsigned int armor;
	unsigned int recovery;		// Restores health or armor up to the current max
	unsigned int unrecov;
	unsigned int energy;
	~Stat() {};
};

// Contact damage/protection, Ranged ', Nova ', Compression ', Health Recovery, Armor Recovery
enum Type {CONTACT, RANGED, NOVA, COMPRESSION, H_RECOVERY, H_UNRECOV, A_RECOVERY, A_UNRECOV};

class Item {
	friend class Invslot;

	protected:
		// Because an item can only have damage or defense, a union can be used
		union {
			unsigned int damage;
			unsigned int armor;
			unsigned int recovery;
			unsigned int unrecov;
			unsigned int energy;
		};

		Type type;
		unsigned short ID;
		
		MathVector2D<unsigned short> pos;		// Posistion in inventory

		const void** tile_src;				// Image source for dmaCopyHalfWords()
		uint32 tile_len;
		
		const void** pal_src;
		uint32 pal_len;

		void init(const Item & other);
	public:
		Item(unsigned int _stat, Type _type, const void* _img_src, uint32 _tile_len, const void* _pal_src, uint32 _pal_len);
		Item();						// Needed for stuff
		
};

#endif
