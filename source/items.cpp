#include "items.h"

Item::Item(unsigned int _stat, Type _type, unsigned short _ID) {
	// Set item properties
	switch(_type) {
		case CONTACT:
			break;
		case RANGED:
			break;
		case NOVA:
			break;
		case COMPRESSION:
			this->damage = _stat;
			break;
		case H_RECOVERY:
			break;
		case A_RECOVERY:
			this->recovery = _stat;
			break;
		case H_UNRECOV:
			break;
		case A_UNRECOV:
			this->unrecov = _stat;
			break;
	}
	this->type = _type;
	this->ID = _ID;
}

void Item::putInOam(const void* _img_src, void* _pal_src, uint32 _tile_len, uint32 _pal_len, int _oamId) {
	this->tile_src = &_img_src;	// Because a const anything in a class is the same for all class members, use a pointer to the const void pointer instead
	this->pal_src = _pal_src;

	this->gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
	this->tile_len = _tile_len;
	this->pal_len = _pal_len;

	this->oamId = _oamId;
	
	dmaCopyHalfWords(3, &(this->tile_src), this->gfx_mem, this->tile_len);
	dmaCopyHalfWords(3, this->pal_src, &SPRITE_PALETTE[this->oamId * 16], this->pal_len);
}

// MARK: Setup Items 

// SUBMARK: Basic Sword (id 1)
const Item bsSword(1, CONTACT, 1);	// Really, its worse than flinging bs as a bioweapon at your enemy...

// SUBMARK: Apple (id 2)
const Item apple(10, H_RECOVERY, 2);	// Decent health recovery

// SUBMARK: Mysterious Drink (id 3)
const Item mysDrink(75, H_UNRECOV, 3);

// SUBMARK: Stabby Knife (id 4)
const Item stabbyKnife(5, CONTACT, 4);

// SUBMARK: Infinite Bow (id 5) (only infinite until I decide to make it have an ammo system, but it doesnt even display yet so it doesnt matter)
const Item infiniteBow(3, RANGED, 5); 
