#ifndef INITS_H
#define INITS_H
#include <string>	// Used for std::string type
#include <nds.h>
#include <nds/ndstypes.h>
#include <nds/arm9/sassert.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

#include "sprite.h"

void initVideo(int vidMode);
void initSoundbank(void);

#endif
