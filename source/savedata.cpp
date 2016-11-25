#include "savedata.h"

SaveData::SaveData(const char* _saveFileName) {
	sassert(nitroFSInit(NULL), "nitroFS failed to initialise when attempting to access the savefile");

	this->saveFileName = &_saveFileName;

	// Open the file in read+update mode (will never over-write)
	this->saveFile = fopen(this->saveFileName,"r+");
	if(saveFile == NULL) {				// fopen returns NULL if the file does not exist for r+ mode
		// Open the file in write+update mode (will always over-write)
		this->saveFile = fopen(this->saveFileName,"w+");
		fclose(this->saveFile);	
		// MARK: New Game
		this->inv = { { 1, 2, 0, 0, 0 },	// Initialise backpack, contains item IDs 1 and 2 which will be a really bad weapon and an apple probably
				{ 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0}};
		this->curItem = MathVector2D<char> { 0, 0};
		this->health = { 100, 100 };		// Start with 100 max health and have all of it
		this->currentMap = 1;			// Start on first map
		this->playerPos = MathVector3D<int32> { floattof32(0.0f), floattof32(1.0f), floattof32(0.0f); };
		// Save the created data
		this->Save;
	} else {

		// MARK: Load
		//this.Load;
	}
}

bool SaveData::Save() {
	// Make sure nitroFS is still initialised
	sassert(nitroFSInit(NULL), "nitroFS failed to initialise when attempting to save data.");
	{
		const char* tempChar = &this->saveFileName;
		std::ofstream tempOfStream(tempChar, ios::binary);
		tempOfStream.write((char *)&this, sizeof(this));
	}
}
