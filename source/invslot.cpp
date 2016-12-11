#include "invslot.h"

Invslot::Invslot(int _oamId, Item _item, MathVector2D<int> _position) {
	this->oamId = _oamId;
	this->item = _item;
	this->position = _position;
	// Check item icon and display it and move self
	this->gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_16Color);

	// Check for item icon and copy it
	dmaCopyHalfWords(3, this->item.tile_src, this->gfx_mem, this->item.tile_len);
	dmaCopyHalfWords(3, this->item.pal_src, &SPRITE_PALETTE_SUB[this->oamId * 16], this->item.pal_len);

	// Set the oam
	oamSet(&oamSub,
		this->oamId,
		this->position.x,
		this->position.y,
		0,
		this->oamId,
		SpriteSize_32x32,
		SpriteColorFormat_16Color,
		this->gfx_mem,
		-1,
		false,
		false,
		false, false,
		false);

	swiWaitForVBlank();
	oamUpdate(&oamSub);
}

void Invslot::Suicide() {
	sassert(false, "Invslot::Suicide() is not yet implemented");
}

void Invslot::Update(Item _item, MathVector2D<int> _position) {
	this->item = _item;
	this->position = _position;
	// Move sprite
	oamSetXY(&oamSub, this->oamId, this->position.x, this->position.y);
	// Copy new image source to gfx
	dmaCopyHalfWords(3, this->item.tile_src, this->gfx_mem, this->item.tile_len);
	dmaCopyHalfWords(3, this->item.pal_src, &SPRITE_PALETTE[this->oamId * 16], this->item.pal_len);
}

void Invslot::Update(Item _item) {
	this->item = _item; 
	// Copy new image source to gfx
	dmaCopyHalfWords(3, this->item.tile_src, this->gfx_mem, this->item.tile_len);
	dmaCopyHalfWords(3, this->item.pal_src, &SPRITE_PALETTE[this->oamId * 16], this->item.pal_len);
}

void Invslot::Update(MathVector2D<int> _position) {
	this->position = _position;
	// Move sprite
	oamSetXY(&oamSub, this->oamId, this->position.x, this->position.y);
}

void Invslot::Update() {
	// Move sprite
	oamSetXY(&oamSub, this->oamId, this->position.x, this->position.y);
	// Copy new image source to gfx
	dmaCopyHalfWords(3, this->item.tile_src, this->gfx_mem, this->item.tile_len);
	dmaCopyHalfWords(3, this->item.pal_src, &SPRITE_PALETTE[this->oamId * 16], this->item.pal_len);
}
