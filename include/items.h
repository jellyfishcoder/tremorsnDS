#include <nds/ndstypes.h>
#include <map>
#include "types.h" 

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
	private:
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
		
		void* pal_src;
		uint32 pal_len;
		
		u16* gfx_mem;
		u8* frame_gfx;


		int oamId;
		void init(const Item & other);
	public:
		Item(unsigned int _stat, Type _type, unsigned short ID);
		void putInOam(const void* _img_src, void* _pal_src, uint32 _tile_len, uint32 _pal_len, int _oamId);
		void putInInv(MathVector2D<unsigned short> _pos);
};

const extern Item bsSword;
const extern Item apple;
const extern Item stabbyKnife;
const extern Item infiniteBow; 
#endif
