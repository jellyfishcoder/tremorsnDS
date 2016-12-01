#include "items.h"

Item::Item(Stat _stats, Type _type, unsigned short _ID) {
	// Set item properties
	this->stats = _stats;
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
