// Main header file
#ifndef MAIN_H
#define MAIN_H

// nDS Libraries
#include <nds.h>
#include <nds/ndstypes.h>
#include <nds/arm9/sassert.h>	// To use sassert and print crash message
#include <maxmod9.h>

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

// Background Headers (IK mm for main menu is confusing with mm for maxmod)
#include "mmMainScreen.h"
#include "mmSubScreen.h"

// Soundbank Headers
#include "soundbank.h"
#include "soundbank_bin.h"

// Custom Libraries
#include "inits.h"
#include "types.h"
#include "splash.h"

// Functions Referances
void mainMenu();
void OnKeyPressed(int key);

#endif
