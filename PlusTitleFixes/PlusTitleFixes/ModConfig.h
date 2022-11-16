#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    bool32 earlyStart;
    bool32 fixPlusPos;
    bool32 enableEggman;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H