#include "savedata.h"

// MARK: Constants
char SaveData::invInit[4][5] = {{1, 2, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0}};

char SaveData::healthInit[2] = {100, 100};

// MARK: Class initialiser
SaveData::SaveData(const char* saveFileName) {
	sassert(!nitroFSInit(NULL), "nitroFS failed to initialise when attempting to access the savefile");
	//nitroFSInit(NULL);
	// Open the file in read+update mode (will never over-write)
	this->saveFile = fopen(saveFileName,"r+");
	if(saveFile == NULL) {				// fopen returns NULL if the file does not exist for r+ mode
		fclose(this->saveFile);	
		// MARK: New Game
		// Initialise the inventory
		for(int x = 0; x < 4; x++) {
			for(int y = 0; y < 5; y++) {
				this->inv[x][y] = invInit[x][y];
			}
		}
		this->curItem.x = 0; 
		this->curItem.y = 0;
		// Initialise the health
		for(int x = 0; x < 2; x++) {
			this->health[x] = healthInit[x];
		}
		this->currentMap = 1;			// Start on first map
		this->playerPos.x = floattof32(0.0f);
		this->playerPos.y = floattof32(1.0f);
		this->playerPos.z = floattof32(0.0f);
		// Save the created data
		saveSaveData(*this, saveFileName);
	} else {
		fclose(this->saveFile);
		loadSaveData(*this, saveFileName);
	}
}

void saveSaveData(SaveData sd, const char * filename) {
	sassert(!nitroFSInit(NULL), "nitroFS failed to initialise when attempting to serialise the saveData object.");
	std::ofstream ofs(filename);
	cereal::BinaryOutputArchive ar(ofs);

	ar(sd);
}

void loadSaveData(SaveData sd, const char * filename) {
	sassert(!nitroFSInit(NULL), "nitroFS failed to initialise when attempting to deserialise the saveData object.");
	std::ifstream ifs(filename);
	cereal::BinaryInputArchive ar(ifs);

	ar(sd);
}
