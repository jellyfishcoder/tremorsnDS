// Several keyboard improving functions
#ifndef KEYBOARDPLUS_H
#define KEYBOARDPLUS_H

#include <nds/ndstypes.h>
#include <nds/arm9/background.h>
#include <nds/arm9/keyboard.h>

void keyPress(int c);
void getStringPlus(Keyboard* keyboard, char* stbg, uint maxlen);		// char* stbg stands for string to be gotten
