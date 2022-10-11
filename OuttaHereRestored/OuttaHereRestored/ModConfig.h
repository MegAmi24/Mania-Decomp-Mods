#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    bool32 superSonicOuttaHere;
    bool32 tailsOuttaHere;
    bool32 knuxOuttaHere;
    bool32 mightyOuttaHere;
    bool32 rayOuttaHere;
    bool32 uniqueCharSfx;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H