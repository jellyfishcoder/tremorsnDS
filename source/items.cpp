#include "items.h"

Item::Item(unsigned int _stat, Type _type, const void* _img_src, uint32 _tile_len, const void* _pal_src, uint32 _pal_len) {
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

	this->tile_src = _img_src;
	this->tile_len = _tile_len;
	
	this->pal_src = _pal_src;
	this->pal_len = _pal_len;
}
// Next line required to pass any Item into a function
Item::Item() {}
