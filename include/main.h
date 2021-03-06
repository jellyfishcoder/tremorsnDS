// Main header file
#ifndef MAIN_H
#define MAIN_H

// nDS Libraries
#include <nds.h>
#include <nds/ndstypes.h>
#include <nds/arm9/sassert.h>	// To use sassert and print crash message
#include <maxmod9.h>

// File Sys Libraries
#include <filesystem.h>
#include <dirent.h>

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
// Background Headers (IK mm for main menu is confusing with mm for maxmod)
#include "mmMainScreen.h"
#include "mmSubScreen.h"
// Font headers
#include "font.h"

// Soundbank Headers
#include "soundbank.h"
#include "soundbank_bin.h"

// Custom Libraries
#include "inits.h"
#include "types.h"
#include "button.h"
#include "splash.h"
#include "savedata.h"
#include "items.h"

// Functions Referances
void mainMenu();
void startGame(const char* save);
void updateGameTime();
void incrementTime();
void getSaveName();
void keyPress(int c);
void hideKeyboardW(int splashID);

#endif
