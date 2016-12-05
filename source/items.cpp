#include "items.h"

Item::Item(unsigned int _stat, Type _type, const void* _img_src, uint32 _tile_len, void* pal_src, uint32 _pal_len) {
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

	this->tile_src = &_img_src;
	this->tile_len = _tile_len;
	
	this->pal_src = _pal_src;
	this->pal_len = _pal_len;
}

Item::Item() {
}

// MARK: Setup Items 

// SUBMARK: Basic Sword (id 1)
const Item bsSword(1, CONTACT, bsSwordTiles, bsSwordTilesLen, bsSwordPal, bsSwordPalLen, 1);	// Really, its worse than flinging bs as a bioweapon at your enemy...

// SUBMARK: Apple (id 2)
const Item apple(10, H_RECOVERY, appleTiles, appleTilesLen, applePal, applePalLen, 2);	// Decent health recovery

// SUBMARK: Mysterious Drink (id 3)
const Item mysDrink(75, H_UNRECOV, mysDrinkTiles, mysDrinkTilesLen, mysDrinkPal, mysDrinkPalLen, 3);

// SUBMARK: Stabby Knife (id 4)
const Item stabbyKnife(5, CONTACT, stabbyKnifeTiles, stabbyKnifeTilesLen, stabbyKnifePal, stabbyKnifePalLen, 4);

// SUBMARK: Infinite Bow (id 5) (only infinite until I decide to make it have an ammo system, but it doesnt even display yet so it doesnt matter)
const Item infiniteBow(3, RANGED, 5); 
