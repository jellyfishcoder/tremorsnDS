#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <nds.h>
#include <filesystem.h>
#include <stdio.h>
#include <fstream>
#include "types.h"

class SaveData {
	private:
		FILE* saveFile;				// FILE pointer to save file
		char currentMap;			// byte holding current map ID
		MathVector3D<int32> playerPos;		// f32 math vector holding player position on map
		char inv[5][4];				// byte array holding player inventory
		MathVector2D<char> curItem;		// byte math vector holding currently equipted item
		int health[2];				// int array with [1] holding current health and [2] holding max health
		char saveFileName;
		void init(const SaveData & other);
	public:
		SaveData(const char* _saveFileName);	// initialiser for load and create
		bool Save();				// save game now
		//void Delete(bool _areYouSure, bool _areYouSureYoureSure, bool _youUnderstandItWillDieIfYouDoThis);
};

#endif
