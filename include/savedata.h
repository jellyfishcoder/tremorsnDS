#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <nds.h>
// Filesystem interaction libraries
#include <filesystem.h>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>
// Custom libraries
#include "types.h"
// Cereal serialisation libraries
#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>

class SaveData {
	private:
		friend class cereal::access;
		friend std::ostream & operator<<(std::ostream &os, const SaveData &sd);

		friend void saveSaveData(SaveData sd, const char * filename);
		friend void loadSaveData(SaveData sd, const char * filename);

		template <class Archive>
		void serialize(Archive & ar) {
			ar(currentMap, playerPos, inv, curItem, health);
		}
	public:
		/* Sadly because the serialization had to be called from outside *
		 * the class, all of the members of this class are required to   *
		 * be public.                                                    */
		FILE* saveFile;		// FILE pointer to save file
		char currentMap;			// byte holding current map ID
		MathVector3D<int32> playerPos;		// f32 math vector holding player position on map
		char inv[4][5];				// byte array holding player inventory
		MathVector2D<char> curItem;		// byte math vector holding currently equipted item
		int health[2];				// int array with [1] holding current health and [2] holding max health
		void init(const SaveData & other); 
		
		SaveData(const char* _saveFileName);	// initialiser for load and create

		// Initialise backpack, contains item IDs 1 and 2 which will be a really bad weapon and an apple probably 
		static char invInit[4][5];
		static char healthInit[2];		// Start off with a max of 100 health and at full health

};

//std::ostream & operator<<(std::ostream &os, const SaveData &sd) {
//	return os << sd.currentMap << sd.playerPos.x << sd.playerPos.y << sd.playerPos.z << sd.inv << sd.curItem.x << sd.curItem.y << sd.health;
//}

void saveSaveData(SaveData sd, const char * filename);
void loadSaveData(SaveData sd, const char * filename);


#endif
